#include "Graph.h"


int main(int argc, char const *argv[])
{
	Graph<int> Kursal(1,6,8);
	Kursal.input();
	Kursal.print();	
	Kursal.miniSpanKruskal();
	return 0;
}