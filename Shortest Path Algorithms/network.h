#pragma once
#include "basic.h"
#include "spath.h"
#include "kspath.h"
using namespace std;
class network : public basic, public spath, public kspath
{
public:
	char dummyc[100][100];
	float dummyf;
	float dummyfl[100];
	double *weightmat;
	double *weightmatcopy;
	double t1, t2;
	double *dijtime, *revdijtime, *bidijtime, *primstime;
	int nodes,arcs,decider;
	int iterations;
	int *arcmatrix[4];
	int *arcmatrixcopy[4];
	int arcs_done = 0;
	int *distmatrix;
	int *temp;
	int *tempindex;
	string tntp;
	void inputdata();
	void maninputdata();
	void outputdata();
	void manoutputdata();
	void otdata();
};