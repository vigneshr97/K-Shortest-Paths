#pragma once
#include <vector>
#include "kspath.h"
using namespace std;
class network : public kspath
{
public:
	GRAPH graph, subgraph;
	int Origin, Destination, K, mod;
	char dummyc[3][20];
	float dummyf;
	double capacity, length, freeflowtime, B, power, speedlimit, toll, linktype, traveltime;
	int decider;
	string tntp;
	bool reduced;
	vector<int> new_node;
	vector<int> old_node;
	void randomized_grid_net(int);
	void grid_net(int);
	void input_data();
	void man_input_data();
	void output_data();
	void output_time_data();
};