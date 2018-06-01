#include <iostream>
using namespace std;

#define MAX 999999;



class HuffmanTree{
	public:


		class Node{
			public:

				Node():lchild(-1),rchild(-1),parent(-1),info('0'),weight(-1){};
				int weight;
				char  info;
				int lchild, rchild, parent;
		};


		class Link{
			public:
				int weight;
				char info;
				Link *lchild, *rchild;

				Link(): lchild(NULL), rchild(NULL) {
				}
		};

		typedef Link *LinkPoint;

		void SqeToLink();
		HuffmanTree();
		HuffmanTree(int);
		~HuffmanTree();
		void create();
		void SqeToLink_aux(int i, LinkPoint p);
		int getRoot();
		void display();
		void initialize();
		void selectMin( int num, int &i, int  &j);
		void displayTree_aux(LinkPoint p);
		void displayTree();



	
		Node *arrary;
		int nodeNum;
		int leafNum;
		LinkPoint root;

	
};




HuffmanTree :: HuffmanTree(int Num){

	leafNum = Num;
	nodeNum = Num * 2 - 1;
	arrary = new Node[nodeNum];


}


HuffmanTree :: ~HuffmanTree(){

	nodeNum = 0;
	delete [] arrary;

}


void HuffmanTree :: selectMin(int num, int &j, int  &k){

	int min1 = MAX;
	int min2 = MAX;



	for (int i = 0; i < num; i ++ ){
			if (arrary[i].parent == -1 ){

				if (arrary[i].weight <  min1){
					min2 = min1;
					min1 = arrary[i].weight;
					k = j;
					j = i;
				}


				else 
					if(arrary[i].weight < min2){
						k = i ;
						min2 = arrary[i].weight;

					}

			}

	}



}


void HuffmanTree :: create(){

	for (int j = leafNum ; j < nodeNum; j++){
		int L, R;
		selectMin(j,L, R);
		arrary[j].weight = arrary[L].weight + arrary[R].weight;
		arrary[L].parent = arrary[R].parent =  j;
		arrary[j].lchild = L;
		arrary[j].rchild = R;
		arrary[j].info = '\0';
	}

}




int  HuffmanTree ::  getRoot(){

	int i;

	for (i = 0; i < nodeNum; i++)
		if (arrary[i]. parent == -1)
			break;

	return i;

}


void HuffmanTree :: initialize(){
	for (int i = 0; i < leafNum; i ++){
		arrary[i].weight = i;
		arrary[i].info = i + 'A' ;
	}

}

 



void HuffmanTree :: display (){


	for (int i = 0; i < nodeNum; i ++){

		cout <<"lchild"<<arrary[i].lchild<<"arrary: " << i <<"\t"<<"parent :" <<arrary[i].parent<<"  info :"<< arrary[i].info<<"  arrary[i].weight :  "<< arrary[i].weight<< endl;
	}


}





void HuffmanTree :: SqeToLink(){

	SqeToLink_aux(getRoot(), root);
}


void HuffmanTree :: SqeToLink_aux(int i, LinkPoint p){

	p = new   Link;
	p -> info = arrary[i].info;
	p -> weight = arrary[i].weight;


	if (arrary[i].lchild > -1)
		SqeToLink_aux(arrary[i].lchild, p -> lchild);
	if (arrary[i].rchild > -1)
		SqeToLink_aux(arrary[i].rchild, p -> rchild);



}



void HuffmanTree ::displayTree(){
	displayTree_aux(root);
}

void HuffmanTree :: displayTree_aux(LinkPoint p){


	if (p){
		cout << p -> weight;
		displayTree_aux(p -> lchild);
		displayTree_aux(p -> rchild);
	}
}


