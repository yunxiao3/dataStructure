#include <iostream>
// #include<>

using namespace std; 


template  <typename  Elem>
class  Rectangle{

	public: 
		class RectangleNo{
			public : int no;
		};

		Rectangle operator = ( Rectangle right);

		void setLength(Elem length);

		void setNo(int N);

		Rectangle();

		Rectangle( const Rectangle <Elem> & otherD);

		virtual ~Rectangle();
	
		Elem length;
		Elem width;
		RectangleNo myNo;
};



template <typename  Elem>
	Rectangle <Elem>  Rectangle <Elem> :: operator = (Rectangle <Elem>  right){
				if ( this != &right){
					length = right.length;
					width = right.width;
					myNo = right.myNo;
				}

				return *this;
} 


template <typename  Elem>
	void  Rectangle<Elem> ::  setLength(Elem lengt){
		
	length = lengt;

	}


template <typename  Elem>
	void Rectangle<Elem> :: setNo(int i ){
		myNo.no = i;

	}



template <typename  Elem>
	Rectangle <Elem> :: Rectangle(){
		length = width = 0;
		cout<<"constructor!";
	}

template <typename  Elem>
	Rectangle<Elem> :: Rectangle ( const  Rectangle<Elem>&  Other ){
		length = Other.length;
		width = Other.width;
		myNo = Other.myNo;
	 cout<< "Copy Initialize Constructor";
	}

template <typename  Elem>
	Rectangle <Elem> :: ~Rectangle(){

		cout<< "Distroy";
	}



