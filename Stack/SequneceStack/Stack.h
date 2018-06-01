#include <iostream>

using namespace std;

template <typename Elem>
	class  Stack{

		public:  


			bool pop(Elem &e);
			bool push(Elem e);
			void clear();
			bool isEmpty();
			bool isFull();
			int getLength();
			bool getTop(Elem &e);
			void print();
			virtual ~Stack();
			Stack(const Stack<Elem> & other);
			Stack( int );


		protected:
			int stackSize;
			Elem *base;
			Elem *top;

	};


template <typename Elem>


void Stack<Elem> :: clear(){

	top = base;
}




template <typename Elem>


void Stack<Elem> :: print(){


	if (getLength()){
		int length = getLength();

		for (int i = 0; i < length; i++)
			cout << *(base + i)<< "  " ;

		cout << endl;



		cout<<"|";

		for (int i = 0; i < length; i++)
			cout <<"  ";
		cout<< "|";

		cout << endl;

		cout<< "base";

		for (int i = 0; i < length; i++)
			cout <<"  ";
		cout<< "top";
	}


}





template <typename Elem>


bool Stack<Elem> :: isEmpty(){

	return top == base ? true : false;

}

template <typename Elem>

bool Stack<Elem> :: isFull(){

	return top - base >= stackSize ? true : false;

}

template <typename Elem>

int Stack<Elem> :: getLength(){

	return top - base;

}

template <typename Elem>

bool Stack<Elem> :: push(Elem e){

	if (isFull())	{	
	
		cout << "push failed ! ";

		return false;

	}
	else{
		(*top) = e;
	top ++;
	
	// cout << "push succeed !";

	}
return true;

}



template <typename Elem>

bool Stack<Elem> :: pop(Elem &e){


	if (isEmpty())
		
		return false;

	else
		e = *(--top);

return true;

}

template <typename Elem>
bool Stack<Elem> :: getTop(Elem &e){

	if (isEmpty())
		return false;
	else

	e = *(top - 1);
return true;
}









template <typename Elem>


Stack<Elem> ::  Stack( int size ){

	stackSize = size;

	top = base = new Elem[stackSize];

}

template <typename Elem>

Stack<Elem> ::  Stack( const Stack<Elem>& other ){

	if (stackSize < other.stackSize)
		stackSize = other.stackSize;
	int length = other.top - other.base;
	base = new Elem[stackSize];

	for (int i = 0; i < length; i++)
		*(i + base) = *(i + other.base);

	top = base + length;

	}



template <typename Elem>

Stack<Elem> :: ~Stack(){

	if (!base)
		delete base;
	stackSize = 0;
	top = base = NULL;

}


