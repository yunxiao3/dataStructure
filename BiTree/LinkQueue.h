#include <iostream>
using namespace std;

template <typename Elem>
	class LinkQueue
	{

		private:
			class LinkNode{

			public:

				Elem data ;
				LinkNode * next;

			};

			typedef LinkNode  *LinkPoint;


		public:
			bool enterQueue(Elem e);
			bool outQueue(Elem & e);
			void clear();
			bool isEmpty();
			int getLength();
		 	bool getFront(Elem &e);
			
			LinkQueue( const LinkQueue <Elem> & other);
			LinkQueue();
			virtual	~LinkQueue();
		protected:
			LinkPoint front , rear;
		
	};


template <typename Elem>
	bool	LinkQueue<Elem> ::  enterQueue(Elem e){

		LinkPoint s ;
		s = new LinkNode;
		s -> data = e;
		s -> next = NULL;

		if (!front){
			front =  rear = s;
			rear -> next = NULL;
			return true;
		}

		else
		rear -> next = s;
		rear = s;

	}


template <typename Elem>
	bool	LinkQueue<Elem> ::  outQueue(Elem &e){

		if (!front)
			return false;

		LinkPoint s ;
		s = front;
		e = front -> data;

		front = front -> next;

		delete s;
		s = NULL;


		return true;



	}



template <typename Elem>

	bool	LinkQueue<Elem> ::  getFront(Elem &e){

		if (!front)
			return false;

		e = front -> data;
	return true;

	}

template <typename Elem>
	int	LinkQueue<Elem> :: getLength(){

		LinkPoint s = front;
		int j = 0;
		while(s){
			s = s ->  next;
			j ++;
		}

	return j;
		}

template <typename Elem>
	bool	LinkQueue<Elem> ::  isEmpty(){


		return front ?  false : true;
	}
 

template <typename Elem>
	void LinkQueue<Elem> ::  clear(){

		LinkPoint p, s;
		p = front ;
		while(p){
			s = p;
			p = p -> next;
			delete s;

		}

		front = rear = NULL;

	}
 


template <typename Elem>
	LinkQueue<Elem> ::  LinkQueue(){

		front =  rear = NULL;

	}

template <typename Elem>
	LinkQueue<Elem> ::  ~LinkQueue(){


	}


template <typename Elem>

 	LinkQueue<Elem> :: LinkQueue(const LinkQueue<Elem> &other){

		front = rear = NULL;

		LinkPoint s, p , op;
		op = other.front;
		while(op){
			s = new  LinkNode;
			s -> data = op -> data;

			if (!front)
				front = s;
			else 
				p -> next = s;
			p = s;
			op = op -> next;
		}

		p -> next = NULL;
		rear -> p;

	}