#include"Myrectangle.h"
#include <cstdlib>
#include <stdio.h>
Rectangle <int> MyRectangle;

void setNo(){
	int no;
	cout <<"please input Rectangle's No\n";
	cin >> no;
	MyRectangle.setNo(no);
	cout <<"successful !\n";

}


void setLength(){
	int no;
	cout <<"please input Rectangle's Length\n";
	cin >> no;
	MyRectangle. setLength(no);
	cout <<"successful !\n";
}

void overload(){
	Rectangle <int> MyRectangle1;

	MyRectangle1 = MyRectangle;
	cout <<"successful !\n";
}



int main(int argc, char const *argv[])
{
	
	


cout <<"\no1. set the Number of Myraectangle \n";
cout <<"2. set the Length of Myraectangle \n";
cout <<"3. overload opertor = \n";
cout <<"4. exit  \n";









	int choice;
	bool flag = false;
	while (true){
		if (flag)
			break;

		cin >> choice;

		switch (choice){
			case 1: setNo(); break; 
			case 2: setLength() ; break; 
			case 3: overload() ; break; 
			case 4: flag = true ; break; 
		}


	}


	return 0;
}