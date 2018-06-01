#include <iostream>
#include"Stack.h"
using namespace std;


Stack<char> S(15);
Stack<int> C(15);
char in[50] = "23-((34-13)*7+6/2)";
char post[50];
int i = 0, j = 0;
char top;
char e;
int flag;
int p = 0;


int jugde[4][4] = { {-1,1,1,-1},
					{-1,-1,1,-1},
					{1,1,1,2},
					{0,0,0,0}				
							};






int getNum(char C){
	if (C == '+' || C == '-')
		return 0;
	if (C == '*' || C == '/')
		return 1;
	if (C == '(')
		return 2;
	return 3;
}





int getFlag(int a, int b){

	return  jugde[b][a];

}





void output(){


	
	while(!S.isEmpty() && flag == -1){
		S.pop(e);
		post[j++] = e;
		S.getTop(top);
		flag = getFlag(getNum(in[i]),getNum(top));
		
	}




}




void inToPostOrder(){	

	while(in[i]){
		if (in[i] >= '0' && in[i] <= '9'){
			
			post[j++] = in[i++];	continue;
		}

		if (S.isEmpty() || in[i] == '('){
				if (S.isEmpty())
				post[j++] = ' ';
			S.push(in[i++]);	continue;
			}

		if (in[i] == ')'){
			while(1){
				S.pop(e);
				if (e == '(')
					break;
				post[j++] = e;
			}

			i ++;
			continue;
		}
		

		post[j++] = ' ';
				
		S.getTop(top);
		flag = getFlag(getNum(in[i]),getNum(top));
		if (flag == 1)
			S.push(in[i++]);
		if (flag == -1){
			output();
			S.push(in[i++]);


		}

	}

	while(!S.isEmpty()){
			S.pop(e);
			post[j++] = e;
	}
	post[j] = '\0';

}






int opert(char a){

	if (a >= '0' && a <= '9')
		return 1;
	if(a == ' ')
		return -1;

	return 2;



}



int get(char A, int i, int j){

	switch(A){

		case '+': return i + j;
		case '-': return i - j;
		case '*': return i * j;
		case '/': return i / j;



	}


}


int caculate(){

	int a;
	int A;
	int B;


	while(post[p]){

		a = 0;



		while(opert(post[p]) ==  1){		
					
				a = a * 10 + (post[p++] - '0');
				
		}

		if (a > 0)
			C.push(a);

		if (opert(post[p]) == 2){
			C.pop(A);
			C.pop(B);
			a = get(post[p],B,A);
			C.push(a);
		}

			p++;


	}


	C.pop(a);


	return a;

}














