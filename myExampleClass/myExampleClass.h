#include <Myrectangle.h>


template <typename Elem>

	class myExampleClass : public Myrectangle <Elem>{
	public:
		friend istream & oprerator >> (istream & in, myExampleClass<Elem> & iD);
		friend ostream & oprerator <<(istream & out, const myExampleClass<Elem> & iD);
		myExampleClass();
		~myExampleClass();
		
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



template <typename Elem>
	istream & operator >> (istream & in, const myExampleClass <Elem>  &iD){

		in >> length >> width;
		if (!in)
			iD = Myrectangle();

		return in;
		
	}



template <typename Elem>
	ostream & operator << (ostream & out, myExampleClass <Elem>  &iD){

		out << length << width ;
		return out;
		
	}







	