#include <vector>
using namespace std;
struct GRAPH
{
	int nodes,arcs;//nodes and arcs
	int *arcmatrix[3];//[0]-left end;[1]-right end;[2]-accessibility 
	double *weightmat;//Cost
	int *revarcmatrix;//[0]-right end;[0]-left ends
};
struct PATH
{
	double weight;
	vector<int> pathlist;
	bool used;
	int end;
};
struct SPATH
{
	double weight;//To store the weight of the path
	vector<int> pathlist;//To store the path
	vector<int> accessible_arcs;//To store the index of all the arcs accessible from the end node
	//The arcs shouldn't have been visited before that iteration 
	int end;//To store the right end node in forward dijkstra and left end node in reverse dijkstra
	double bestweight;//To store the best possible weight in future iteration
	int bestarc;//To store the arc with the best possible weight in future iteration
	int bestnode;//To store the other node in the arc with the best possible weight in future iteration
};
struct comparebyweight
{
	bool operator()(const PATH &a, const PATH &b) const
	{
		return (a.weight<b.weight);
	}
};
typedef struct GRAPH GRAPH;
typedef struct SPATH SPATH;
typedef struct PATH PATH;
typedef struct comparebyweight comparebyweight;
struct SPATHMAT
{
	vector<SPATH> pathmat;
};
struct PATHMAT
{
	vector<PATH> pathmat;
};
typedef struct PATHMAT PATHMAT;
typedef struct SPATHMAT SPATHMAT;
#pragma once
class kspath
{
public:
	bool cyclic(PATH);
	bool cyclic(PATH , bool *);
	bool same_path(PATH, PATH);
	PATH mergepath(PATH, PATH, double);
	PATH mergepath(SPATH, SPATH, double);
	PATHMAT bidijkstra(GRAPH, int , int, int );
};