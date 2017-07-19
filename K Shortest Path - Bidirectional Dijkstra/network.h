#pragma once
#include "basic.h"
#include "kspath.h"
using namespace std;
class network : public basic, public kspath
{
public:
	GRAPH graph;
	char dummyc[100][100];
	float dummyf;
	float dummyfl[100];
	double t1, t2;
	int decider;
	int iterations;
	int arcs_done = 0;
	int num_operating = 1;
	string tntp;
	void inputdata();
	void maninputdata();
	void otdata();
};