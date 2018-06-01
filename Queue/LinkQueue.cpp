#include "LinkQueue.h"

int main(){


	LinkQueue<char>  LinkQueue;
		// LinkQueue<char>   LinkQueue1;

	
	 
	
	char E;

	for (int i = 76 ; i < 100; i ++)
		LinkQueue.enterQueue(i);




	LinkQueue.getFront(E);

	LinkQueue.clear();

	cout<<E<<LinkQueue.getLength();
	
	



return 0;
}