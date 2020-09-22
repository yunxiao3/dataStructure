#include"bPlusTree.h"

template <class Key, class Value, int MinChild> 
BPlusTree<Key,Value,MinChild>::BPlusTree(){
	leafHead = make_shared<TreeLeaf>();
	leafHead->isLeaf = true;
	root = leafHead;
}


template <class Key, class Value, int MinChild> 
bool BPlusTree<Key,Value,MinChild>::insert(Key const& key, Value const& value){

	if (root == nullptr){
		cout << "root is null";
	}

	if (root->keyNum == MinChild * 2 - 1){
		shared_ptr<TreeNode> newRoot = make_shared<TreeNode>();
		newRoot->isLeaf = false;
		newRoot->child[0] = root;
		root = newRoot;
		splitChildNode(root,0);
		cout << "#####root splitChildNode######\n";
		//if (key > )
		insertNotFull(root,key,value); 
	}else{
		insertNotFull(root,key,value);
	}

//	insertNotFull(key,value);
}


template <class Key, class Value, int MinChild> 
bool BPlusTree<Key,Value,MinChild>::splitChildNode(shared_ptr<Node> node, int index){
	//if (fa)
			//cout << " splitChildNode\n";

	auto father = dynamic_pointer_cast<TreeNode>(node);
 	if (father->child[index]->isLeaf){
 		shared_ptr<TreeLeaf> leaf =	dynamic_pointer_cast<TreeLeaf>(father->child[index]);
 		shared_ptr<TreeLeaf> newLeaf = make_shared<TreeLeaf>();
 		
 		newLeaf->isLeaf = true;
 	
 					//cout << " bug1\n";

 		// Copy the value from child to newchild
 		for (int i = 0; i < MinChild-1; ++i){
 			newLeaf->bucket[i] = leaf->bucket[MinChild+i];
 		}
 		newLeaf->keyNum = MinChild - 1;
 		leaf->keyNum = MinChild;

 		if (leaf->next != nullptr){
 			leaf->next->pre = newLeaf;
 			newLeaf->pre= leaf;
 			newLeaf->next = leaf->next;
 			leaf->next = newLeaf;
 		}else{
 			leaf->next = newLeaf;
 			newLeaf->pre = leaf;
 		}

 		for (int i = father->keyNum; i > index; --i){
 			father->key[i] = father->key[i-1];
 			father->child[i+1] = father->child[i];
 		}
 		father->key[index] = leaf->bucket[MinChild-1].first;
 		father->child[index+1] = newLeaf;
 		father->keyNum++;
 		

 	}else{
 		shared_ptr<TreeNode> child = dynamic_pointer_cast<TreeNode> (father->child[index]);
 		shared_ptr<TreeNode> newChild = make_shared<TreeNode>();
 		newChild->isLeaf = false;
 		// Copy the value from child to newchild
 		for (int i = 0; i < MinChild-1; ++i){
 			newChild->key[i] = child->key[MinChild+i];
 		}
 		for (int i = 0; i < MinChild; ++i){
 			newChild->child[i] = child->child[MinChild + i];
 		}
 		child->keyNum = MinChild - 1;
 		newChild->keyNum = MinChild - 1;

 		for (int i = father->keyNum; i > index; --i){
 			father->key[i] = father->key[i-1];
 			father->child[i+1] = father->child[i];
 		}
 		father->key[index] = child->key[MinChild-1];
 		father->child[index+1] = newChild;
 		father->keyNum++;
 	}
}


