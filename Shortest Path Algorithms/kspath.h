#pragma once
using namespace std;
class kspath
{
public:
	int *spathmat;
	int *arcindex;
	int numarcs;
	double minimum_dist;
	void bidijkstra(int , int, int **, double *, int , int );
};