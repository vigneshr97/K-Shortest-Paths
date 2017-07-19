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
#include "basic.h"
#include "network.h"
#include "kspath.h"
void network::otdata()
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
	PATHMAT pathmatrix = kspath::bidijkstra(graph, Origin, Destination, K);
	int size = pathmatrix.pathmat.size();
	for (int i = 0; i < size; ++i)
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
	if(!in) {
	  cout << "Cannot open"<<tntp<< "file.\n";
	}
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> dummyf;
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> graph.nodes;
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> dummyf;
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> graph.arcs;
	for(i=0;i<3;i++)
	in>>dummyc[i];

	graph.arcmatrix[0] = new int[graph.arcs];//To store the origin
	graph.arcmatrix[1] = new int[graph.arcs];//To store the destination
	graph.weightmat = new double[graph.arcs];//To store the weights
	graph.arcmatrix[2] = new int[graph.arcs];//To store accessibility ( in case of bidirectional dijkstra it is for forward direction)
	graph.revarcmatrix = new int[graph.arcs];
	cout << "Nodes: "<<graph.nodes<<'\n'<<"Arcs: "<<graph.arcs<<'\n';
	for (i = 0; i < graph.arcs; i++)
	{
	  in>>graph.arcmatrix[0][i]>>graph.arcmatrix[1][i]>>dummyf>>graph.weightmat[i]>>dummyfl[0]>>dummyfl[1]>>dummyfl[2]>>dummyfl[3]>>dummyfl[4]>>dummyfl[5]>>dummyc[1];
	}
	for(i=0;i<graph.arcs;i++)
	{
		graph.arcmatrix[0][i]--;
		graph.arcmatrix[1][i]--;
	}
}
void network::maninputdata()
{
	int i,j;
	cout<<"Enter the number of nodes"<<endl;
	cin>>graph.nodes;
	cout<<"Enter the number of arcs"<<endl;
	cin>>graph.arcs;
	graph.arcmatrix[0] = new int[graph.arcs];//To store the origin
	graph.arcmatrix[1] = new int[graph.arcs];//To store the destination
	graph.weightmat = new double[graph.arcs];//To store the weights
	graph.arcmatrix[2] = new int[graph.arcs];//To store accessibility ( in case of bidirectional dijkstra it is for forward direction)
	graph.revarcmatrix = new int[graph.arcs];
	cout << "Nodes: 1 to "<<graph.nodes<<"\nEnter thearcs (maximum value of weight:32766)\nFormat : origin destination weight\nE.g: 1 2 3 indicates arc from 1 to 2 whose cost is 3\n";
	for (i = 0; i < graph.arcs; i++)
		cin>>graph.arcmatrix[0][i]>>graph.arcmatrix[1][i]>>graph.weightmat[i];
	for(i=0;i<graph.arcs;i++)
	{
		graph.arcmatrix[0][i]--;
		graph.arcmatrix[1][i]--;
	}
}