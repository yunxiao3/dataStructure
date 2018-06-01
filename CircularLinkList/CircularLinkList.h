#include <iostream>
using namespace std;

template <typename Elem>
	class CircularLinkList{
		public:
		
			class LinkNode{
				public:
					Elem data;
					LinkNode *next;
			};
			typedef LinkNode *LinkPoint;

			bool printElem();
			bool moveHead (int i);
			bool insertElem(int i,Elem e );
			bool isEmpty();
			bool deleteElem(Elem e);
			bool deleteElem(int i);
			bool appendElem(Elem e);
			bool clear();
			void del();
			bool locateElem(int i, Elem & point);
			int getLength();
			CircularLinkList();
			virtual ~CircularLinkList();
			CircularLinkList(const CircularLinkList<Elem> & other);
		
		protected:
			LinkPoint head;
	};




template <typename Elem>
	bool CircularLinkList<Elem> ::insertElem(int i , Elem e){

		LinkPoint s, point, prior;
		s = new LinkNode;
		s -> data = e;
			point = head;
			while( point && point -> next != head)
				point = point -> next ;
		if (i == 1){		
			if (point){
				s -> next = head ;
				head = s;
				point -> next = head;
			}
			else{
				head = s;
				head -> next = head;
			}


		return true;

			}


			int j = 1;
			prior = head;

		while(j < i - 1 && prior -> next != head){

			prior = prior -> next;
			j ++;

		}


		s -> next = prior -> next;
		prior -> next = s; 


	return true;
		}

	
/*

template <typename Elem>
		void CircularLinkList <Elem> ::*/


template <typename Elem>
	bool CircularLinkList<Elem> :: locateElem(int i, Elem &e){

		int j = 1;
		LinkPoint s  = head;

		while( s && j < i && s -> next != head ){
			s = s -> next;
			j ++;
		}
		

		if (i == j){

			e = s -> data;					
			return true;
		}
		else
			return false;

	}


template <typename Elem>
	bool  CircularLinkList<Elem> ::moveHead(int i){



	 	LinkPoint s = head;
	 	int j = 0;
	 	while(head && j < i  ){
	 		s = s -> next;
	 		j ++;
	 	}

	 	if (j != i  ){
	 		// cout << "failure !!"<<i<<"    "<<j<<endl;
	 		return false;
	 	}
	 	else
	 		 head = s;

	 	return true;
	 }


template <typename Elem>
	bool CircularLinkList<Elem> :: appendElem(Elem e){

		LinkPoint s, op;
		op = head;
		s = new LinkNode;
		s -> data = e;
		s ->  next = head;

		if (!head){

			head = s;
			head -> next = s;
			return true;
		}

		while(op -> next != head)
			op = op -> next;
		op -> next = s;

	}


template <typename Elem>
	bool CircularLinkList<Elem> :: clear(){

		if (!head)
			return true ;

		LinkPoint s,p ;
		s =  head;
		p = s -> next;
		while(p -> next != head){
			s = p ;
			p = p -> next ;
			delete s;


		}

		delete head ;
		head = NULL;

	return true;


	}	



template <typename Elem>
	bool CircularLinkList<Elem> :: printElem(){
		if (!head)
			return false;

		LinkPoint s = head;
		int i = 0 ;
		while(s -> next != head ){
			cout<< "["<< i << "]";
			 s = s ->  next;
			i ++;
		}

		cout<< "["<< i << "]";

cout<<endl;

		 s = head;
		while(s -> next != head ){
			cout<< s -> data << "->";
			s = s ->  next;
		}

		cout<< s -> data;

		return true;
	}

template <typename Elem>
	int CircularLinkList<Elem> :: getLength(){

		LinkPoint s = head;
		int j = 1;
		if (!head)
			return 0;

		while(s->next != head){
			j++;
			s = s-> next;

		}
	return j;
	}


template <typename Elem>
	bool  CircularLinkList<Elem> :: deleteElem(int i ){
	
		if (!head)

			return false;

		LinkPoint rear, point, front;
		int  j = 1;

		point = rear = head;


		if (i == 1){

			if (head -> next == head){
				head = NULL;
			}

			else{

				while(rear -> next != head)
					rear = rear -> next;

				head = head -> next;

				rear -> next = head;
			}

			cout << "delete "<<point  -> data   <<endl;

			delete point ;

			point = NULL;

			return true ;
		}
			



		while(j < i ){

			front = point;
			point = point -> next ;
			j ++;
			// cout <<j ;
		}


		if (j != i)
			return false;


		cout << "delete "<<point  -> data   <<endl;

		front -> next = point -> next;

		if (head == point){

			head = NULL;
		}

		delete point ;
		point = NULL;

	return true;


	}







template <typename Elem>
	 CircularLinkList<Elem> :: CircularLinkList(){

	 	head = NULL;
	 }

template <typename Elem>
	bool  CircularLinkList<Elem> ::isEmpty(){

	 	return head ? false :  true;
	 }


template <typename Elem>
	 CircularLinkList<Elem> :: ~ CircularLinkList(){

	 	clear();
	 }

template <typename Elem>
	 CircularLinkList<Elem> ::  CircularLinkList(const CircularLinkList<Elem> & other){
	 
	 		LinkPoint s, op, p;
	 		op = other.head;
	 		p = head = NULL;
		 	while(op != other.head){
		 	s = new LinkNode;
		 	s -> data = op -> data;		 	
		 	if (!head)
		 		head = s;
		 	else
		 		p -> next =  s;

		 		p = s;
		 		op = op -> next;		 		
		 	}

		 	if (head)
		 	p -> next = head;
	 }




