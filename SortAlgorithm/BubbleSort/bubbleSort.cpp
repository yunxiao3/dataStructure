#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

#define N  10


void bubbleSort(int arr[]){

	for (int i = 0; i < N; ++i){
		for(int j = 0; j < N - i - 1; j++){
			if(arr[j] > arr[j+1]){
				int tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}	
	}
}





int main(int argc, char const *argv[]){
	
	int arr[N];
	srand(time(NULL));
 	for (int i = 0; i < N; ++i){
 		arr[i] = rand() % 100;
 		cout << arr[i] << " "; 
 	}
 	cout << endl;

 	bubbleSort(arr);

 	for (int i = 0; i < N; ++i){
 		cout << arr[i] << " "; 
 	}
 	cout << endl;

	return 0;
}