#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define N  10


void selectSort(int arr[]){

	for (int i = 0; i < N; ++i){
		int minJ = i;
		for(int j = i + 1; j < N; j++){
			if (arr[minJ] > arr[j]){
				minJ = j;
			}
		}
		int tmp = arr[i];
		arr[i] = arr[minJ];
		arr[minJ] = tmp;
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

 	selectSort(arr);

 	for (int i = 0; i < N; ++i){
 		cout << arr[i] << " "; 
 	}
 	cout << endl;

	return 0;
}