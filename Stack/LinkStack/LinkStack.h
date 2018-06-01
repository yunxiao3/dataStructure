#include <iostream>
using namespace std;

template <typename Elem>
class LinkStack
{
	private:

		class LinkNode
		{
		public:
			Elem data;
			LinkNode *next;
			
		};


		typedef LinkNode *NodePoint;



	public:

		void clear();
		int getLength();
		bool getTop(Elem &e);
		bool isEmpty();
		LinkStack <Elem>    operator = (LinkStack <Elem>  otherS);
		bool pop(Elem &e);
		bool push(Elem  e);
		LinkStack();
		~LinkStack();


	protected:
		NodePoint top;
	
};



template <typename Elem> 
	LinkStack<Elem> :: LinkStack(){
		top = NULL;
	}


template <typename Elem> 
	LinkStack<Elem> :: ~LinkStack(){
		clear();
	}




template <typename Elem> 
	void	LinkStack<Elem> :: clear(){

		NodePoint p;
				while(top){
					p = top -> next;
					delete top ; 
					top = p;

				}


		top = NULL;
	}





template <typename Elem> 
	bool LinkStack<Elem> :: getTop(Elem  &e){


		e = top -> data;

	}



template <typename Elem> 
	bool LinkStack<Elem> :: isEmpty(){
		if( top == NULL )
			return true;
		return false;

	}


template <typename Elem> 
	bool LinkStack<Elem> :: pop(Elem &e){

		if (top == NULL )
			return false;

		e = top -> data;
		NodePoint p;
		p = top -> next;
		delete top ; 
		top = p;

		return true;

	}



template <typename Elem> 
	bool LinkStack<Elem> :: push(Elem e){
		NodePoint p;
		p = new LinkNode;
		p -> data = e;
		p -> next = top;
		top = p;

	}