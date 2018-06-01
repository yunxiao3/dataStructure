#include "LinkStack.h"
#include<ctime>
#include<cstdlib>


int main(int argc, char const *argv[]){
	LinkStack<char> S;
	

	srand((unsigned)time(NULL));	


	for (int i = 0, e; i < 1000; ++i){
		e =rand()%26;
		S.push(e+'A');

	}


	char A;


	for (int i = 0; i < 1000; ++i){
		S.pop(A);cout<<i<<" ";
		cout << A<<"\t";
		

	}


	return 0;
}