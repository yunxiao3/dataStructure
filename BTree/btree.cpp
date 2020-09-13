#include"btree.h"

template<class T>
Btree<T>::Btree(){
	root = make_shared<TreeNode>();
	
	//root = temp;
}



template<class T>
bool Btree<T>::del( T const& value ){



	if (root == nullptr){
		cout<<"The tree is empty !\n";
		return false;
	}

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
		if( leftChild->keyNum <= MinChild-1 && rightChild->keyNum <= MinChild-1){
			mergeChild(root,0,leftChild,rightChild);
			root = leftChild;
			return remove(root,value);
		}else{
			return remove(root,value);
		} 
	}else{
		return remove(root,value);
	}

}

template<class T>
bool Btree<T>::remove(shared_ptr<TreeNode> node, T const& value){
	
/*	if (node == nullptr){
		cout<<"#######33  node == nullptr\n";
	}*/

	int position = node->keyNum - 1;
	while(position >=0 && value < node->key[position]){
		position--;
	}

	// 如果待删除的key在叶子节点上找到，因为之前在搜索的过程中保证了next->node的keynum > minChild-1
	// 所以可以直接直接删除，无需回溯检查
	if (node->isLeaf){

		if (value == node->key[position]){
			for (int i = position; i < node->keyNum-1; ++i){
				node->key[i] = node->key[i+1];
			}
			node->keyNum--;
		//	cout << "find delete value "<< value << " in btree\n";
			return true;
		}
		// cout << "Can't find delete value in btree\n";
		return false;
	}else{
		// 如果待删除的key在中间节点上找到，且左右孩子存在一个keyNum大于MinChild - 1的节点，则找该key的前驱或者后继（newvalue）
		// 在将newvalue的值赋值给当前的key以后，继续向下递归删除newvalue。（不直接删除newvalue的原因是，无法保证删除以后的树仍合法）
		// 如果key值附近的左右孩子都等于MinChild - 1,则先将改key和与其相邻的左右child节点合并形成一个新的包含minChild * 2 - 1的节点
		// 再继续向下删除，执行这一步的目的是保证向下删除过成中delete递归所经过的路径上，所有节点的keynum数量>MinChild - 1，这样在两个
		// child node合并的时候需要向farther node一个key后，也不会使得farther node的keynum < MinChild - 1导致回溯。
		if (position >= 0 && value == node->key[position]){
			shared_ptr<TreeNode>  leftChild = node->child[position];
			shared_ptr<TreeNode>  rightChild = node->child[position+1];
			if (leftChild->keyNum >= MinChild){
				T newValue = precursor(leftChild);
				//cout<<"Find precursor " << newValue << endl;
				node->key[position] = newValue;
				return remove(leftChild,newValue);
			} else if (rightChild->keyNum >= MinChild){
				T newValue = successor(rightChild);
			//	cout<<"Find successor " << newValue << endl;
				node->key[position] = newValue;
				return remove(rightChild,newValue);
			} else{
				mergeChild(node,position,leftChild,rightChild);
				//cout<<" mergeChild A :"<< endl;
				
				return remove(leftChild,value);
			}
		// 如果key在内部节点中没有找到，则需要继续向下递归删除
		}else{
			position++;
			shared_ptr<TreeNode> nextNode = node->child[position];

			//如果nextNode的keynum大于MinChild - 1，直接继续删除否则需要借一个节点或者合并两个子节点来保证nextNode的keyNum > MinChild-1
			if(nextNode->keyNum > MinChild - 1){
				//cout<<"nextNode->keyNum > MinChild - 1\n";
				return remove(nextNode,value);
			}else{
				//如果待删除的key在最左边的child的子数上则只存在向右子数借key的可能，否则需要合并子数再删除
				if(position == 0){
					shared_ptr<TreeNode> righNode = node->child[position+1];
					if (righNode->keyNum > MinChild - 1){
						borrowFromRight(node,position,nextNode,righNode);
					//	cout<<"borrowFromRight A\n";
						return remove(nextNode,value);
					}else{

						mergeChild(node,position,nextNode,righNode);
					//	cout<<" mergeChild B :"<< endl;
						return remove(nextNode,value);
					}
				}else if(position == node->keyNum) {
					shared_ptr<TreeNode>  leftNode = node->child[position-1];
					if(leftNode->keyNum > MinChild - 1){
						borrowFromLeft(node,position-1,nextNode,leftNode);
					//	cout<<"borrowFromLeft A\n";
						return remove(nextNode,value);
					}else{
						mergeChild(node,position-1,leftNode,nextNode);
					//	cout<<" mergeChild C :"<< endl;
						return remove(leftNode,value);
					}
				} else{
					shared_ptr<TreeNode>  righNode = node->child[position+1];
					shared_ptr<TreeNode>  leftNode = node->child[position-1];
					if (righNode->keyNum > MinChild - 1){
						borrowFromRight(node,position,nextNode,righNode);
						//cout<<"borrowFromRight B\n";
						return remove(nextNode,value);
					}else if(leftNode->keyNum > MinChild - 1){
						borrowFromLeft(node,position-1,nextNode,leftNode);
						//cout<<"borrowFromLeft B\n";
						return remove(nextNode,value);
					}else{
						mergeChild(node,position,nextNode,righNode);
						return remove(nextNode,value);
					}
				}
			}
		}
	}
	return false;
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

	//int keyNum = rightChild->keyNum - 1;
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
/*	shared_ptr<TreeNode> y = x->child[position];
	shared_ptr<yTreeNode> z = x->child[position+1];*/
	
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
	// bug
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








template<class T>
bool Btree<T>::find( T const& key){
	int position = root->keyNum - 1;
	while(position >=0 && key < root->key[position]){
		position--;
	}
	if (position >= 0){
		if (key == root->key[position]){
			//cout<<"find value  is isLeaf"<< root->isLeaf << "\n";
			return true;
		}
	} 
	
	position++;
	if (root->child[position] == nullptr){
		//cout<<"can't Find value \n";
		return false;
	}
	//cout<<"return find "<< position <<" \n";
	return find(root->child[position],key);
}


template<class T>
bool Btree<T>::find(shared_ptr<TreeNode> node , T const& key){
	int position = node->keyNum - 1;
	while(position >=0 && key < node->key[position]){
		position--;
	}
	if (position >= 0){
		if (key == node->key[position]){
			//cout<<"find value  is isLeaf"<< node->isLeaf << "\n";
			return true;
		}
	} 
	position++;
	if (node->child[position] == nullptr){
		//cout<<"can't Find value \n";
		return false;
	}
	//cout<<"return find "<< position <<" \n";
	return find(node->child[position],key);
}


/*template<class T>
shared_ptr<TreeNode> Btree<T>::newNode(){
	shared_ptr<TreeNode> node = make_shared<TreeNode>;
	//node->key[0]=value;
	node->isLeaf = false;
	node->keyNum = 0;
	return node;
}*/




template<class T>
bool Btree<T>::splitChildNode(shared_ptr<TreeNode> parent, int position){
	shared_ptr<TreeNode> newChild = make_shared<TreeNode>()/*(MinChild)*/;
	shared_ptr<TreeNode> child = parent->child[position];

	newChild->isLeaf = child->isLeaf; 

	// Copy the bigest value in oldchild to the new child
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


	// Add the new value and node to parent
	//int p = parent->keyNum;
	for (int i = parent->keyNum; i > position ; --i){
		parent->key[i] = parent->key[i-1];
		parent->child[i+1] = parent->child[i];
	}

	parent->key[position] = child->key[MinChild-1];
	parent->child[position+1] = newChild;
	parent->keyNum++;

}

template<class T>
bool Btree<T>::insert( T const& value){
	
	if (root == nullptr){
		return false;
	}

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

	int position = node->keyNum - 1;

	// Find the right place to insert the new value
	while(position >= 0 && value < node->key[position] ){
		position--;
	}
	position++;

	// if the node is leaf node, insert the new value dirctly
	if (node->isLeaf){	

		for (int i = node->keyNum; i > position; --i){
			node->key[i] = node->key[i-1];
		}
		node->key[position] = value;
		node->keyNum++;
		//cout<<"node->key[position] = " << value;
		//node->key.insert(node->key.begin() + position, value);
	}else{ 
		if (node->child[position]->keyNum == MinChild * 2 - 1){
			splitChildNode(node,position);
			if (value > node->key[position]){
				position++;
			}		
		}
		//cout<<"insertNotFull " << value;
		insertNotFull(node->child[position],value);
	}
	return true;
}


template<class T>
void Btree<T>::printTree(){
	
	if (root == nullptr){
		cout<<"Empty Tree \n";
		return;
	}

	queue< pair<shared_ptr<TreeNode>,int> > q;
	q.push( make_pair(root,1) );
	int depth = 0;
	while(!q.empty()){
		shared_ptr<TreeNode> node = q.front().first;
		if (depth < q.front().second){
			cout<< " \n depth : "<< depth << " --------";
			depth = q.front().second;
		}
		q.pop();
		
		for (int i = 0; i < node->keyNum; ++i){
			cout << node->key[i] << " ";
		}
		cout<< "# ";
		//if (!node->isLeaf){
			for (int i = 0; i <= node->keyNum; ++i){
				if (node->child[i] == nullptr){
					break;
				}
				q.push(make_pair(node->child[i],depth+1));
			}
		//}
		
	}
}




int main(int argc, char const *argv[]){

	Btree<int> btree/* = Btree<int> Btree()*/;
	
	char flag;
	int temp;

	vector<int> v;
	map<int,bool> m;
	srand((int)time(0)); 
	

	/*for (int i = 0; i < 10000; ++i){
		int num =  rand()%100000;
		v.push_back(num);
	}

	for (int i = 0; i < 1030; ++i){
		btree.insert(v[i]); 
		m[i] = true;
	}


	for (int i = 0; i < 1003; ++i){
		cout << btree.del(v[i]);
		m[i] = false;
	}
*/

	for (int i = 0; i < 50000; ++i){
		int num = rand()%10000000;
		if (m[num]){
			continue;
		}
		bool rt  = btree.insert(num);
		if (!rt){
			cout << "insert "<< num << "ERR\n";
		}
		m[num] = true ; 
	}


	for (int i = 0; i < 1000; ++i){
		int num = rand()%10000000;
		bool rt = btree.find(num); 
		if (rt != m[num]){
			cout<<"find "<< num <<" ERR\n"; 
		}
	}

	for (int i = 0; i < 130000; ++i){
		int num = rand()%10000000;
		bool rt = btree.del(num);  
		if (rt != m[num]){
			cout<<"del ERR can't delete "<< num << "  "<< rt <<"  \n";
			btree.printTree(); 
			return 0;
		};
		m[num] = false;
					
	}

	cout<< "success !" ;
	return 0;


	//btree.printTree();
	while(true){
		cin >> flag >> temp;
		switch(flag){
			case 'i':  btree.insert(temp); break;
			case 'd': btree.del(temp);break;
			case 'f': btree.find(temp);break;
		}

		btree.printTree();
	}
	

	return 0;
}