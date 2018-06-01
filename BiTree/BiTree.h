#include <iostream>
#include"LinkQueue.h"
#include"Stack.h"
using namespace std;
 

template<typename Elem>

class BiTree
{
	public:

		class Node{

			public:
				Node() : lchild(NULL), rchild(NULL){};
				Elem data;
				Node *lchild, *rchild;
		};

		typedef Node *NodePointer;


	public:
		void clear();
		int countLeaf();
		int countNode();
		int depth();
		void displaySeqTree();
		void exchangeLRchild();
		NodePointer getRoot();
		void inOrderTravelse();
		bool isEmpty();
		void layOrderTraverse();
		void linkToSequential();
		void noRecursionInOrderTraverse();
		void postOrderTraverse();
		void preOrderTraverse();
		void randomCreate();
		// void sequentialToLink();


	private:
		void BiTree_aux(NodePointer & p,  NodePointer otherP);
		int countLeaf_aux(NodePointer p);
		int countNode_aux(NodePointer p);
		void deleteNode_aux(NodePointer p);
		int depth_aux(NodePointer p);
		void inOrderTraverse_aux(NodePointer p);
		void postOrderTraverse_aux(NodePointer p);
		void exchangeLRchild_aux(NodePointer p);
		void preOrderTraverse_aux( NodePointer p);
		void inOrderTravelse_aux(NodePointer p);
		void noRecursionPreOrderTraverse();
		void sequentialToLink_aux(NodePointer p);

	public:
		BiTree();
		~BiTree();
		BiTree(const BiTree<Elem> & otherT);



	protected:
		NodePointer root;

};









template <typename Elem>
void BiTree<Elem> :: clear(){

	deleteNode_aux(root);
	root = NULL;

}



template <typename Elem>
void BiTree<Elem> :: deleteNode_aux( NodePointer p){
	
	if(p){

		deleteNode_aux(p -> rchild);
		deleteNode_aux(p -> lchild);
		delete p; 
		p = NULL;

	}

}







template <typename Elem>
int BiTree<Elem> :: countLeaf(){

	return countLeaf_aux(root);

}



template <typename Elem>
int BiTree<Elem> :: countLeaf_aux(NodePointer p){

	static int i = 0;
	int num ;

	if (p){

		if ( !p -> rchild && !p -> lchild)
			i ++;


		countLeaf_aux(p -> lchild);
		countLeaf_aux(p -> rchild);

	}

	if (p == root){

		num = i ;
		i = 0;
	} 


return num;

}



template <typename Elem>
int BiTree<Elem> :: countNode(){

	return countNode_aux(root);

}



template <typename Elem>
int BiTree<Elem> :: countNode_aux(NodePointer p){

	int num ;
	static int i = 0;

	if (p){

		i ++;

		countNode_aux(p -> rchild);
		countNode_aux(p -> lchild);
	}


	if (p == root){
		num = i ; 
		i = 0;

	}

return num ;

}




template <typename Elem>
int BiTree<Elem> :: depth(){

	return	depth_aux(root);

}




template <typename Elem>
int BiTree<Elem> :: depth_aux(NodePointer p){

	if (!p)
		return 0;


	int deepL =  depth_aux(p -> lchild);
	int deepR = depth_aux(p -> rchild); 


return ( deepR >  deepL ? deepR : deepL ) + 1;

}



template <typename Elem>
void  BiTree<Elem> :: exchangeLRchild(){

	exchangeLRchild_aux(root);

}


template <typename Elem>
void  BiTree<Elem> :: exchangeLRchild_aux(NodePointer p){


	if (p){



		exchangeLRchild_aux(p -> rchild);
		exchangeLRchild_aux(p -> lchild);

		NodePointer temp;
		temp = p -> lchild;
		p -> lchild = p -> rchild;
		p -> rchild = temp;
	}

}



template <typename Elem>
 typename  BiTree<Elem> :: NodePointer  BiTree<Elem> :: getRoot(){

	return root;

}



template <typename Elem>
void  BiTree<Elem> :: inOrderTravelse(){

	inOrderTravelse_aux(root);

}


template <typename Elem>
void  BiTree<Elem> :: inOrderTravelse_aux(NodePointer p){

	if (p){
		inOrderTravelse_aux(p -> lchild);
		cout << p -> data;
		inOrderTravelse_aux(p -> rchild);
	}
}






template <typename Elem>
void  BiTree<Elem> :: preOrderTraverse(){

	preOrderTraverse_aux(root);

}


template <typename Elem>
void  BiTree<Elem> :: preOrderTraverse_aux( NodePointer p){

	if (p){
		
		cout << p -> data;
		preOrderTraverse_aux(p -> lchild);
		preOrderTraverse_aux(p -> rchild);
	}
}


template <typename Elem>
void  BiTree<Elem> :: layOrderTraverse(){

	LinkQueue<NodePointer> Q;
	NodePointer p;


	if (root)
		Q.enterQueue(root);

	while(!Q.isEmpty())	{
		 Q.outQueue(p);

		 cout << p -> data;

		 if (p -> lchild)
		 		Q.enterQueue(p -> lchild);

	 	 if (p -> rchild)
	 		Q.enterQueue(p -> rchild);

	}

}


template <typename Elem>
void  BiTree<Elem> :: noRecursionInOrderTraverse(){


	NodePointer p  = root;
	Stack<NodePointer> S;

	while(root || !S.isEmpty()){

	
		if (p){
			S.push(p);
			p = p -> lchild;
	
		}

		else{

			S.pop(p);
			cout << p -> data;
			p = p -> rchild;

		}

	}

}



template <typename Elem>
void  BiTree<Elem> :: noRecursionPreOrderTraverse(){


	NodePointer p  = root;
	Stack<NodePointer> S;

	while(root || !S.isEmpty()){

	
		if (p){

			cout << p -> data;
			S.push(p);
			p = p -> lchild;
	
		}

		else{

			S.pop(p);
			p = p -> rchild;

		}

	}

}






/*template <typename Elem>
void  BiTree<Elem> :: sequentialToLink_aux(NodePointer p){

	// if() 
	p = new BiTree<Elem> :: Node;
	// p -> data = S.get(i);
	if ()



}
*/





template <typename Elem>
BiTree<Elem> :: BiTree(){

	root = NULL;
}


template <typename Elem>
BiTree<Elem> :: ~ BiTree(){


	clear();
}