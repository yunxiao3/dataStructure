


​	因为这几天看数据库方索引面的内容，所以自己写了一个BTree的Demo，加深一下自己对BTree的理解。因为只是为了学习，所以只涉及了基本功能的实现，不涉及并发和事务以及优化。

​	本文中的BTree完全是参照算法导论中的描述实现的，导论中的Btree在插入和删除删除过程中，都会提前检验节点是否可能出现不符合BTree规则的状态，提前将这些可能出现的状态消除掉。这样做的好处是，避免了插入删除过程中可能出现的递归回溯问题，使得在并发过程中加锁更加的简单。但是因为提前预判的缘故也会带来一些不必要的合并和分裂子树的消耗。至于这种避免递归回溯的实现方式，是否比递归回溯保证Tree正确性的方式更为高效？我觉得是个挺有意思的问题，在我现在看来如果是并发情况下，由于需要加锁，提前预判会比递归回溯有更好的效果。而单线程情况下则递归回溯会比提前预判有更好的效果。

####　1.　基本概念

B 树是为了磁盘或其它存储设备而设计的一种多叉平衡查找树，一颗Ｂ树具有以下性质：

~~~
1. 每个节点最多有m个孩子。 
2. 除了根节点和叶子节点外，其它每个节点至少有Ceil(m/2)个孩子。 
3. 若根节点不是叶子节点，则至少有2个孩子 
4. 所有叶子节点都在同一层，且不包含其它关键字信息 
5. 每个非终端节点包含n个关键字信息（P0,P1,…Pn, k1,…kn） 
6. 关键字的个数n满足：ceil(m/2)-1 <= n <= m-1 
7. ki(i=1,…n)为关键字，且关键字升序排序。 
8. Pi(i=1,…n)为指向子树根节点的指针。P(i-1)指向的子树的所有节点关键字均小于ki，但都大于k(i-1)
~~~

关于Ｂ树的具体概念可以参照其他blog或者《算法导论》里面都有很详细的描述，并且在https://www.cs.usfca.edu/~galles/visualization/BTree.html上有递归回溯方式的图形化展示动画，本文重点讲一下实现的过程。

#### 2. 基本实现

##### 2.1 插入操作

按照《算法导论》的描述，当root->keyNum == MinChild*2-1需要特殊处理：生成新的root节点，向上生长使得BTree的高度加一。除此之外所有的插入操作都由insertNotFull来完成，并且在递归插入的路径上，不断的检测节点的 keyNum是否等于MinChild * 2 - 1。如果相等，为了防止后面插入过程中splitChildNode使得父节点出现keyNum == MinChild * 2的情况发生向上的递归检验，提前将节点拆分，并继续递归删除。

~~~c++
template<class T>
bool Btree<T>::insert( T const& value){
	if (root == nullptr){
		return false;
	}
   // 按照《算法导论》的描述，当root->keyNum == MinChild*2-1需要特殊处理，生成新的root节点，使得BTree的高度加一
	if (root->keyNum == MinChild * 2 - 1){
		shared_ptr<TreeNode> newNode = make_shared<TreeNode>();
		newNode->child[0] = root;
		newNode->isLeaf = false;
		root = newNode;
		splitChildNode(root,0);
		insertNotFull(root,value);
	}else{
		insertNotFull(root,value);
	}
	return true;
}

template<class T>
bool Btree<T>::insertNotFull(shared_ptr<TreeNode> node ,T const& value){
	if (node == nullptr){
		return false;
	}
	int position = 0;
	while(position < node->keyNum && value > node->key[position] ){
		position++;
	}
	// 如果是叶节，由于之前的递归判断，保证了node->keyNum<MinChild * 2 - 1,因此可以直接插入
	if (node->isLeaf){	
		for (int i = node->keyNum; i > position; --i){
			node->key[i] = node->key[i-1];
		}
		node->key[position] = value;
		node->keyNum++;
	}else{
	// 否则需要判断递归插入的路径上的节点的 keyNum是否等于MinChild * 2 - 1，如果相等，为了防止后面插入过程中splitChildNode使得父节点出现keyNum == MinChild * 2的情况发生向上的递归检验，这里提前将节点拆分
		if (node->child[position]->keyNum == MinChild * 2 - 1){
			splitChildNode(node,position);
			if (value > node->key[position]){
				position++;
			}		
		}
		insertNotFull(node->child[position],value);
	}
	return true;
}
~~~

