#include "BiTree.h"
#include"SeqTree.h"

typedef  char  Elem;  

int main(){


	BiTree<char> Tree;
	SeqTree<char> SeqTree1(20);
	SeqTree1.append('a');	
	SeqTree<char>  S;
	S = SeqTree1;
	 

/*
	cout << B.size;
	B.append('b');


	cout <<"\n\n\n";

	cout<< "Tree size: "<<SeqTree1.size<<"final :"<<SeqTree1.final<<endl<<"finalIndex:"<<SeqTree1.getFinalIndex()<<"  InitialAddress:"	;
	cout<<SeqTree1.getInitialAddress()<<endl;


	cout << "Node Number :" << Tree.countNode()<<endl;
	cout << "Leaf Number :" << Tree.countLeaf()<<endl;
	cout << "deep Number :" << Tree.depth()<<endl;


*/
	char a[10] = {'a'};

	cout<<a;

	return 0;
}