#include <iostream>

using namespace  std;


template <typename Elem>

	class LinkList {

		public : 
			class LinkNode{
				public :
					 Elem data;
					 LinkNode *next;					 
			};

			typedef LinkNode *Nodepointer;

			void adverse();

			void clear();

			bool deleteElem(int i);

			void printElem();

			bool deleteElem(Elem e);

			void deletRepeat();

			bool getElemet(int i , Elem & e);

			bool getElemet(Elem e);

			Nodepointer getHead();

			int getLength();

			bool insert(int i, Elem e);

			bool isEmpty();
			void append(Elem e);

			// bool localateElem(Elem e,  );

			bool  nextElem(Elem e, Elem & next);

			LinkList <Elem>  operator = (LinkList<Elem> rigthL);
			bool priorElem(Elem e, Elem &prior_e);

			LinkList();

			virtual	~LinkList();

			LinkList(const LinkList<Elem> & otherL);

		protected : 
				Nodepointer head;

	};



template <typename Elem>
	void LinkList<Elem> :: append(Elem e){


		Nodepointer	s = new LinkNode;
			s -> data = e;


			if ( !head ) {
				head = s;
			}

			else{
				Nodepointer p = head;
				while (p -> next)
					p = p -> next;
				p -> next = s;
			}

	}



template <typename Elem>
	void LinkList<Elem> ::  printElem(){
		int j = 1;
		Nodepointer p = head;

		while(p){

				

			cout<< "["<<j <<"]";

			p = p -> next;

			j++;
		}

p = head;

cout<<endl;
while(p){

				

			cout<< " "<<p -> data	 <<" ";

			p = p -> next;

			j++;
		}


	cout<<endl;
	

	}


template <typename Elem>
	bool LinkList<Elem> :: isEmpty(){

		return head ? false : true;
	}


template <typename Elem>
	bool LinkList<Elem> ::getElemet(Elem e){
			int j = 1;

			Nodepointer p = head ;

			while(p -> data != e  && p){

				p = p -> next;
				j ++;

			}

			if( !p ){
				cout << "can't find the Element in LinkList";
				return false;
			}
			else
				cout << "the No of Element :"<< e << "is "<<j; 

			return true;

	}


template <typename Elem>
	bool LinkList<Elem> :: nextElem(Elem e , Elem & next){

		if (!head)
			return false;

		Nodepointer r;
		r = head;
		while (r && r -> data != e){
			r = r -> next;
		}

		if (r && r -> next){
			next = r -> next -> data;
			return true;
		}

		else
			return false;
	}




template <typename Elem>
	bool LinkList<Elem> :: priorElem(Elem e , Elem & next){

		if (!head)
			return false;
		Nodepointer r,  p;
		r = head;
		p = NULL;
		while (r && r -> data != e){
			p = r;
			r = r -> next;
			// cout<<"  "<<"r -> data";
		}

		if (p){

			cout<<"priorElem\n";

			next = p -> data;
			return true;
		}

		else
			return false;

}






template <typename Elem>
	void LinkList<Elem> :: adverse(){
		Nodepointer  r,p,q;

		if (!head)
			return ;

		r = NULL; p = head; q = p -> next;

		while(p){
			p -> next = r;
			r = p;
			p = q;
			if (q)
				q = q -> next;
		}  

		head = r;


	}



template <typename Elem>	
		void LinkList<Elem> :: clear(){

			if (!head){

				Nodepointer q, p;
				p = NULL ; q = head ;
				while(q){
					p = q;
					q = q -> next ;
					delete p; 
					p = NULL;	
				}

			}		head = NULL;

		}


template <typename Elem>
		bool LinkList<Elem> :: deleteElem(int i){

			// cout<<"删除元素\n";

			if (!head)
				return false;

			Nodepointer r, p;
			int j = 1;
			 p = head;

			if (i == 1){
				head = head -> next;
				delete p ;
				p = NULL;
			return true;

			}


			while(j < i && p){
				r = p ;
				p = p -> next;
				j ++;

			}



			if (i != j ){
				cout<<"删除失败\n";
				return false;
			}

			r -> next = p -> next;
			delete p ;
			p = NULL;
			cout<<"删除成功\n";
		return true;

}


template <typename Elem>
		bool LinkList<Elem> :: deleteElem(Elem e){
			Nodepointer r, p, q;

			r = NULL; p = head;


				while(p && p->data != e ){

					r = p;
					p = p -> next;

				}

				if(p == NULL)
					return false;
				if(p == head)
					head = head -> next;
				else
					r = p -> next;
				
				delete p;
				p = NULL;
				
				return true;


		}


template <typename Elem>
		void LinkList<Elem> :: deletRepeat(){

			Nodepointer r, p, s;
			r = NULL;
			p = head ;
			while(p){

				s = head;

				while (s != p){
					if (s -> data == p -> data){

					}
				}
			}



		}



template <typename Elem>
		bool LinkList<Elem> :: getElemet(int i, Elem &e){
			if(i < 1)
				return false;

			int j  = 1;
			Nodepointer p = head ;

			while(j < i  && p){

				p = p -> next;
				j ++;

			}

			if( !p )
				return false;
			else
				e = p -> data;

			return true;

		}

template <typename Elem>
	typename LinkList<Elem> :: Nodepointer   LinkList<Elem> :: getHead(){
			return head;

		}   

template <typename Elem>
		int  LinkList<Elem> :: getLength(){
			int i = 0;

			Nodepointer p = head; 
			while(p){
				i++;
				p = p -> next;
				//cout <<i<<endl;

			}


		return i ;



		}




template <typename Elem>
		bool LinkList<Elem> :: insert(int i, Elem e){


			int j = 1;

			Nodepointer r = NULL, p = head, s = NULL ;
			while(j < i - 1 && p){
				j ++;
				p = p -> next;

			}


			s = new LinkNode;
		//	assert(!s);

			s -> data = e;


			if ( i == 1) {
				s -> next = head ;
				head = s;
			}

			else{

				s -> next = p -> next;
				p -> next = s;
			}
				cout<<"insert successful" << endl;

		return true;
			

		}




template <typename Elem>
	 LinkList<Elem>   LinkList<Elem> :: operator = (LinkList <Elem> rigthL){

	 	Nodepointer p = NULL;
	 	Nodepointer pr = rigthL.head;

	 	Nodepointer s;


	 	if (this != &rigthL){

	 		clear();

	 		while(pr){

	 			s = new LinkNode;
	 			// assert(!s);

	 			s -> data = pr -> data;
	 			
	 			if (!head)
	 				head = s;
	 			else

	 				s -> next = pr -> next;

	 			p = s;

	 			pr = pr -> next;

	 		}



	 		if (p)
	 			p -> next = NULL;

	 	}

	return *this;

	 }



template <typename Elem>
	 LinkList<Elem> :: LinkList(const LinkList & otherL){

	 	Nodepointer p = otherL.head;
	 	Nodepointer s = NULL ,rp = NULL;
	 	head = NULL;

	 	while(p){

	 		s = new  LinkNode;

	 		// assert (!s);		

	 		s -> data = p -> data;


	 		if(!head)
	 			head = s;
	 		else
	 			rp -> next = s;


	 		rp = s;

	 		p = p -> next;

	 	}


	 	if(rp)
	 		rp -> next = NULL;



	 }





template <typename Elem>
	 LinkList<Elem> :: LinkList(){

	 	head = NULL;

	 }


template <typename Elem>
	 LinkList<Elem> :: ~LinkList(){
	 clear();
	 }