#include "Myrectangle.h"



template <typename T,typename Elem>

	class myExampleClass : public Rectangle <Elem>{
	public:
		T height;
	friend 	ostream & operator << (ostream & out,const myExampleClass<T,Elem>  &iD){

		out <<iD.length<< iD.width ;
		return out;
		
	}

	
   	friend  istream & operator >> (istream & in,  myExampleClass<T,Elem>   &iD){

		in >> iD.length >> iD.width;
		

		return in;
		
	}
	

		/*myExampleClass();
		~myExampleClass();
		*/
	};


/*template <typename Elem>
	void myExampleClass<Elem> ::  read (istream & in){

		cout << "please the "<<myNo.no<<" rectangle";
		cout << "the length of rectangle :";
		in >> length;
		cout << "please input the width of rectangle";
		in >> width;

	}


template <typename Elem>
	istream & operator >> (istream & in, Myrectangle <Elem>  &iD){

		iD.read(in);
		return in;

	}*/


/*template <typename T,typename Elem>

	istream & operator >> (istream & in,  Rectangle <Elem>  &iD){

		in >> iD.length >> iD.width;
		

		return in;
		
	}




template <typename T,typename Elem>

	ostream & operator << (ostream & out,const Rectangle <Elem>  &iD){

		out <<iD.length<< iD.width ;
		return out;
		
	}*/