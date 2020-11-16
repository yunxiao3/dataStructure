#include <iostream>
using namespace std;


template <typename Elem>
	class Sort
	{
	public:
		void binaryInsertSort();
		void insertSort();

		
	};



template <typename Elem>
	void Sort<Elem> :: binaryInsertSort(){
		int low, mid, high;
		int k = -1, 
		Elem temp;


		for (int i = 1; i < n; i ++){
			temp = index[i];

			while(low <= high)





		}




	}	





template <typename Elem>
	void Sort<Elem> ::  insertSort(){

		Elem temp;

		for (int i = 1, j; i < N; i ++){
				temp = index[i];
				j = i - 1;
				
				while(j >= 0 && index[j] > index[i]){
					index[i] = index[j];
					j--;
				}

				index[i] = temp;

		}
				

	}