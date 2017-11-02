#include <vector>
using namespace std;
struct ARC
{
	int head;//leftend
	int tail;//rightend
	bool faccess;//access in forward directional dijkstra
	bool raccess;//access in reverse directional dijkstra
	double weight;//weight of the arc
};
typedef struct ARC ARC;
struct GRAPH
{
	int nodes,arcs;//nodes and arcs
	vector<ARC> fstarmatrix;
	vector<ARC> rstarmatrix;
	//int *fstar;
	//int *rstar;
	vector<int> fstar;
	vector<int> rstar;
};
struct YENPATH
{
	double weight;
	vector<int> pathlist;
	int position;
	bool found;
};
struct forwardstar
{
	bool operator()(const ARC &a, const ARC &b) const
	{
		return ((a.head < b.head)||((a.head == b.head)&&(a.tail < b.tail)));
	}
};
struct reversestar
{
	bool operator()(const ARC &a, const ARC &b) const
	{
		return ((a.tail < b.tail)||((a.tail == b.tail) && (a.head < b.head)));
	}
};
struct cw
{
	bool operator()(const YENPATH &a, const YENPATH &b) const
	{
		return (a.weight<b.weight);
	}	
};
typedef struct GRAPH GRAPH;
typedef struct YENPATH YENPATH;
typedef struct cw cw;
typedef struct forwardstar forwardstar;
typedef struct reversestar reversestar;
/*struct HEAPNODE
{
	int nodeid;
	double keyweight;
};*/
struct PATH
{
	double weight;
	vector<int> pathlist;
};
typedef struct PATH PATH;
struct NODE
{
	int position;
	vector<PATH> pathmat;
	int permanent;
	int finite;
};
typedef struct NODE NODE;
//typedef struct HEAPNODE HEAPNODE;
struct YENPATHMAT
{
	vector<YENPATH> pathmat;
};
/*struct HEAPNODEVECTOR
{
	vector<HEAPNODE> heapelement;
};*/
struct PATHMAT
{
	vector<PATH> pathmat;
	long int kn;
	long int KN;
	long int km;
	long int KM;
};
typedef struct YENPATHMAT YENPATHMAT;
//typedef struct HEAPNODEVECTOR HEAPNODEVECTOR;
#pragma once
class kspath
{
public:
	bool acyclic(PATH,int);
	//bool isempty(HEAPNODEVECTOR);
	//void heapify(HEAPNODEVECTOR &, int, int, vector<NODE> &);
	//void buildheap(HEAPNODEVECTOR &, int, vector<NODE> &);
	void heapify(vector<int> &, int, int, vector<YENPATH>&);
	//void buildheap(vector<YENPATH> &, int, vector<int>&);
	void heapify(vector<int> &, int, int, vector<NODE>&);
	bool cyclic(YENPATH);
	bool same_path(YENPATH, YENPATH);
	YENPATH mergepath(YENPATH, YENPATH);
	YENPATH sp( GRAPH, int, int);
	YENPATHMAT yen(GRAPH, int, int, int);
	PATHMAT dijkstra(GRAPH, int , int, int );
};