template <class Key, class Value, int MinChild> 
bool BPlusTree<Key,Value,MinChild>::insertNotFull(shared_ptr<Node> node, Key const& key, Value const& value){
	if(node->isLeaf){
		auto leafNode = std::dynamic_pointer_cast<TreeLeaf>(node);
		int index = leafNode->keyNum - 1; 
		
		/*
		#### Wrong Implement ####
		while(index >= 0){
			if (leafNode->bucket[index].first > key){
				break;
			}
			index--;
		}
		if (index < 0) {index = 0;}
		*/

		while(index >= 0 && leafNode->bucket[index].first > key){
			index--;
		}
		index++;

		for (int i = leafNode->keyNum; i > index ; --i){
			leafNode->bucket[i] = leafNode->bucket[i-1];
		}
		leafNode->bucket[index] = make_pair(key,value);
		node->keyNum++;
		cout<< key << value << "insert Success !\n";
	}else{
		auto treeNode = std::dynamic_pointer_cast<TreeNode>(node);
		int index = treeNode->keyNum - 1; 
		/*
		Wrong implement 
		while(index >= 0){
			if (treeNode->key[index] < key){
				break;
			}
			index--;
		}
		if (index < 0) {index = 0;}
		*/
		

		while(index >= 0 && treeNode->key[index] > key){
			index--;
		}
		index++;

		if(treeNode->child[index]->keyNum == MinChild*2 - 1){
			splitChildNode(treeNode,index);
			// treeNode's key have changed after splitChildNode
			if (key > treeNode->key[index]){
				index++;
			}	
			insertNotFull(treeNode->child[index],key,value);
		}else{
			insertNotFull(treeNode->child[index],key,value);
		}

	}
}

template <class Key, class Value, int MinChild> 
bool BPlusTree<Key,Value,MinChild>::find(Key const& key, Value &value){
	if (root->isLeaf){
		auto treeLeaf = dynamic_pointer_cast<TreeLeaf>(root); 
		for (int i = 0; i < treeLeaf->keyNum; ++i){
			if (treeLeaf->bucket[i].first == key){
				value = treeLeaf->bucket[i].first;
				return true;
			}
		}
		return false;
	}else{
		auto treeNode = dynamic_pointer_cast<TreeNode>(root); 
		/*
		int index = treeNode->keyNum - 1; 
		while(index >= 0 && treeNode->key[index] > key){
			index--;
		}
		if ( treeNode->key[index] == key){
			return find(treeNode->child[index],key,value);
		}else{
			index++;	
			return find(treeNode->child[index],key,value);
		}
		*/
		int index = 0;
		while(index < treeNode->keyNum  && treeNode->key[index] < key){
			index++;
		}
		return find(treeNode->child[index],key,value);		
	}
}

template <class Key, class Value, int MinChild> 
bool BPlusTree<Key,Value,MinChild>::find(shared_ptr<Node> node,Key const& key, Value &value){
	if (node->isLeaf){
		auto treeLeaf = dynamic_pointer_cast<TreeLeaf>(node); 
		for (int i = 0; i < treeLeaf->keyNum; ++i){
			if (treeLeaf->bucket[i].first == key){
				value = treeLeaf->bucket[i].second;
				cout<< key << " find value : " << value;
				return true;
			}
		}
		return false;
	}else{
		auto treeNode = dynamic_pointer_cast<TreeNode>(node); 
		/*
		// In this way, when key is little enough, index can be -1 which may cause segmentation fault
		int index = treeNode->keyNum - 1; 
		while(index >= 0 && treeNode->key[index] > key){
			index--;
		}
		if ( treeNode->key[index] == key){
			return find(treeNode->child[index],key,value);
		}else{
			index++;	
			return find(treeNode->child[index],key,value);
		}
		*/
		int index = 0;
		while(index < treeNode->keyNum  && treeNode->key[index] < key){
			index++;
		}
		return find(treeNode->child[index],key,value);
	}
}


/*############### Remove Value in B tree ##############*/
	
template <class Key, class Value, int MinChild> 
bool BPlusTree<Key,Value,MinChild>::remove(Key const key){



}


