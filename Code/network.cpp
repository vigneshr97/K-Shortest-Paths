#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <string>
#include <ctime>
#include <time.h>
#include <vector>
#include <algorithm>
#include "network.h"
#include "kspath.h"

void network::grid_net(int n)
{
	graph.nodes = n*n;
 	graph.arcs = 4*n*(n-1);
 	for (int i = 0; i < n*n; ++i)
 	{
 		int fstarsize = graph.fstarmatrix.size();
 		int rstarsize = graph.rstarmatrix.size();
 		graph.fstarposition.push_back(fstarsize);
 		graph.rstarposition.push_back(rstarsize);
 		if ((i-n)>=0)
 		{
 			graph.fstarmatrix.push_back(ARC());
 			fstarsize = graph.fstarmatrix.size();
 			graph.fstarmatrix[fstarsize-1].tail = i;
 			graph.fstarmatrix[fstarsize-1].head = i-n;
 			graph.fstarmatrix[fstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 			graph.rstarmatrix.push_back(ARC());
 			rstarsize = graph.rstarmatrix.size();
 			graph.rstarmatrix[rstarsize-1].tail = i;
 			graph.rstarmatrix[rstarsize-1].head = i-n;
 			graph.rstarmatrix[rstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 		}
 		if ((i+n)<n*n)
 		{
 			graph.fstarmatrix.push_back(ARC());
 			fstarsize = graph.fstarmatrix.size();
 			graph.fstarmatrix[fstarsize-1].tail = i;
 			graph.fstarmatrix[fstarsize-1].head = i+n;
 			graph.fstarmatrix[fstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 			graph.rstarmatrix.push_back(ARC());
 			rstarsize = graph.rstarmatrix.size();
 			graph.rstarmatrix[rstarsize-1].tail = i;
 			graph.rstarmatrix[rstarsize-1].head = i+n;
 			graph.rstarmatrix[rstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 		}
 		if ((i-1)>=0)
 		{
 			graph.fstarmatrix.push_back(ARC());
 			fstarsize = graph.fstarmatrix.size();
 			graph.fstarmatrix[fstarsize-1].tail = i;
 			graph.fstarmatrix[fstarsize-1].head = i-1;
 			graph.fstarmatrix[fstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 			graph.rstarmatrix.push_back(ARC());
 			rstarsize = graph.rstarmatrix.size();
 			graph.rstarmatrix[rstarsize-1].tail = i;
 			graph.rstarmatrix[rstarsize-1].head = i-1;
 			graph.rstarmatrix[rstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 		}
 		if ((i+1)<n*n)
 		{
 			graph.fstarmatrix.push_back(ARC());
 			fstarsize = graph.fstarmatrix.size();
 			graph.fstarmatrix[fstarsize-1].tail = i;
 			graph.fstarmatrix[fstarsize-1].head = i+1;
 			graph.fstarmatrix[fstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 			graph.rstarmatrix.push_back(ARC());
 			rstarsize = graph.rstarmatrix.size();
 			graph.rstarmatrix[rstarsize-1].tail = i;
 			graph.rstarmatrix[rstarsize-1].head = i+1;
 			graph.rstarmatrix[rstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 		}
 	}
}

void network::randomized_grid_net(int n)
{
	vector<int> a;
	for (int i = 0; i < n*n; ++i)
	{
		a.push_back(i);
	}
	random_shuffle(&a[0],&a[n*n]);
	graph.nodes = n*n;
 	graph.arcs = 4*n*(n-1);
 	for (int i = 0; i < n*n; ++i)
 	{
 		int fstarsize = graph.fstarmatrix.size();
 		int rstarsize = graph.rstarmatrix.size();
 		if ((i-n)>=0)
 		{
 			graph.fstarmatrix.push_back(ARC());
 			fstarsize = graph.fstarmatrix.size();
 			graph.fstarmatrix[fstarsize-1].tail = a[i];
 			graph.fstarmatrix[fstarsize-1].head = a[i-n];
 			graph.fstarmatrix[fstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 			graph.rstarmatrix.push_back(ARC());
 			rstarsize = graph.rstarmatrix.size();
 			graph.rstarmatrix[rstarsize-1].tail = a[i];
 			graph.rstarmatrix[rstarsize-1].head = a[i-n];
 			graph.rstarmatrix[rstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 		}
 		if ((i+n)<n*n)
 		{
 			graph.fstarmatrix.push_back(ARC());
 			fstarsize = graph.fstarmatrix.size();
 			graph.fstarmatrix[fstarsize-1].tail = a[i];
 			graph.fstarmatrix[fstarsize-1].head = a[i+n];
 			graph.fstarmatrix[fstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 			graph.rstarmatrix.push_back(ARC());
 			rstarsize = graph.rstarmatrix.size();
 			graph.rstarmatrix[rstarsize-1].tail = a[i];
 			graph.rstarmatrix[rstarsize-1].head = a[i+n];
 			graph.rstarmatrix[rstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 		}
 		if ((i-1)>=0)
 		{
 			graph.fstarmatrix.push_back(ARC());
 			fstarsize = graph.fstarmatrix.size();
 			graph.fstarmatrix[fstarsize-1].tail = a[i];
 			graph.fstarmatrix[fstarsize-1].head = a[i-1];
 			graph.fstarmatrix[fstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 			graph.rstarmatrix.push_back(ARC());
 			rstarsize = graph.rstarmatrix.size();
 			graph.rstarmatrix[rstarsize-1].tail = a[i];
 			graph.rstarmatrix[rstarsize-1].head = a[i-1];
 			graph.rstarmatrix[rstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 		}
 		if ((i+1)<n*n)
 		{
 			graph.fstarmatrix.push_back(ARC());
 			fstarsize = graph.fstarmatrix.size();
 			graph.fstarmatrix[fstarsize-1].tail = a[i];
 			graph.fstarmatrix[fstarsize-1].head = a[i+1];
 			graph.fstarmatrix[fstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 			graph.rstarmatrix.push_back(ARC());
 			rstarsize = graph.rstarmatrix.size();
 			graph.rstarmatrix[rstarsize-1].tail = a[i];
 			graph.rstarmatrix[rstarsize-1].head = a[i+1];
 			graph.rstarmatrix[rstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 		}
 	}
 	for (int i = 0; i < graph.nodes+1; ++i)
	{
		graph.fstarposition.push_back(0);
		graph.rstarposition.push_back(0);
	}
	sort(graph.fstarmatrix.begin(), graph.fstarmatrix.end(), forwardstar());
	sort(graph.rstarmatrix.begin(), graph.rstarmatrix.end(), reversestar());
	if (graph.fstarmatrix[0].tail!=0)
	{
		for (int i = 0; i < graph.fstarmatrix[0].tail; ++i)
		{
			graph.fstarposition[i] = 0;
		}
	}
	if (graph.fstarmatrix[0].head!=0)
	{
		for (int i = 0; i < graph.fstarmatrix[0].head; ++i)
		{
			graph.rstarposition[i] = 0;
		}
	}
	int x = 0;
	while(x < graph.arcs)
	{
		int i;
		int y = graph.fstarmatrix[x].tail;
		graph.fstarposition[y] = x;
		for (i = x; i < graph.arcs; ++i)
		{
			if (graph.fstarmatrix[i].tail==y)
			{
				continue;
			}
			else
			{
				if (graph.fstarmatrix[i].tail == y+1)
				{
					x = i;
					break;
				}
				else
				{
					for (int j = y+1; j < graph.fstarmatrix[i].tail; ++j)
					{
						graph.fstarposition[j] = i;
					}
					x = i;
					break;
				}
			}
		}
		x = i;
	}
	for (int i = graph.fstarmatrix[ graph.arcs - 1 ].tail + 1; i <= graph.nodes; ++i)
	{
		graph.fstarposition[i] = graph.arcs;
	}
	x = 0;
	while(x < graph.arcs)
	{
		int i;
		int y = graph.rstarmatrix[x].head;
		graph.rstarposition[y] = x;
		for (i = x; i < graph.arcs; ++i)
		{
			if (graph.rstarmatrix[i].head==y)
			{
				continue;
			}
			else
			{
				if (graph.rstarmatrix[i].head == y+1)
				{
					x = i;
					break;
				}
				else
				{
					for (int j = y+1; j < graph.rstarmatrix[i].head; ++j)
					{
						graph.rstarposition[j] = i;
					}
					x = i;
					break;
				}
			}
		}
		x = i;
	}
	for (int i = graph.rstarmatrix[ graph.arcs - 1 ].head + 1; i <= graph.nodes; ++i)
	{
		graph.rstarposition[i] = graph.arcs;
	}
}

void network::man_input_data()
{
	cout<<"Enter the number of nodes"<<endl;
	cin>>graph.nodes;
	cout<<"Enter the number of arcs"<<endl;
	cin>>graph.arcs;
	for (int i = 0; i < graph.nodes+1; ++i)
	{
		graph.fstarposition.push_back(0);
		graph.rstarposition.push_back(0);
	}
	cout << "Nodes: 1 to "<<graph.nodes<<"\nEnter the arcs (maximum value of weight:32766)\nFormat : origin destination weight\nE.g: 1 2 3 indicates arc from 1 to 2 whose cost is 3\n";
	for (int i = 0; i < graph.arcs; i++)
	{
		graph.fstarmatrix.push_back(ARC());
		graph.rstarmatrix.push_back(ARC());
		cin>>graph.fstarmatrix[i].tail>>graph.fstarmatrix[i].head>>graph.fstarmatrix[i].weight;
		graph.fstarmatrix[i].tail--;
		graph.fstarmatrix[i].head--;
		graph.rstarmatrix[i].tail = graph.fstarmatrix[i].tail;
		graph.rstarmatrix[i].head = graph.fstarmatrix[i].head;
		graph.rstarmatrix[i].weight = graph.fstarmatrix[i].weight;
	}
	sort(graph.fstarmatrix.begin(), graph.fstarmatrix.end(), forwardstar());
	sort(graph.rstarmatrix.begin(), graph.rstarmatrix.end(), reversestar());
	if (graph.fstarmatrix[0].tail!=0)
	{
		for (int i = 0; i < graph.fstarmatrix[0].tail; ++i)
		{
			graph.fstarposition[i] = 0;
		}
	}
	if (graph.fstarmatrix[0].head!=0)
	{
		for (int i = 0; i < graph.fstarmatrix[0].head; ++i)
		{
			graph.rstarposition[i] = 0;
		}
	}
	int x = 0;
	while(x < graph.arcs)
	{
		int i;
		int y = graph.fstarmatrix[x].tail;
		graph.fstarposition[y] = x;
		for (i = x; i < graph.arcs; ++i)
		{
			if (graph.fstarmatrix[i].tail==y)
			{
				continue;
			}
			else
			{
				if (graph.fstarmatrix[i].tail == y+1)
				{
					x = i;
					break;
				}
				else
				{
					for (int j = y+1; j < graph.fstarmatrix[i].tail; ++j)
					{
						graph.fstarposition[j] = i;
					}
					x = i;
					break;
				}
			}
		}
		x = i;
	}
	for (int i = graph.fstarmatrix[ graph.arcs - 1 ].tail + 1; i <= graph.nodes; ++i)
	{
		graph.fstarposition[i] = graph.arcs;
	}
	x = 0;
	while(x < graph.arcs)
	{
		int i;
		int y = graph.rstarmatrix[x].head;
		graph.rstarposition[y] = x;
		for (i = x; i < graph.arcs; ++i)
		{
			if (graph.rstarmatrix[i].head==y)
			{
				continue;
			}
			else
			{
				if (graph.rstarmatrix[i].head == y+1)
				{
					x = i;
					break;
				}
				else
				{
					for (int j = y+1; j < graph.rstarmatrix[i].head; ++j)
					{
						graph.rstarposition[j] = i;
					}
					x = i;
					break;
				}
			}
		}
		x = i;
	}
	for (int i = graph.rstarmatrix[ graph.arcs - 1 ].head + 1; i <= graph.nodes; ++i)
	{
		graph.rstarposition[i] = graph.arcs;
	}
}

void network::input_data()
{
	int i,j;
	cout<<"Enter the Network to be tested on (Type the number before the network):"<<endl<<"1: Anaheim\n"<<"2: Austin\n"<<"3: Barcelona\n"<<"4: Berlin-Center\n"<<"5: Berlin-Friedrichshain	\n"<<"6: Berlin-Mitte-Center	\n"<<"7: Berlin-Mitte-Prenzlauerberg-Friedrichshain-Center	\n"<<"8: Berlin-Prenzlauerberg-Center	\n"<<"9: Berlin-Tiergarten	\n"<<"10: Birmingham-England	\n"<<"11: Braess-Example	\n"<<"12: Chicago-Sketch	\n"<<"13: Eastern-Massachusetts	\n"<<"14: GoldCoast\n"<<"15: Hessen-Asymmetric	\n"<<"16: Philadelphia\n"<<"17: SiouxFalls	\n"<<"18: Sydney	\n"<<"19: Terrassa-Asymmetric	\n"<<"20: Winnipeg	\n"<<"21: Winnipeg-Asymmetric	\n"<<"22: chicago-regional\n";
	cin >> decider;
	switch(decider)
	{
		case 1:
		tntp="Networks/Anaheim_flow.tntp";
		break;
		case 2:
		tntp="Networks/Austin_net.tntp";
		break;
		case 3:
		tntp="Networks/Barcelona_net.tntp";
		break;
		case 4:
		tntp="Networks/berlin-center_net.tntp";
		break;
		case 5:
		tntp="Networks/friedrichshain-center_net.tntp";
		break;
		case 6:
		tntp="Networks/berlin-mitte-center_net.tntp";
		break;
		case 7:
		tntp="Networks/berlin-mitte-prenzlauerberg-friedrichshain-center_net.tntp";
		break;
		case 8:
		tntp="Networks/berlin-prenzlauerberg-center_net.tntp";
		break;
		case 9:
		tntp="Networks/berlin-tiergarten_net.tntp";
		break;
		case 10:
		tntp="Networks/Birmingham_Net.tntp";
		break;
		case 11:
		tntp="Networks/Braess_net.tntp";
		break;
		case 12:
		tntp="Networks/ChicagoSketch_net.tntp";
		break;
		case 13:
		tntp="Networks/EMA_net.tntp";
		break;
		case 14:
		tntp="Networks/Goldcoast_network_2016_01.tntp";
		break;
		case 15:
		tntp="Networks/Hessen-Asym_net.tntp";
		break;
		case 16:
		tntp="Networks/Philadelphia_net.tntp";
		break;
		case 17:
		tntp="Networks/SiouxFalls_net.tntp";
		break;
		case 18:
		tntp="Networks/Sydney_net.tntp";
		break;
		case 19:
		tntp="Networks/Terrassa-Asym_net.tntp";
		break;
		case 20:
		tntp="Networks/Winnipeg_net.tntp";
		break;
		case 21:
		tntp="Networks/Winnipeg-Asym_net.tntp";
		break;
		case 22:
		tntp="Networks/ChicagoRegional_net.tntp";
		break;
		default:
		cout<<"invalid";
	}
	ifstream in(tntp);
	if(!in) 
	{
	  cout << "Cannot open"<<tntp<< "file.\n";
	}
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> dummyf;
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> graph.nodes;
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> dummyf;
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> graph.arcs;
	for (int i = 0; i <= graph.nodes; ++i)
	{
		graph.fstarposition.push_back(0);
		graph.rstarposition.push_back(0);
	}
	for(i=0;i<3;i++)
	in>>dummyc[i];
	cout << "Nodes: "<<graph.nodes<<'\n'<<"Arcs: "<<graph.arcs<<'\n';
	for (i = 0; i < graph.arcs; i++)
	{
		graph.fstarmatrix.push_back(ARC());
		graph.rstarmatrix.push_back(ARC());
		in>>graph.fstarmatrix[i].tail>>graph.fstarmatrix[i].head>>capacity>>length>>freeflowtime>>B>>power>>speedlimit>>toll>>linktype>>dummyc[1];
		double flow = capacity/2;
		traveltime = freeflowtime*(1+B*pow((flow/capacity),power));
		graph.fstarmatrix[i].weight = traveltime + length + 0.1*toll;
		graph.fstarmatrix[i].tail--;
		graph.fstarmatrix[i].head--;
		graph.rstarmatrix[i].tail = graph.fstarmatrix[i].tail;
		graph.rstarmatrix[i].head = graph.fstarmatrix[i].head;
		graph.rstarmatrix[i].weight = graph.fstarmatrix[i].weight;
	}
	sort(graph.fstarmatrix.begin(), graph.fstarmatrix.end(), forwardstar());
	sort(graph.rstarmatrix.begin(), graph.rstarmatrix.end(), reversestar());
	if (graph.fstarmatrix[0].tail!=0)
	{
		for (int i = 0; i < graph.fstarmatrix[0].tail; ++i)
		{
			graph.fstarposition[i] = 0;
		}
	}
	if (graph.rstarmatrix[0].head!=0)
	{
		for (int i = 0; i < graph.rstarmatrix[0].head; ++i)
		{
			graph.rstarposition[i] = 0;
		}
	}
	int x = 0;
	while(x < graph.arcs)
	{
		int i;
		int y = graph.fstarmatrix[x].tail;
		graph.fstarposition[y] = x;
		for (i = x; i < graph.arcs; ++i)
		{
			if (graph.fstarmatrix[i].tail==y)
			{
				continue;
			}
			else
			{
				if (graph.fstarmatrix[i].tail == y+1)
				{
					x = i;
					break;
				}
				else
				{
					for (int j = y+1; j < graph.fstarmatrix[i].tail; ++j)
					{
						graph.fstarposition[j] = i;
					}
					x = i;
					break;
				}
			}
		}
		x = i;
	}
	for (int i = graph.fstarmatrix[ graph.arcs - 1 ].tail + 1; i <= graph.nodes; ++i)
	{
		graph.fstarposition[i] = graph.arcs;
	}
	x = 0;
	while(x < graph.arcs)
	{
		int i;
		int y = graph.rstarmatrix[x].head;
		graph.rstarposition[y] = x;
		for (i = x; i < graph.arcs; ++i)
		{
			if (graph.rstarmatrix[i].head==y)
			{
				continue;
			}
			else
			{
				if (graph.rstarmatrix[i].head == y+1)
				{
					x = i;
					break;
				}
				else
				{
					for (int j = y+1; j < graph.rstarmatrix[i].head; ++j)
					{
						graph.rstarposition[j] = i;
					}
					x = i;
					break;
				}
			}
		}
		x = i;
	}
	for (int i = graph.rstarmatrix[ graph.arcs - 1 ].head + 1; i <= graph.nodes; ++i)
	{
		graph.rstarposition[i] = graph.arcs;
	}
	graph.fstarposition[graph.nodes] = graph.arcs;
	graph.rstarposition[graph.nodes] = graph.arcs;
}

void network::output_data()
{
	ofstream output;
	srand(time(NULL));
	output.open("paths.txt");
	cout<<"enter the origin"<<endl;
	cin>>Origin;
	cout<<"enter the destination"<<endl;
	cin>>Destination;
	cout<<"enter the value of K"<<endl;
	cin>>K;
	int actual_K;
	PATHLIST P1 = kspath::S(graph, Origin, Destination, K);
	cout<<"1"<<endl;
	actual_K = P1.pathlist.size();
	PATHLIST P2 = kspath::S1(graph, Origin, Destination, K);
	cout<<"2"<<endl;
	PATHLIST P3 = kspath::S2(graph, Origin, Destination, K);
	cout<<"3"<<endl;
	PATHLIST P4 = kspath::S3(graph, Origin, Destination, K);
	cout<<"4"<<endl;
	for (int i = 0; i < actual_K; ++i)
	{
		output<<"S:"<<endl;
		output<<"Weight: "<<P1.pathlist[i].weight<<endl<<"Path: ";
		int psize = P1.pathlist[i].path.size();
		for (int j = 0; j < psize; ++j)
		{
			output<<P1.pathlist[i].path[j]<<" ";	
		}
		output<<endl;
		output<<"S1:"<<endl;
		output<<"Weight: "<<P2.pathlist[i].weight<<endl<<"Path: ";
		psize = P2.pathlist[i].path.size();
		for (int j = 0; j < psize; ++j)
		{
			output<<P2.pathlist[i].path[j]<<" ";	
		}
		output<<endl;
		output<<"S2:"<<endl;
		output<<"Weight: "<<P3.pathlist[i].weight<<endl<<"Path: ";
		psize = P3.pathlist[i].path.size();
		for (int j = 0; j < psize; ++j)
		{
			output<<P3.pathlist[i].path[j]<<" ";	
		}
		output<<endl;
		output<<"S3:"<<endl;
		output<<"Weight: "<<P4.pathlist[i].weight<<endl<<"Path: ";
		psize = P4.pathlist[i].path.size();
		for (int j = 0; j < psize; ++j)
		{
			output<<P4.pathlist[i].path[j]<<" ";	
		}
		output<<endl;
	}
}

void network::output_time_data()
{
	ofstream output;
	srand(time(NULL));
	output.open("time.csv");
	//int *source, *sink;
	int test_cases;
	cout<<"enter the number of od pairs to be tested on"<<endl;
	cin>>test_cases;
	//source = new int[test_cases];
	//sink = new int[test_cases];
	// for (int i = 0; i < test_cases; ++i)
	// {
	// 	source[i] = rand()%graph.nodes;
	// 	sink[i] = rand()%graph.nodes;
	// }
	//following is for 100*100 grid
	//int source[100] = {5083,9627,1695,2235,4054,615,1774,5851,5612,148,786,8490,7536,6857,3970,3458,3864,6215,5620,2123,9701,6212,5367,8365,4187,1035,6499,5149,7479,2524,4815,2858,8899,573,6085,9949,3761,6572,3840,3958,5824,8489,6909,4920,772,2247,7899,3865,3724,1712,9632,6187,334,8746,6459,3453,6746,5574,1310,7444,8405,4010,7384,7110,1510,9961,5415,2506,3762,7077,3657,9757,2991,418,7876,7625,3225,9554,2936,9362,7809,670,5902,3159,8304,8911,2947,775,6067,5479,8832,6649,637,8776,8235,9196,5374,5306,2779,1880};
	//int sink[100] = {2414,3339,9825,3693,999,1920,8394,4882,705,362,7294,1841,7336,4445,447,6926,8549,5938,5156,4192,3193,6812,638,4340,1306,3829,7274,4491,7930,2807,6343,6213,6240,9883,6828,9025,9337,9185,9315,9495,5523,2452,6961,7913,8837,6354,60,5573,5246,7531,3790,5694,4967,3704,8444,150,3109,1594,7609,2341,4081,8848,2579,3792,9997,7680,613,8322,9728,2535,574,3046,3144,2694,1938,9853,4641,3480,2210,4491,1062,6457,3368,2979,1788,9880,124,6617,2946,5505,1507,7599,3429,6874,2555,6915,7751,7146,4748,6128};
	//following is for 10*10 grid
	// int source[100], sink[100];
	// for (int i = 0; i < 100; ++i)
	// {
	// 	source[i] = i;
	// 	sink[i] = 99-i;
	// }
	//following is for 150*150 grid
	int source[100] = {4730,18973,21960,21176,5054,12694,20311,17325,21268,9475,20184,22037,13715,18808,4497,16503,18774,5795,17242,21328,13243,7032,19049,20602,22421,16958,4284,7513,11843,5115,4653,8521,11653,2881,14909,16195,5826,1365,16886,13996,1473,15279,13698,11851,1676,20731,14079,17048,15861,20491,2459,5557,22379,937,3498,9543,6079,478,17919,14944,19272,19910,17117,21110,17628,5751,9631,12642,15661,8264,18212,4173,9587,13968,14322,9465,20957,15578,20040,16844,12605,10454,7965,13573,19072,6721,347,17431,6776,9402,9286,11879,19847,9484,5458,1796,3162,4490,18492,7437};
	int sink[100] = {18047,2577,19427,9116,2091,13725,13063,6855,7531,16978,22099,16131,8811,13273,8203,1413,1268,20534,19233,10945,9460,16015,10570,4142,15090,22407,15985,11059,4421,1333,12458,9105,11128,11002,21483,10368,13738,10425,5063,3470,2368,3201,20161,7065,17625,4513,21054,2661,15175,18113,9630,15107,64,13177,1800,7203,3041,9057,3829,2998,16757,21566,18006,5004,15293,12564,12705,18633,6169,12742,7,7830,2034,8118,9684,16466,7420,18889,1472,20715,9046,17407,10673,5727,8766,12666,17767,562,8921,4326,5838,13466,434,9916,220,17685,9655,14473,2929,8659};
	output<<"K,S,S1,S2,S3,"<<endl;
	cout<<"The experiments will be run with the following inputs: The starting value of K, The step size for increment of K, The final value of K"<<endl;
	cout<<"enter starting value of K"<<endl;
	int start;
	cin>>start;
	cout<<"enter step size"<<endl;
	int step;
	cin>>step;
	cout<<"enter the largest value of K to be tested on"<<endl;
	cin>>K;
	double i1 = 0;
	double i2 = 0;
	double i3 = 0;
	double i4 = 0;
	
	for (int i = start; i <= K; i+=step)
	{
		i1 = 0;
		i2 = 0;
		i3 = 0;
		i4 = 0;
		for (int j = 0; j < test_cases; ++j)
		{
			double t1 = clock();
			kspath::S(graph, source[j], sink[j], i);
			cout<<"1"<<endl;
			double t2 = clock();
			PATHLIST P1 = kspath::S1(graph, source[j], sink[j], i);
			cout<<"2"<<endl;
			double t3 = clock();
			kspath::S2(graph, source[j], sink[j], i);
			cout<<"3"<<endl;
			double t4 = clock();
			kspath::S3(graph, source[j], sink[j], i);
			cout<<"4"<<endl;
			double t5 = clock();

			i1 =(t2-t1)/CLOCKS_PER_SEC;
			i2 =(t3-t2)/CLOCKS_PER_SEC;
			i3 =(t4-t3)/CLOCKS_PER_SEC;
			i4 =(t5-t4)/CLOCKS_PER_SEC;
			output<<i1<<','<<i2<<','<<i3<<','<<i4<<','<<endl;
			//output<<i2<<','<<P1.t<<endl;
		}
		i1/=test_cases;
		i2/=test_cases;
		i3/=test_cases;
		i4/=test_cases;
		//output<<i1<<','<<i2<<','<<i3<<','<<i4<<','<<endl;
	}
}