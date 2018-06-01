#include "Stack.h"


Stack<int> Stack1 (15);


void  push(){

	int Elem;
	cout<<"输入压栈元素：";
	cin >> Elem;
	Stack1.push(Elem);
	cout<<endl;
}

void pop(){
	int Elem;

	Stack1.pop(Elem);

	cout << Elem << endl;

}
 

void gettop(){
	int Elem;

	Stack1.pop(Elem);

	cout << Elem << endl;

}


void isempty(){

	if (Stack1.isEmpty())
		cout << "栈为空！"<<endl;
	else
		cout << "栈为不空！"<<endl;


}

void init(){

for(int i = 0; i < 10; i ++)
	Stack1.push(i);

}

int main(){

	cout<< "1. 在栈顶压入元素e："<<endl;
	cout<< "2. 弹出栈顶元素e：" <<endl;
	cout<< "3. 读栈顶的元素：" <<endl;
	cout<< "4. 判断栈顶的元素是否空：" <<endl;
	cout<< "5. 把一个栈元素赋给：" <<endl;
	cout<< "6. 求栈中的元素个数：" <<endl;
	cout<< "7. 把一个栈至空："<<endl;
	cout<< "8.随机生成一个栈"<<endl;
	cout<<"9.退出程序"<<endl;
	// Stack<int> Stack3(Stack1);
	// cout<< i << endl;


int choice;
int flag = 0;


while(1){

cin >> choice ;

	switch(choice){
		case 1: push(); break ;
		case 2: pop(); break;
		case 3: gettop(); break;
		case 4: isempty(); break;
		case 5: break;
		case 6: cout<<"栈中的元素个数为"<<Stack1.getLength()<<endl;
		case 7:Stack1.clear(); break;
		case 8:  init(); break;
		case 9: flag = 1; break;

	}



	if (flag)
		break;



}

cout << "栈为空！"<<endl;

// cout<< 10 << endl;

return 0;

}




