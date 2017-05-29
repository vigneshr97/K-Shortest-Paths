#pragma once
using namespace std;
class spath
{
public:
	double bidijkstra(int, int, int**, double*, int, int);
	double dijkstra(int, int, int**, double*, int, int);
	double reversedijkstra(int, int, int**, double*, int, int);
	void prims(int , int , int**, double*, int, int);
};