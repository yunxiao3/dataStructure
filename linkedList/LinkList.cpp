	#include "linkList.h"
	typedef char Elem;






	LinkList<Elem>  s;
	int choose;
	bool quit ;


	void insert(){

		int i ;
		Elem e;
		cout<< "请输入第元素序号"; cin >> i ;
		cout<< "请输入第元素"; cin >> e ; 

		s.insert(i,e);

	}


	void deleteElem(){
		int i;
		cout<< "请输入要删除元素序号";
		cin >> i ;
		s.deleteElem(i);
	}





	void getNext(){
		Elem e, next;
		cout<< "请输入元素Ｅ";
		 cin >> e;

		if (s.nextElem(e, next))
			cout << e <<"　后的元素是"<< next<<endl;
		else
			cout <<"error input \n";

	}

	void getElem(){
		int i ;
		Elem next;
		cout<< "请输入第元素序号"; cin >> i ;

	 
		if (s.getElemet(i, next))
			cout  <<"　元素是"<< next<<endl;
		else
			cout <<"error input \n";

	}



	void getPrior(){
		Elem e, next; 

		cout<< "请输入元素Ｅ\n";
		cin >> e;

		if (s.priorElem(e, next))
			cout << e <<"　前的元素是"<< next<<endl;
		else
			cout <<"error input \n";

	}



	bool isEmpty(){
		if (s.isEmpty())
			cout <<"顺序表为空\n";

		else
			cout<<"顺序表不为空\n";
	}


	void findElem (){
		Elem i;
		cout << "please input the Element you want to find ";
		cin >> i ;
		s.getElemet(i);

	}


	void initilize(){


		for (int i = 0 ; i < 10	; i ++)
		s.append(i+'A');

	// cout <<"#include ";
	}


	void initilizeOther(){

			LinkList<Elem>  p;
			p = s;
			cout << "successful !\n";	

	} 


	void append(){
		Elem c;
		cout << "please input the Elem\n";
		cin>> c;
		s.append(c);
	}

	int main(){







	cout<<"************测试非顺序表的操作*************"<<endl;
	cout<<"1.　  取非循环单链表第ｉ个元素"<<endl;
	cout<<"２. 　在第ｉ个元素前插入一个数据域为Ｅ的元素"<<endl;
	cout<<"３. 　判断非循环表是否为空"<<endl;
	cout<<"４．　求非循环表中元素个数"<<endl;
	cout<<"５．　寻找第一个与Ｅ相等的元素"<<endl;
	cout<<"６．　返回某个元素的前驱"<<endl;
	cout<<"７．　返回某个元素的后继"<<endl;
	cout<<"８．　删除第ｉ个元素\n";
	cout<<"９.　 删除非循环单链表的重复值"<<endl;
	cout<<"１０．　把非循环单链表反转\n";
	cout<<"１１．　把一个非循环表赋值给另一个表\n";
	cout<<"１２．把顺序表至空\n";
	cout<<"１３．随机生成一个表\n";
	cout<<"１４．　打印顺序表\n";
	cout<<"１５．　用已有非循环单链表初始化另一个单链表\n";
	cout<<"１６．　输入非循环单链表\n";
	cout<<"17. 多项式运算\n";
	cout<<"18. 退出程序\n";






	while(true){

		cin >> choose;

		switch(choose){

			case 1: getElem() ;break;
			case 2: insert() ;break;
			case 3: isEmpty();break;
			case 4: cout<<"表中元素个数为"<<s.getLength()<<endl;break;
			case 5: findElem();break;	
			case 6: getPrior() ;break;
			case 7: getNext() ;break;
			case 8: deleteElem();break;
			case 9: s.deletRepeat();break;
			case 10: s.adverse();break;
		//	case 10: s.adverse();break;

			case 12: cout<<"clear";s.clear() ;break;
			case 13: initilize() ;cout<<"inintlize";break;
			case 14:cout <<"printElem"<<endl; s.printElem() ;break;
			case 15: initilizeOther() ;break;
			case 16: append() ;break;


			

			case 17:
				char c;
				cout<<"是否确认退出y/n";cin >> c;

				if (c == 'y' || c == 'Y')
					quit =  true;
				 ;break;

		}


	if (quit)
		break;


	}
		

		return 0;
	}