template <class Key, class Value, int MinChild> 
bool BPlusTree<Key,Value,MinChild>::removeAtLeaf(shared_ptr<Node> node, Key const key){
	auto treeLeaf = dynamic_pointer_cast<TreeLeaf>(node); 
	int index = 0;
	for (; index < treeLeaf->keyNum; ++index){
		if (treeLeaf->bucket[index].first == key){
			break;
		}
	}
	if (index == treeLeaf->keyNum){
		cout << "can't find and remove " << key <<endl;
		return false;
	}
	for (int i = index; i < treeLeaf->keyNum-1; ++i){
		treeLeaf->bucket[index] = treeLeaf->bucket[index+1];
	}
	treeLeaf->keyNum--;
	return true;
}


template <class Key, class Value, int MinChild> 
bool BPlusTree<Key,Value,MinChild>::removeAtNode(shared_ptr<Node> node, int index){
	auto treeNode = dynamic_pointer_cast<TreeNode>(node); 
	/*
	DEBUG:	Maybe exist bug when reomve key 
	*/
	// 如果删除节点的左子树的keyNum > MinChild -1则可以向右边找一个后继替代待删除的key
	if (treeNode->child[index]->keyNum > MinChild -1){
		Key newKey = precursor(treeNode->child[index]);
		Key key = treeNode->key[index];
		treeNode->key[index] = newKey;
		//并且继续递归删除后继newKey
		return remove(treeNode->child[index],key);
	}
	// 如果删除节点的右子树的keyNum > MinChild -1则可以向右边找一个后继替代待删除的key
	else if (treeNode->child[index+1]->keyNum > MinChild -1){
		Key newKey = successor(treeNode->child[index+1]);
		Key key = treeNode->key[index];
		treeNode->key[index] = newKey;
		//并且继续递归删除后继newKey
		return remove(treeNode->child[index+1],key);
	}else{
		//合并左右子树将key移到子树上面继续删除
		mergeChild(treeNode,index,treeNode->child[index],treeNode->child[index+1]);
		return remove(treeNode->child[index],treeNode->key[index]);
	}
}

template <class Key, class Value, int MinChild> 
bool BPlusTree<Key,Value,MinChild>::borrowOrMerge(shared_ptr<Node> node,  int index){

}


template <class Key, class Value, int MinChild> 
bool BPlusTree<Key,Value,MinChild>::remove(shared_ptr<Node> node, Key const key){

	if (node->isLeaf){
		return removeLeaf(node,key);
	}else{
		auto treeNode = dynamic_pointer_cast<TreeNode>(node); 
		int index = 0;
		while(index < treeNode->keyNum  && treeNode->key[index] < key){
			index++;
		}
		//如果key在TreeNode节点上调用removeAtNode
		if(treeNode->key[index] == key){
			return removeAtNode(node,index);
		//如过不在则继续递归删除，此时应该判断nextNode的keyNum值是否大于MinChild - 1
		}else{
			//如果nextNode的keynum大于MinChild - 1，直接继续删除
			if (treeNode->child[index]->keyNum > MinChild - 1){
				return remove(treeNode->child[index], key);
			// 否则需要向左右子树借一个节点，或者合并两个子节点来保证nextNode的keyNum > MinChild-1
			}else{
				if ( borrowOrMerge(node,index) ){
					return remove(treeNode->child[index], key);
				}else{
					cout<< "borrowOrMerge ERROR" << endl;
					return false;
				}
			}
		}
	}
}





template <class Key, class Value, int MinChild> 
bool BPlusTree<Key,Value,MinChild>::mergeChild(shared_ptr<Node>  father, int position,
	shared_ptr<Node> leftChild, shared_ptr<Node> rightChild){
	/*
		ToDo
	*/
}

template <class Key, class Value, int MinChild> 
Key BPlusTree<Key,Value,MinChild>::precursor(shared_ptr<Node> node){
	if (node->isLeaf){
		auto treeLeaf = dynamic_pointer_cast<TreeLeaf>(node); 
		return treeLeaf->bucket[treeLeaf->keyNum - 1].first;
	}
	else{
		auto treeNode = dynamic_pointer_cast<treeNode>(node); 
		return precursor(node->child[node->keyNum]);
	}
}