##### 2.1 删除操作

和插入操作一样，如果root->keyNum==1，需要做一些特判和处理。安照《算法导论》中的描述：BTREE的高度降低只会发生在root。如果树root->keyNum==1，可能存在子树合并使得root节点的keyNum==0不满足条件的情况，因此提前合并使得的Btree高度下降，避免回溯。

~~~c++
template<class T>
bool Btree<T>::del( T const& value ){
	if (root == nullptr){
		cout<<"The tree is empty !\n";
		return false;
	}
//如果root->keyNum==1，需要做一些特判和处理。安照《算法导论》中的描述：BTREE的高度降低只会反生在root
	if (root->keyNum == 1){
		if (root->isLeaf){
			if (root->key[0] == value){
				root = nullptr;
				return true;
			}else{
				return false;
			}
		}
		auto leftChild = root->child[0];
		auto rightChild = root->child[1];
		if (rightChild == nullptr){
			cout << "rightChild == nullptr \n";
		}
		// 如果root左右孩子上的keyNum都小于MinChild-1，则将左右孩子合并树的高度减一
		if( leftChild->keyNum <= MinChild-1 && rightChild->keyNum <= MinChild-1){
			mergeChild(root,0,leftChild,rightChild);
			root = leftChild;
			return remove(root,value);
		// 如果存在一个节点的keyNum > MinChild-1,则可以直接执行remove(root,value)。
		// 原因在于,在删除过程中即使节点keyNum <= MinChild-1也可以从兄弟节点借一个值。
		// 而不会发生从root节点借一个值，合并子树使得root节点的keyNum==0不满足条件的情况
		}else{
			return remove(root,value);
		} 
	}else{
		return remove(root,value);
	}
}
~~~

在特判完了root节点以后，还要实现在叶子节点和中间节点的删除操作:

1. 如果待删除的key在叶子节点上找到，因为在上一步的递归删除过程中保证了next->node的keynum > minChild-1所以可以直接直接删除，无需回溯检查。

2. 如果待删除的key在中间节点上找到，且左右孩子存在一个keyNum大于MinChild - 1的节点，则找该key的前驱或者后继（newvalue),并用newvalue的值覆盖当前的key以后， 继续向下递归删除newvalue。（不直接删除newvalue的原因是，无法保证删除以后的树仍合法，如leaf节点的keyNum<MinChild - 1） 如果key值附近的左右孩子都为MinChild - 1,则将key和与其相邻的左右child节点合并，再继续向下删除。执行这一步的目的是保证向下删除过成中delete递归所经过的路径上，所有节点的keynum数量>MinChild - 1. 这样在后面的节点合并时不会出现父节点的keynum < MinChild - 1导致回溯的情况。(MergeChild候需要向父节点的一个key)，removeAtNode()，的代码在后面给出。
3. 如果key在内部节点中没有找到，且nextNode的keynum大于MinChild - 1，可以直接继续删除操作否则需要借一个节点或者合并两个子节点来保证nextNode的keyNum > MinChild-1，removeMergeOrBorrow的代码在后面给出。

~~~c++
template<class T>
bool Btree<T>::remove(shared_ptr<TreeNode> node, T const& value){

	//找到正确的position的值
	int position = 0;
	while(position < node->keyNum && value > node->key[position]){
		position++;
	}
	// 如果待删除的key在叶子节点上找到，因为在上一步的递归删除过程中保证了
	// next->node的keynum > minChild-1所以可以直接直接删除，无需回溯检查
	if (node->isLeaf){
		if (value == node->key[position]){
			for (int i = position; i < node->keyNum-1; ++i){
				node->key[i] = node->key[i+1];
			}
			node->keyNum--;
			return true;
		}
		return false;
	}else{
	 // 如果待删除的key在中间节点上找到，且左右孩子存在一个keyNum大于MinChild - 1的节点，则找该key的前驱或者后继（newvalue),并用newvalue的值覆盖当前的key以后， 继续向下递归删除newvalue。（不直接删除newvalue的原因是，无法保证删除以后的树仍合法，如leaf节点的keyNum<MinChild - 1） 如果key值附近的左右孩子都为MinChild - 1,则将key和与其相邻的左右child节点合并，再继续向下删除。执行这一步的目的是保证向下删除过成中delete递归所经过的路径上，所有节点的keynum数量>MinChild - 1. 这样在后面的节点合并时不会出现父节点的keynum < MinChild - 1导致回溯的情况。(MergeChild候需要向父节点的一个key)
		if (value == node->key[position]){
			return removeAtNode(node,position);
		// 如果key在内部节点中没有找到，则需要继续向下递归删除
		}else{
			shared_ptr<TreeNode> nextNode = node->child[position];
			// 如果nextNode的keynum大于MinChild - 1，可以直接继续删除操作
			if(nextNode->keyNum > MinChild - 1){
				return remove(nextNode,value);
			// 否则需要借一个节点或者合并两个子节点来保证nextNode的keyNum > MinChild-1	
			}else{
				return removeMergeOrBorrow(node,position,value);
			}
		}
	}
	return false;
}

