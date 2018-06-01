#include <iostream>
using namespace std;

typedef int Vertex;

// #define MAX 20;




class ShortPathInfo{

	public:
		bool node[20];	
		int distance;
};


template <typename Elem>
	class Graph
	{
	public:
		bool isEmpty();
		void input();
		void miniSpanKruskal();
		void miniSpanPrim(Vertex v);
		void ShortPath_DIJ(Vertex v);
		void ShortPath_FLOYD();
		Graph(int ,int , int);
		void print();
	
	protected:
		int kind;
		int vexNum;
		Vertex *vertexs;
		int arcNum;
		Vertex **arcs;

	};


template <typename Elem>

	 Graph<Elem> :: Graph(int k, int v, int a){
		kind = k;
		vexNum = v;
		arcNum = a;
		vertexs =  new Vertex[vexNum];
		arcs = new Vertex *[v];
		for (int i = 0; i < v; ++i)
		{
			arcs[i] = new Vertex[v];
		}


	}


template <typename Elem>
	bool Graph<Elem> :: isEmpty(){

		return !vexNum;
	}




template <typename Elem>
	void Graph<Elem> :: print(){

		for (int i = 0; i < vexNum; ++i){
			for (int j = 0; j < vexNum; ++j){
				cout << arcs[i][j] << "  ";
			}

			cout << endl;
		}


	}



template <typename Elem>
	void Graph<Elem> :: input(){

		cout << "please input begin and end weight: \n";
		int begin, end, weight;
		

		for (int i = 0; i < arcNum ; ++i){

				cin >>begin>>end>>weight;
				arcs[begin][end] = weight;
				arcs[end][begin] = weight;
			}	


	}


template <typename Elem>
	void Graph<Elem> :: miniSpanKruskal(){

		struct{

			int begin;
			int end;
			int cost;
		}edges[arcNum],temp;




		int miniShort;
		int begin;
		int end;
		int set[vexNum];


		for (int i = 0; i < arcNum; i++)
			edges[i].cost = 999999;

		for (int i = 0, k = 0; i < vexNum; i ++){

			for (int j = i + 1; j < vexNum; j++){
				if (arcs[i][j] >  0 ){
					edges[k].begin = i;
					edges[k].end = j;
					edges[k].cost = arcs[i][j];
					k ++;
				}
			}

		}




		for (int i = 0; i < arcNum - 1; i++)
			for(int j = i + 1; j < arcNum; j++)
				if (edges[i].cost > edges[j].cost){
					temp = edges[i];
					edges[i] = edges[j];
					edges[j] = temp;
				}





		for (int i = 0; i < arcNum ; ++i){

			cout <<edges[i].begin << edges[i].end << edges[i].cost <<endl;
		}



		for (int i = 0; i < vexNum ; ++i)
			set[i] = i;


		
		int k = 1 , j;


		for (int i = 0; i < arcNum; i++){

			if (set[edges[i].begin] != set[edges[i].end]){
				cout<<set[edges[i].begin] << "  "<< set[edges[i].end]<<endl;
				cout << edges[i].begin << "  -->  "  <<edges[i].end<< endl;
				/*if (set[edges[i].begin] != edges[i].begin)
					set[edges[i].end] = set[edges[i].begin];
				else if (set[edges[i].end] != edges[i].end )
						set[edges[i].begin] = set[edges[i].end];
					else */
						set[edges[i].end] = set[edges[i].begin];
				k ++;
				if (k >= vexNum)
					break;

			}				
		}




}


	

