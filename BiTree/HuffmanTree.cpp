#include "HuffmanTree.h"


int main(int argc, char const *argv[])
{
	
	HuffmanTree T(20);

	T.initialize();
	T.create(); 
	T.display();
	T.SqeToLink();
	T.displayTree();
	cout<< "rootIndex :" << T.getRoot()<<endl;
	cout<< T.leafNum<<endl;
	cout<< T.nodeNum<<endl;
	cout<<T.arrary[2].info;

	return 0;
}