template <class Key, class Value, int MinChild> 
Key BPlusTree<Key,Value,MinChild>::successor(shared_ptr<Node> node){
	if (node->isLeaf){
		auto treeLeaf = dynamic_pointer_cast<TreeLeaf>(node); 
		return treeLeaf->bucket[0].first;
	}
	else{
		auto treeNode = dynamic_pointer_cast<treeNode>(node); 
		return precursor(node->child[0]);
	}
}
template <class Key, class Value, int MinChild> 
bool borrowFromRight(shared_ptr<Node>  father, int position,shared_ptr<Node> node, shared_ptr<Node> rightChild){
	/*
		ToDo
	*/
	return false;

}
template <class Key, class Value, int MinChild> 
bool borrowFromLeft(shared_ptr<Node>  father, int position,
	shared_ptr<Node> node, shared_ptr<Node> leftChild){
	/*
		ToDo
	*/
	return false;
}









/*################# Test Function　 ################*/

template <class Key, class Value, int MinChild> 
void BPlusTree<Key,Value,MinChild>::printLeaf(){
	shared_ptr<TreeLeaf> node = leafHead;
	int num = 0;
	while(node != nullptr && node->next != leafHead){
		cout << "bucket " << num << " ";
		for (int i = 0; i < node->keyNum; ++i){
			cout << " key: " << node->bucket[i].first << " value: " << node->bucket[i].second <<" ";
		}
		cout << endl;
		node = node->next;
		num++;
	}
}

template <class Key, class Value, int MinChild> 
void BPlusTree<Key,Value,MinChild>::printTree(){
	
	if (root == nullptr){
		cout<<"Empty Tree \n";
		return;
	}
	queue< pair<shared_ptr<Node>,int> > q;
	q.push( make_pair(root,1) );
	int depth = 0;
	while(!q.empty()){
		shared_ptr<Node> node = q.front().first;
		if (depth < q.front().second){
			cout<< " \n depth : "<< depth << " --------";
			depth = q.front().second;
		}
		q.pop();

		if (node->isLeaf){
			shared_ptr<TreeLeaf> leaf = dynamic_pointer_cast<TreeLeaf>(node);
			for (int i = 0; i < leaf->keyNum; ++i){
				cout << " key: "<< leaf->bucket[i].first << " value: " << leaf->bucket[i].second;
			}
			cout<< "# ";
		}else{
			shared_ptr<TreeNode> treeNode = dynamic_pointer_cast<TreeNode>(node);
			for (int i = 0; i < treeNode->keyNum; ++i){
				cout << " key: "<< treeNode->key[i];
			}
			cout<< "# ";			
			for (int i = 0; i <= treeNode->keyNum; ++i){
				if (treeNode->child[i] == nullptr){
					break;
				}
			q.push(make_pair(treeNode->child[i],depth+1));
				}	
		}
	}
}


int main(int argc, char const *argv[]){
	
	BPlusTree<int,int,3> tree ;

	for (int i = 0; i < 1800; ++i){
		tree.insert(i,i*10);
	}
	cout<<"insert success!";
	for (int i = 0; i < 1800; ++i){
		int value = 0;
		int key = 0;
		bool ok = tree.find(i,value);
	/*	if (ok == true){
			cout << value <<" ";
		}
*/
		if (ok == false){
			cout<< "#########find##### " << i+1 <<" ERROR!" << endl;
			//return -1;
		}
	}
	tree.printTree();
	while(true){
		int value = 0;
		int key = 0;
		cin >> key;
		bool ok = tree.find(key,value);
		if (ok){
			cout << value << endl;
		}else{
			cout << "can't find value\n";
		}
	}
	return 0;
}
