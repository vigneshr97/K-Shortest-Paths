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
	net.outputdata();
	return 0;
}
/*
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
Nodes:9 Arcs:14
1 2 4
1 3 8
2 4 8
2 3 11
3 5 7
3 6 1
4 5 2
4 7 7
4 8 4
5 6 6
6 8 2
7 8 14
7 9 9
8 9 10
*/