~~~

##### 3 查找操作

查找操作相对比较简单就直接给出实现代码：

~~~c++
template<class T>
bool Btree<T>::find( T const& key){
	int position = 0;
	while(position < root->keyNum && key > root->key[position]){
		position++;
	}
	if (key == root->key[position]){
		return true;
	}
	if (root->child[position] == nullptr){
		return false;
	}
	return find(root->child[position],key);
}
template<class T>
bool Btree<T>::find(shared_ptr<TreeNode> node , T const& key){
	int position = 0;
	while(position < node->keyNum && key > node->key[position]){
		position++;
	}
	if (key == node->key[position]){
		return true;
	}
	if (node->child[position] == nullptr){
		return false;
	}
	return find(node->child[position],key);
}
~~~

#### 3. 完整代码

​	上述过程只是简单的描述了一下插入和删除的实现，但是里面的很多实现的细节并没有给出，比如合并和分裂子树，向左右兄弟借一个节点，虽然这些实现不是很难，但也有很多细节需要考虑。因此在本文的最后贴上这些方法的实现的代码，完整代码和测试用例可访问：https://github.com/yunxiao3/dataStructure/tree/master/BTree，如有问题可以将其发送到me@jackdu.cn。

~~~c++
template<class T>
bool Btree<T>::splitChildNode(shared_ptr<TreeNode> parent, int position){
	shared_ptr<TreeNode> newChild = make_shared<TreeNode>()/*(MinChild)*/;
	shared_ptr<TreeNode> child = parent->child[position];
	newChild->isLeaf = child->isLeaf; 
	// Copy the bigest value in oldchild to the new child
	// 从原有的孩子拷贝最大到新的节点，不拷贝最小的值是因为，当前实现的Btree中的数据都是从小到大左对齐
	for (int i = 0; i < MinChild - 1; ++i){
		newChild->key[i] = child->key[MinChild + i];
	}
	if (!child->isLeaf){
		for (int i = 0; i < MinChild ; ++i){
			newChild->child[i] = child->child[MinChild + i];
		}
	}
	newChild->keyNum = MinChild - 1;
	child->keyNum = MinChild - 1;
	// 把位于MinChild - 1的值复制到父节点
	for (int i = parent->keyNum; i > position ; --i){
		parent->key[i] = parent->key[i-1];
		parent->child[i+1] = parent->child[i];
	}
	parent->key[position] = child->key[MinChild-1];
	parent->child[position+1] = newChild;
	parent->keyNum++;
}
template<class T>
bool Btree<T>::borrowFromLeft(shared_ptr<TreeNode>  father, int position,
	shared_ptr<TreeNode> node, shared_ptr<TreeNode> leftChild){
	node->child[node->keyNum + 1] =  node->child[node->keyNum]; 
	for (int i = node->keyNum; i > 0; --i){
		node->key[i] = node->key[i-1];
		node->child[i] = node->child[i-1];
	}
	node->key[0] = father->key[position];
	node->child[0] = leftChild->child[leftChild->keyNum];
	node->keyNum++;
	father->key[position] = leftChild->key[leftChild->keyNum-1];
	leftChild->child[leftChild->keyNum] = nullptr;
	leftChild->keyNum--;
}
template<class T>
bool Btree<T>::borrowFromRight(shared_ptr<TreeNode>  father, int position,
	shared_ptr<TreeNode> node, shared_ptr<TreeNode> rightChild){
	node->key[node->keyNum] = father->key[position];
	node->child[node->keyNum+1] = rightChild->child[0];
	node->keyNum++;
	father->key[position] = rightChild->key[0];
	for (int i = 0; i < rightChild->keyNum - 1; ++i){
		rightChild->key[i] = rightChild->key[i+1];
		rightChild->child[i] = rightChild->child[i+1];
	}
	rightChild->child[rightChild->keyNum-1] = rightChild->child[rightChild->keyNum];
	rightChild->child[rightChild->keyNum] = nullptr;
	rightChild->keyNum--;
}
template<class T>
bool Btree<T>::mergeChild(shared_ptr<TreeNode>  father, int position,
	shared_ptr<TreeNode> leftChild, shared_ptr<TreeNode> rightChild){
	leftChild->key[MinChild-1]= father->key[position];
	for (int i = 0; i < MinChild - 1; ++i){
		leftChild->key[MinChild+i] = rightChild->key[i];
	}
	if (!leftChild->isLeaf){
		for (int i = 0; i < MinChild; ++i){
			leftChild->child[MinChild+i] = rightChild->child[i];
			rightChild->child[i] = nullptr;
		}
	}
	leftChild->keyNum = MinChild * 2 - 1; 
	for (int i = position; i < father->keyNum - 1; ++i){
		father->key[i] = father->key[i+1];
		father->child[i+1] = father->child[i+2];
	}
	father->child[father->keyNum] = nullptr;
	father->keyNum--;
}
template<class T>
T Btree<T>::precursor(shared_ptr<TreeNode> node){
	if (node->isLeaf)
		return node->key[node->keyNum - 1];
	else
		return precursor(node->child[node->keyNum]);
}
template<class T>
T Btree<T>::successor(shared_ptr<TreeNode> node){
	if (node->isLeaf)
		return node->key[0];
	else
		return successor(node->child[0]);
}
~~~

