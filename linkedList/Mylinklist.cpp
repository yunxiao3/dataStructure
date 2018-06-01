#include "linkList.h"

#define  L   1



template<typename Elem>
class Mylinklist : public LinkList <Elem>
{
public:
	void test();

	Mylinklist();
	~Mylinklist();
	
};






template<typename Elem>
void Mylinklist<Elem> :: test(){


	typename LinkList<Elem>::	Nodepointer a;
}