#pragma once 

#include <memory>
#include <vector>
#include <queue>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>


using namespace std;






template <class Key, class Value, int MinChild> 
class BPlusTree{

	public:
	class Node{
		public:
			Node(int num){
				keyNum = num;
			}
			bool isLeaf;
			int keyNum;
			virtual ~Node(){};
	};

	class TreeNode : public Node{
		public:
		TreeNode():Node(0){}
		~TreeNode(){}
		//int keyNum; 
		Key key[MinChild*2-1];
		shared_ptr<Node> child[MinChild*2];
	};	

	class TreeLeaf : public Node{
		public:
		TreeLeaf():Node(0){}
		~TreeLeaf(){}
	//	int bucketNum; 
		shared_ptr<TreeLeaf> next;
		shared_ptr<TreeLeaf> pre;
		pair<Key,Value> bucket[MinChild*2-1];

	};


	BPlusTree();
	//bool splitChildNode(shared_ptr<Node> father, int position);
	bool insert(Key const& key, Value const& value);
	bool insertNotFull(shared_ptr<Node> father, Key const& key, Value const& value);
	bool splitChildNode(shared_ptr<Node> father, int position);
	void printLeaf();
	void printTree();
	bool find(shared_ptr<Node> node,Key const& key, Value &value);
	bool find(Key const& key, Value &value);
	//bool find(shared_ptr<TreeNode> node , T const& key);
	//bool find(T const& key);
/*
	bool del(T const& value);
	bool remove(T const& value);
	//bool remove(shared_ptr<TreeNode> node, T const& value);
	bool remove(shared_ptr<TreeNode> node, T const& value);
	bool mergeChild(shared_ptr<TreeNode>  father, int position,
		shared_ptr<TreeNode> leftChild, shared_ptr<TreeNode> rightChild);
	T precursor(shared_ptr<TreeNode> node);
	
	T successor(shared_ptr<TreeNode> node);
	bool borrowFromRight(shared_ptr<TreeNode>  father, int position,
		shared_ptr<TreeNode> node, shared_ptr<TreeNode> rightChild);
	bool borrowFromLeft(shared_ptr<TreeNode>  father, int position,
		shared_ptr<TreeNode> node, shared_ptr<TreeNode> leftChild);

	bool splitChildNode(shared_ptr<TreeNode>, int );	
	bool insertNotFull(shared_ptr<TreeNode> node ,T const& value);
	void printTree();*/
	


	private:
	
	int M;
	shared_ptr<Node> root;
	shared_ptr<TreeLeaf> leafHead;
};
