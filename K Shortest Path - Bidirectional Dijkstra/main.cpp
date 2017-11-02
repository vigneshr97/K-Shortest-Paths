#include <iostream>
#include "network.h"
#include "kspath.h"
using namespace std;
int main()
{
	int k;
	network net;
	//net.maninputdata();
	//net.inputdata();
	net.outputdata();
	return 0;
}
/*
give the following input by rewriting net.inputdata(); to net.maninputdata();
#1
Nodes:22 Arcs:38
1 2 12
1 3 9
1 4 7
1 10 14
2 5 5
2 6 6
3 7 10
4 7 6
4 10 7
4 11 10
5 8 6
5 9 10
6 9 9
6 10 6
7 11 4
7 12 3
8 15 6
9 15 12
9 16 15
10 13 8
10 16 6
11 13 13
11 14 9
12 14 10
12 18 17
13 20 11
14 17 8
14 18 5
15 19 9
16 19 7
16 20 6
17 20 15
17 21 3
17 22 5
18 21 6
19 22 13
20 22 12
21 22 4

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

#Nodes:7 Arcs:11
1 2 15
1 3 20
2 4 10
2 5 25
3 4 15
3 6 20
4 5 20
4 6 15
4 7 30
5 7 10
6 7 20
*/
