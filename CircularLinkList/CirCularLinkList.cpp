#include "CircularLinkList.h"


CircularLinkList<char> test ;


void movehead(){
	int i ; 
	cout << "please input the number you want to move "<<endl;
	cin >> i ;
	test.moveHead(i);

}	


void delet(){
	int i ; 
	cout << "please input the element you want to ldelete "<<endl;
	cin >> i ;
	test.deleteElem(i);

}	

void appendElem(){

	char i ;
cout << "please input the element you want to input "<<endl;
	cin >> i ;
	test.appendElem(i);


}


void initlize(){

	for (int i = 1; i < 10; i ++)
		test.appendElem(i+'A');
}



void isEmpty(){

	if (test.isEmpty() == 1)

		cout<<"the CircularLinkList is empty !"<<endl;

}





int main(){



cout << "1. isEmpty" <<endl ;
cout << "2. move headpoint" <<endl;
cout << "3. delete element"<<endl;
cout << "4. initlize other CircularLinkList with the CircularLinkList "<<endl;
cout << "5. clear" <<endl;	
cout << "6. initlize CircularLinkList "<<endl;
cout << "7. input CircularLinkList"<<endl;
cout << "8. output the CircularLinkList " <<endl;
cout << "9. quit" << endl;



int choose ;
bool flag = true;

while (flag){

	cin >> choose;

	switch(choose){

		case 1: isEmpty(); break;
		case 2: movehead();  break;
		case 3: delet() ; break;
		case 4:   break;
		case 5: test.clear();  break;
		case 6: initlize() ;break;
		case 7: appendElem() ;break;
		case 8: test.printElem(); break;
		case 9: flag = false;

	}



}



	// test.test1();


return 0;


}