removeAtNode和removeMergeOrBorrow的实现：

~~~c++
template<class T>
bool Btree<T>::removeAtNode(shared_ptr<TreeNode> node, int position){
	shared_ptr<TreeNode>  leftChild = node->child[position];
	shared_ptr<TreeNode>  rightChild = node->child[position+1];
	if (leftChild->keyNum >= MinChild){
		T newValue = precursor(leftChild);
		node->key[position] = newValue;
		return true;
	} else if (rightChild->keyNum >= MinChild){
		T newValue = successor(rightChild);
		node->key[position] = newValue;
		return true;
	} else{
		mergeChild(node,position,leftChild,rightChild);
		return true;
	}
	return false;
}
template<class T>
bool Btree<T>::removeMergeOrBorrow(shared_ptr<TreeNode> node, int position, int value){
	shared_ptr<TreeNode> nextNode = node->child[position];
	//如果待删除的key在最左边的子树上，则只存在向右子树借key和合并子树的可能
	if(position == 0){
		shared_ptr<TreeNode> righNode = node->child[position+1];
		if (righNode->keyNum > MinChild - 1){
			borrowFromRight(node,position,nextNode,righNode);
			return remove(nextNode,value);
		}else{
			mergeChild(node,position,nextNode,righNode);
			return remove(nextNode,value);
		}
	//如果待删除的key在最右边边的子树上，则只存在向左子树借key和合并子树的可能
	}else if(position == node->keyNum) {
		shared_ptr<TreeNode> leftNode = node->child[position-1];
		if(leftNode->keyNum > MinChild - 1){
			borrowFromLeft(node,position-1,nextNode,leftNode);
			return remove(nextNode,value);
		}else{
			mergeChild(node,position-1,leftNode,nextNode);
			return remove(leftNode,value);
		}
	// 否则同时存在向左右子树和合并子树的可能
	} else{
		shared_ptr<TreeNode>  righNode = node->child[position+1];
		shared_ptr<TreeNode>  leftNode = node->child[position-1];
		if (righNode->keyNum > MinChild - 1){
			borrowFromRight(node,position,nextNode,righNode);
			return remove(nextNode,value);
		}else if(leftNode->keyNum > MinChild - 1){
			borrowFromLeft(node,position-1,nextNode,leftNode);
			return remove(nextNode,value);
		}else{
			mergeChild(node,position,nextNode,righNode);
			return remove(nextNode,value);
		}
	}
}
~~~

