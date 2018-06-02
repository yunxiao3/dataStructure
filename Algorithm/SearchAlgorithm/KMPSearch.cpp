#include <iostream>
#include <cstring>



using namespace std;

void getNext(char * str , int * next){


	int len = strlen(str);
	int i  = 1, k = -1;

	next[0] = k;
	
	while( i < len){

		while(k > -1 && str[i] != str[k + 1])
			k = next[k];

		if (str[i] == str[k+1])
			k ++;

		next[i] = k;

		i ++;
	}

	for (i = 0; i < len ; i ++)
		cout <<"next"<< i<<next[i]<<endl;


}


int  KMP (char *str, char *substr){

	int len1 = strlen(str);
	int len2 = strlen(substr);



	// /cout <<len2<<endl;


	int next[len2 + 1] ;


	getNext(substr,next);



	int i = 0, j = 0, k = -1;

	while(i < len1 && k < len2 - 1){

		while (k > -1 && str[i] != substr[k + 1])
			k = next[k];

		if (str[i] == substr[k+1])
				k++;



		if (k == len2 - 1)
			return i - len2 + 1;


		i ++;

	}


	cout <<"K:"<<k<<endl;

	if (k  == len2 - 1)
		return len1 - len2 + 1;

	return -1;


}



int  main(){

	char str[13] = {'a','b','c','d','e','a','b','c','d','e','f','g','\0'};
	char substr[3] = {'c','d','\0'};

	cout << KMP(str,substr);

    return 0;
}
