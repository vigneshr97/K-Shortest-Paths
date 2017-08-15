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
#include "basic.h"
#include "network.h"
#include "kspath.h"
void network::outputdata()
{
	int Origin, Destination, K;
	cout<<"Enter the Origin: ";
	cin>>Origin;
	Origin--;
	cout<<"Enter the Destination: ";
	cin>>Destination;
	Destination--;
	cout<<"Enter the number of paths required: ";
	cin>>K;
	srand(time(NULL));
	double t1 = clock();
	SPATHMAT pathmatrix = kspath::bidijkstra(graph, Origin, Destination, K);
	double t2 = clock();
	int psize = pathmatrix.pathmat.size();
	for (int i = 0; i < psize; ++i)
	{
		cout<<"Weight: "<<pathmatrix.pathmat[i].weight<<endl;
		int pathsize = pathmatrix.pathmat[i].pathlist.size();
		cout<<"PATH: ";
		for (int j = 0; j < pathsize-1; ++j)
		{
			cout<<pathmatrix.pathmat[i].pathlist[j]<<"-->";
		}
		cout<<pathmatrix.pathmat[i].pathlist[pathsize-1];
		cout<<endl;
	}
	cout<<"TIME CONSUMED:"<<(t2 - t1) / CLOCKS_PER_SEC<<endl<<endl<<endl<<endl;
	double t3 = clock();
	YENPATHMAT yenpathmatrix = kspath::yen(graph, Origin, Destination, K);
	double t4 = clock();
	int ysize = yenpathmatrix.pathmat.size();
	for (int i = 0; i < ysize; ++i)
	{
		cout<<"Weight: "<<yenpathmatrix.pathmat[i].weight<<endl;
		int pathsize = yenpathmatrix.pathmat[i].pathlist.size();
		cout<<"PATH: ";
		for (int j = 0; j < pathsize-1; ++j)
		{
			cout<<yenpathmatrix.pathmat[i].pathlist[j]<<"-->";
		}
		cout<<yenpathmatrix.pathmat[i].pathlist[pathsize-1];
		cout<<endl;
	}
	cout<<"TIME CONSUMED:"<<(t4 - t3) / CLOCKS_PER_SEC<<endl<<endl<<endl<<endl;
	for (int i = 0; i < ysize; ++i)
	{
		cout<<"Bidijkstra Weight: "<<pathmatrix.pathmat[i].weight<<" Yen's Weight: "<<yenpathmatrix.pathmat[i].weight<<endl;
		int pathsize = pathmatrix.pathmat[i].pathlist.size();
		cout<<"BPATH: ";
		for (int j = 0; j < pathsize-1; ++j)
		{
			cout<<pathmatrix.pathmat[i].pathlist[j]<<"-->";
		}
		cout<<pathmatrix.pathmat[i].pathlist[pathsize-1];
		cout<<endl;
		pathsize = yenpathmatrix.pathmat[i].pathlist.size();
		cout<<"YPATH: ";
		for (int j = 0; j < pathsize-1; ++j)
		{
			cout<<yenpathmatrix.pathmat[i].pathlist[j]<<"-->";
		}
		cout<<yenpathmatrix.pathmat[i].pathlist[pathsize-1];
		cout<<endl;
	}
	for (int i = ysize; i < psize; ++i)
	{
		cout<<"Bidijkstra Weight: "<<pathmatrix.pathmat[i].weight<<endl;
		int pathsize = pathmatrix.pathmat[i].pathlist.size();
		cout<<"BPATH: ";
		for (int j = 0; j < pathsize-1; ++j)
		{
			cout<<pathmatrix.pathmat[i].pathlist[j]<<"-->";
		}
		cout<<pathmatrix.pathmat[i].pathlist[pathsize-1];
		cout<<endl;
	}
}
//The following function reads the graph in a file and converts into a directed graph assuming topographical sorting
void network::inputdata()
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
	ofstream outputFile;
	string filename = "exampleOutput.csv";
	if(!in) 
	{
	  cout << "Cannot open"<<tntp<< "file.\n";
	}
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> dummyf;
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> graph.nodes;
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> dummyf;
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> graph.arcs;
	graph.fstar = new int [graph.nodes + 1];
	graph.rstar = new int [graph.nodes + 1];
	//for (int i = 0; i <= graph.nodes; ++i)
	//{
	//	graph.fstar.push_back(-1);
	//	graph.rstar.push_back(-1);
	//}
	for(i=0;i<3;i++)
	in>>dummyc[i];
	cout << "Nodes: "<<graph.nodes<<'\n'<<"Arcs: "<<graph.arcs<<'\n';
	outputFile.open(filename);
	outputFile << "A" << "," << "B" <<","<< "Weight" <<endl;
	for (i = 0; i < graph.arcs; i++)
	{
		graph.fstarmatrix.push_back(ARC());
		graph.rstarmatrix.push_back(ARC());
		in>>graph.fstarmatrix[i].head>>graph.fstarmatrix[i].tail>>dummyf>>graph.fstarmatrix[i].weight>>dummyfl[0]>>dummyfl[1]>>dummyfl[2]>>dummyfl[3]>>dummyfl[4]>>dummyfl[5]>>dummyc[1];
		outputFile<<graph.fstarmatrix[i].head<<","<<graph.fstarmatrix[i].tail<<","<<graph.fstarmatrix[i].weight<<endl;
		graph.fstarmatrix[i].head--;
		graph.fstarmatrix[i].tail--;
		graph.rstarmatrix[i].head = graph.fstarmatrix[i].head;
		graph.rstarmatrix[i].tail = graph.fstarmatrix[i].tail;
		graph.rstarmatrix[i].weight = graph.fstarmatrix[i].weight;
	}
	sort(graph.fstarmatrix.begin(), graph.fstarmatrix.end(), forwardstar());
	sort(graph.rstarmatrix.begin(), graph.rstarmatrix.end(), reversestar());
	if (graph.fstarmatrix[0].head!=0)
	{
		for (int i = 0; i < graph.fstarmatrix[0].head; ++i)
		{
			graph.fstar[i] = 0;
		}
	}
	if (graph.rstarmatrix[0].tail!=0)
	{
		for (int i = 0; i < graph.rstarmatrix[0].tail; ++i)
		{
			graph.rstar[i] = 0;
		}
	}
	int x = 0;
	while(x < graph.arcs)
	{
		int i;
		int y = graph.fstarmatrix[x].head;
		graph.fstar[y] = x;
		for (i = x; i < graph.arcs; ++i)
		{
			if (graph.fstarmatrix[i].head==y)
			{
				continue;
			}
			else
			{
				if (graph.fstarmatrix[i].head == y+1)
				{
					x = i;
					break;
				}
				else
				{
					for (int j = y+1; j < graph.fstarmatrix[i].head; ++j)
					{
						graph.fstar[j] = i;
					}
					x = i;
					break;
				}
			}
		}
		x = i;
	}
	for (int i = graph.fstarmatrix[ graph.arcs - 1 ].head + 1; i <= graph.nodes; ++i)
	{
		graph.fstar[i] = graph.arcs;
	}
	x = 0;
	while(x < graph.arcs)
	{
		int i;
		int y = graph.rstarmatrix[x].tail;
		graph.rstar[y] = x;
		for (i = x; i < graph.arcs; ++i)
		{
			if (graph.rstarmatrix[i].tail==y)
			{
				continue;
			}
			else
			{
				if (graph.rstarmatrix[i].tail == y+1)
				{
					x = i;
					break;
				}
				else
				{
					for (int j = y+1; j < graph.rstarmatrix[i].tail; ++j)
					{
						graph.rstar[j] = i;
					}
					x = i;
					break;
				}
			}
		}
		x = i;
	}
	for (int i = graph.rstarmatrix[ graph.arcs - 1 ].tail + 1; i <= graph.nodes; ++i)
	{
		graph.rstar[i] = graph.arcs;
	}
	graph.fstar[graph.nodes] = graph.arcs;
	graph.rstar[graph.nodes] = graph.arcs;
	/*cout<<"FSTARMATRIX:"<<endl;
	for (int i = 0; i < graph.arcs; ++i)
	{
		cout<<i<<' '<<graph.fstarmatrix[i].head<<' '<<graph.fstarmatrix[i].tail<<' '<<graph.fstarmatrix[i].weight<<endl;
	}
	cout<<"FSTAR:"<<endl;
	for (int i = 0; i <= graph.nodes; ++i)
	{
		cout<<i<<' '<<graph.fstar[i]<<endl;
	}
	cout<<"RSTARMATRIX:"<<endl;
	for (int i = 0; i < graph.arcs; ++i)
	{
		cout<<i<<' '<<graph.rstarmatrix[i].head<<' '<<graph.rstarmatrix[i].tail<<' '<<graph.rstarmatrix[i].weight<<endl;
	}
	cout<<"RSTAR:"<<endl;
	for (int i = 0; i <= graph.nodes; ++i)
	{
		cout<<i<<' '<<graph.rstar[i]<<endl;
	}*/
}
void network::maninputdata()
{
	cout<<"Enter the number of nodes"<<endl;
	cin>>graph.nodes;
	cout<<"Enter the number of arcs"<<endl;
	cin>>graph.arcs;
	graph.fstar = new int [graph.nodes + 1];
	graph.rstar = new int [graph.nodes + 1];
	cout << "Nodes: 1 to "<<graph.nodes<<"\nEnter the arcs (maximum value of weight:32766)\nFormat : origin destination weight\nE.g: 1 2 3 indicates arc from 1 to 2 whose cost is 3\n";
	for (int i = 0; i < graph.arcs; i++)
	{
		graph.fstarmatrix.push_back(ARC());
		graph.rstarmatrix.push_back(ARC());
		cin>>graph.fstarmatrix[i].head>>graph.fstarmatrix[i].tail>>graph.fstarmatrix[i].weight;
		graph.fstarmatrix[i].head--;
		graph.fstarmatrix[i].tail--;
		graph.rstarmatrix[i].head = graph.fstarmatrix[i].head;
		graph.rstarmatrix[i].tail = graph.fstarmatrix[i].tail;
		graph.rstarmatrix[i].weight = graph.fstarmatrix[i].weight;
	}
	sort(graph.fstarmatrix.begin(), graph.fstarmatrix.end(), forwardstar());
	sort(graph.rstarmatrix.begin(), graph.rstarmatrix.end(), reversestar());
	if (graph.fstarmatrix[0].head!=0)
	{
		for (int i = 0; i < graph.fstarmatrix[0].head; ++i)
		{
			graph.fstar[i] = 0;
		}
	}
	if (graph.fstarmatrix[0].tail!=0)
	{
		for (int i = 0; i < graph.fstarmatrix[0].tail; ++i)
		{
			graph.rstar[i] = 0;
		}
	}
	int x = 0;
	while(x < graph.arcs)
	{
		int i;
		int y = graph.fstarmatrix[x].head;
		graph.fstar[y] = x;
		for (i = x; i < graph.arcs; ++i)
		{
			if (graph.fstarmatrix[i].head==y)
			{
				continue;
			}
			else
			{
				if (graph.fstarmatrix[i].head == y+1)
				{
					x = i;
					break;
				}
				else
				{
					for (int j = y+1; j < graph.fstarmatrix[i].head; ++j)
					{
						graph.fstar[j] = i;
					}
					x = i;
					break;
				}
			}
		}
		x = i;
	}
	for (int i = graph.fstarmatrix[ graph.arcs - 1 ].head + 1; i <= graph.nodes; ++i)
	{
		graph.fstar[i] = graph.arcs;
	}
	x = 0;
	while(x < graph.arcs)
	{
		int i;
		int y = graph.rstarmatrix[x].tail;
		graph.rstar[y] = x;
		for (i = x; i < graph.arcs; ++i)
		{
			if (graph.rstarmatrix[i].tail==y)
			{
				continue;
			}
			else
			{
				if (graph.rstarmatrix[i].tail == y+1)
				{
					x = i;
					break;
				}
				else
				{
					for (int j = y+1; j < graph.rstarmatrix[i].tail; ++j)
					{
						graph.rstar[j] = i;
					}
					x = i;
					break;
				}
			}
		}
		x = i;
	}
	for (int i = graph.rstarmatrix[ graph.arcs - 1 ].tail + 1; i <= graph.nodes; ++i)
	{
		graph.rstar[i] = graph.arcs;
	}
	//graph.fstar[graph.nodes] = graph.arcs;
	//graph.rstar[graph.nodes] = graph.arcs;
	/*cout<<"FSTARMATRIX:"<<endl;
	for (int i = 0; i < graph.arcs; ++i)
	{
		cout<<i<<' '<<graph.fstarmatrix[i].head<<' '<<graph.fstarmatrix[i].tail<<' '<<graph.fstarmatrix[i].weight<<endl;
	}
	cout<<"FSTAR:"<<endl;
	for (int i = 0; i <= graph.nodes; ++i)
	{
		cout<<i<<' '<<graph.fstar[i]<<endl;
	}
	cout<<"RSTARMATRIX:"<<endl;
	for (int i = 0; i < graph.arcs; ++i)
	{
		cout<<i<<' '<<graph.rstarmatrix[i].head<<' '<<graph.rstarmatrix[i].tail<<' '<<graph.rstarmatrix[i].weight<<endl;
	}
	cout<<"RSTAR:"<<endl;
	for (int i = 0; i <= graph.nodes; ++i)
	{
		cout<<i<<' '<<graph.rstar[i]<<endl;
	}*/
}