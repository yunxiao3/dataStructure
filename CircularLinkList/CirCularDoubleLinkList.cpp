#include "CircularDoubleLinkList.h"


CircularLinkList<char> test ;


void movehead(){
	int i ; 
	char e;
	cout << "please input the number you want to get"<<endl;
	cin >> i ;
	test.locateElem(i, e);
	cout << "第"<<i <<"个元素是"<<e<<endl;
}	


void delet(){
	int i ; 
	cout << "please input the element you want to ldelete "<<endl;
	cin >> i ;
	test.deleteElem(i);

}	


void deletElem(){
	char i ; 
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

	else
		cout<<"the CircularLinkList is not empty !"<<endl;

}





int main(){



cout << "1. 是否为空 " <<endl ;
cout << "2. 取第i个数据" <<endl;
cout << "3.删除第i个元素"<<endl;
cout << "4. 删除元素E"<<endl;
cout << "5. 置空" <<endl;	
cout << "6. 初始化双链表 "<<endl;
cout << "7. 输入链表"<<endl;
cout << "8. 输出链表 " <<endl;
cout << "9. 退出" << endl;



int choose ;
bool flag = true;

while (flag){

	cin >> choose;

	switch(choose){

		case 1: isEmpty(); break;
		case 2: movehead();  break;
		case 3: delet() ; break;
		case 4:  deletElem() ; break;
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


