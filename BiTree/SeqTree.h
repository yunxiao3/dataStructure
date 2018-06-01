#include <iostream>
	using namespace std;
template <typename Elem>
class SeqTree{
	public:
		void clear();
		int getFinalIndex();
		Elem* getInitialAddress();
		Elem getNode(int i);
		SeqTree<Elem>  operator = (SeqTree<Elem> const otherS);
		void setNode(int i, Elem E);
		void append(Elem);
		SeqTree(int num);
		SeqTree();
		~SeqTree();
		SeqTree(SeqTree<Elem> const & otherS);



	// protected
		int size;
		Elem *initialAderss;
		int final;
};



template <typename Elem>
	SeqTree<Elem> :: SeqTree(int num){
		
		size = num;
		initialAderss = new Elem[num];
		final = -1;

	}

template <typename Elem>
	SeqTree<Elem> :: SeqTree(){
		
		size = 0;
		initialAderss = NULL;
		final = -1;

	}


template <typename Elem>
	SeqTree<Elem> :: ~SeqTree(){
		clear();
	}


template <typename Elem>
	SeqTree<Elem> :: SeqTree(SeqTree<Elem> const & otherS){
		cout<<"Copy Constructor Function ! \n";
		size = otherS.size;
		initialAderss = new Elem[size];
		final = otherS.final;
		for (int i = 0; i < final; i ++)
			initialAderss[i] = otherS.initialAderss[i];

	}



template <typename Elem>
	SeqTree<Elem> SeqTree<Elem> :: operator = (SeqTree<Elem> const otherS){

		cout<<"overload Function ! \n";
		
		cout<<"overload Function ! \n";

		return *this;

		cout<<"overload Function ! \n";

		if (this != &otherS){
			clear();
			size = otherS.size;
			initialAderss = new Elem[size];
			final = otherS.final;
			for (int i = 0; i < final; i ++)
				initialAderss[i] = otherS.initialAderss[i];
		}


		return *this;
	}




template <typename Elem>
	void  SeqTree<Elem> ::  append(Elem e){
		final ++;
		initialAderss[final] = e;

	}




template <typename Elem>
	void  SeqTree<Elem> ::  clear(){

		delete [] initialAderss;
		initialAderss = NULL;
	}


template <typename Elem>
	int  SeqTree<Elem> ::   getFinalIndex(){

		return final;

	}



template <typename Elem>
	Elem*  SeqTree<Elem> ::   getInitialAddress(){

		cout<< *initialAderss;

		return initialAderss;

	}



template <typename Elem>
	Elem  SeqTree<Elem> :: getNode(int i){
		if (i < 0 || i > final)
			return;

		return  *(initialAderss + i);

	}


template <typename Elem>
	void  SeqTree<Elem> :: setNode(int i, Elem e){

		if(i > final || i < 0) 
		initialAderss[i] = e;

	}