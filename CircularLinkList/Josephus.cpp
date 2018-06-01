#include "CircularLinkList.h"
#include <stdio.h> 
#include <iostream> 
#include <time.h> 
#include<cstdlib>

CircularLinkList<char> JOSEPHUS;

void initlize(){

	srand( (unsigned)time( NULL ));

	for (int i = 0; i < rand() % 100; i ++)
		JOSEPHUS.appendElem(  rand() % 26 +'A');
}



int main(int argc, char const *argv[])
{



	cout <<"***********JOSEPHUS******************\n";
	initlize();
	JOSEPHUS.printElem();cout <<endl;

	cout<<"please input begin number and the interal \n";
	int  begin, interal, NUM = 1;
	cin >> begin >> interal;
	JOSEPHUS.moveHead(begin );
	cout << "第 " << NUM << "次" <<"出列";
	JOSEPHUS.deleteElem(interal);
	JOSEPHUS.moveHead(interal - 1);
	
	JOSEPHUS.printElem();cout<<endl<<endl;


	while(!JOSEPHUS.isEmpty()){

	NUM ++;

	cout << "第 " << NUM << "次" <<"出列";

	JOSEPHUS.deleteElem(interal);
	JOSEPHUS.moveHead(interal - 1);
	
	JOSEPHUS.printElem();cout <<endl<<endl;
	// cout << "kong ? "<<JOSEPHUS.isEmpty() << endl;



	}


	return 0;
}
