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
	int *fstar;
	int *rstar;
};
struct PATH
{
	double weight;
	vector<int> pathlist;
	int end;
};
struct YENPATH
{
	double weight;
	vector<int> pathlist;
	vector<int> arcindex;
	vector<int> inaccessible;
	bool found;
	int end;
};
struct SPATH
{
	double weight;//To store the weight of the path
	vector<int> pathlist;//To store the path
	vector<int> accessible_arcs;//To store the index of all the arcs accessible from the end node
	int end;//To store the right end node in forward dijkstra and left end node in reverse dijkstra
	double bestweight;
	int bestarc;//To store the arc with the best possible weight in future iteration
	int bestnode;//To store the other node in the arc with the best possible weight in future iteration
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
struct comparebyweight
{
	bool operator()(const PATH &a, const PATH &b) const
	{
		return (a.weight<b.weight);
	}
};
struct cw
{
	bool operator()(const YENPATH &a, const YENPATH &b) const
	{
		return (a.weight<b.weight);
	}	
};
struct bestweightsort
{
	bool operator()(const SPATH &a, const SPATH &b) const
	{
		return (a.bestweight<b.bestweight);
	}		
};
struct weightsort
{
	bool operator()(const SPATH &a, const SPATH &b) const
	{
		return (a.weight<b.weight);
	}	
};
typedef struct GRAPH GRAPH;
typedef struct SPATH SPATH;
typedef struct PATH PATH;
typedef struct YENPATH YENPATH;
typedef struct bestweightsort bestweightsort;
typedef struct weightsort weightsort;
typedef struct cw cw;
typedef struct comparebyweight comparebyweight;
typedef struct forwardstar forwardstar;
typedef struct reversestar reversestar;
struct SPATHMAT
{
	vector<SPATH> pathmat;
};
struct PATHMAT
{
	vector<PATH> pathmat;
};
struct YENPATHMAT
{
	vector<YENPATH> pathmat;
};
typedef struct PATHMAT PATHMAT;
typedef struct SPATHMAT SPATHMAT;
typedef struct YENPATHMAT YENPATHMAT;
#pragma once
class kspath
{
public:
	bool cyclic(SPATH);
	bool cyclic(PATH);
	bool cyclic(YENPATH);
	bool cyclic(PATH , bool *);
	bool cyclic(SPATH , bool *);
	bool same_path(SPATH, SPATH);
	bool same_path(PATH, PATH);
	bool same_path(YENPATH, YENPATH);
	YENPATH mergepath(YENPATH, YENPATH);
	PATH mergepath(PATH, PATH, double);
	SPATH mergepath(SPATH, SPATH, double);
	YENPATH sp( GRAPH, int, int);
	YENPATHMAT yen(GRAPH, int, int, int);
	SPATHMAT bidijkstra(GRAPH, int , int, int );
};