#include <iostream>
#include "basic.h"
#include "network.h"
#include "kspath.h"
using namespace std;
int main()
{
	int k;
	network net;
	//net.maninputdata();
	net.inputdata();
	net.otdata();
	return 0;
}
/*
uncomment net.output data and comment net.otdata to see the computational time comparisons of SP algorithms
uncomment net.otdata and comment net.outputdata to see the successive shortest paths
give the following input by rewriting net.inputdata(); to net.maninputdata();
#1
Nodes:7 Arcs:11
1 2 15
1 3 20
2 4 10
3 4 15
2 5 25
4 5 20
3 6 20
4 6 15
4 7 30
5 7 10
6 7 20

#2
Nodes:9 Arcs:13
1 2 5
1 3 10
1 4 15
3 4 20
3 5 5
2 5 15
2 6 10
4 6 10
6 8 15
5 8 10
5 7 20
7 9 10
8 9 5
*/