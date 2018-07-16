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
 			graph.rstarmatrix[rstarsize-1].tail = i-n;
 			graph.rstarmatrix[rstarsize-1].head = i;
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
 			graph.rstarmatrix[rstarsize-1].tail = i+n;
 			graph.rstarmatrix[rstarsize-1].head = i;
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
 			graph.rstarmatrix[rstarsize-1].tail = i-1;
 			graph.rstarmatrix[rstarsize-1].head = i;
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
 			graph.rstarmatrix[rstarsize-1].tail = i+1;
 			graph.rstarmatrix[rstarsize-1].head = i;
 			graph.rstarmatrix[rstarsize-1].weight = (rand()%(10*graph.arcs))/(graph.arcs/100);
 		}
 	}
 	cout<<"Enter the number of paths required: ";
	cin>>K;
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
	cout<<"Enter the Origin: ";
	cin>>Origin;
	Origin--;
	cout<<"Enter the Destination: ";
	cin>>Destination;
	Destination--;
	cout<<"Enter the number of paths required: ";
	cin>>K;
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

// void network::input()
// {
// 	cout<<"Enter the Network to be tested on (Type the number before the network):"<<endl<<"1: Anaheim\n"<<"2: Austin\n"<<"3: Barcelona\n"<<"4: Berlin-Center\n"<<"5: Berlin-Friedrichshain	\n"<<"6: Berlin-Mitte-Center	\n"<<"7: Berlin-Mitte-Prenzlauerberg-Friedrichshain-Center	\n"<<"8: Berlin-Prenzlauerberg-Center	\n"<<"9: Berlin-Tiergarten	\n"<<"10: Birmingham-England	\n"<<"11: Braess-Example	\n"<<"12: Chicago-Sketch	\n"<<"13: Eastern-Massachusetts	\n"<<"14: GoldCoast\n"<<"15: Hessen-Asymmetric	\n"<<"16: Philadelphia\n"<<"17: SiouxFalls	\n"<<"18: Sydney	\n"<<"19: Terrassa-Asymmetric	\n"<<"20: Winnipeg	\n"<<"21: Winnipeg-Asymmetric	\n"<<"22: chicago-regional\n";
// 	cin >> decider;
// 	switch(decider)
// 	{
// 		case 1:
// 		tntp="nydata";
// 		break;
// 		default:
// 		cout<<"invalid";
// 	}
// 	ifstream in(tntp);
// 	if(!in) 
// 	{
// 	  cout << "Cannot open"<<tntp<< "file.\n";
// 	}
// 	in >> graph.nodes;
// 	in >> graph.arcs;
// 	for (int i = 0; i <= graph.nodes; ++i)
// 	{
// 		graph.fstarposition.push_back(0);
// 		graph.rstarposition.push_back(0);
// 	}
// 	cout << "Nodes: "<<graph.nodes<<'\n'<<"Arcs: "<<graph.arcs<<'\n';
// 	for (i = 0; i < graph.arcs; i++)
// 	{
// 		graph.fstarmatrix.push_back(ARC());
// 		graph.rstarmatrix.push_back(ARC());
// 		in>>graph.fstarmatrix[2*i].tail>>graph.fstarmatrix[2*i].head;
// 		graph.fstarmatrix.push_back(ARC());
// 		graph.rstarmatrix.push_back(ARC());
// 		graph.fstarmatrix[2*i+1].tail = graph.fstarmatrix[2*i].head;
// 		graph.fstarmatrix[2*i+1].head = graph.fstarmatrix[2*i].tail;
// 		in>>traveltime>>length>>B;
// 		graph.fstarmatrix[i].weight = traveltime/2.5 + length;
// 		graph.rstarmatrix[i].tail = graph.fstarmatrix[i].tail;
// 		graph.rstarmatrix[i].head = graph.fstarmatrix[i].head;
// 		graph.rstarmatrix[i].weight = graph.fstarmatrix[i].weight;
// 	}
// 	graph.arcs *= 2;
// 	sort(graph.fstarmatrix.begin(), graph.fstarmatrix.end(), forwardstar());
// 	sort(graph.rstarmatrix.begin(), graph.rstarmatrix.end(), reversestar());
// 	if (graph.fstarmatrix[0].tail!=0)
// 	{
// 		for (int i = 0; i < graph.fstarmatrix[0].tail; ++i)
// 		{
// 			graph.fstarposition[i] = 0;
// 		}
// 	}
// 	if (graph.rstarmatrix[0].head!=0)
// 	{
// 		for (int i = 0; i < graph.rstarmatrix[0].head; ++i)
// 		{
// 			graph.rstarposition[i] = 0;
// 		}
// 	}
// 	int x = 0;
// 	while(x < graph.arcs)
// 	{
// 		int i;
// 		int y = graph.fstarmatrix[x].tail;
// 		graph.fstarposition[y] = x;
// 		for (i = x; i < graph.arcs; ++i)
// 		{
// 			if (graph.fstarmatrix[i].tail==y)
// 			{
// 				continue;
// 			}
// 			else
// 			{
// 				if (graph.fstarmatrix[i].tail == y+1)
// 				{
// 					x = i;
// 					break;
// 				}
// 				else
// 				{
// 					for (int j = y+1; j < graph.fstarmatrix[i].tail; ++j)
// 					{
// 						graph.fstarposition[j] = i;
// 					}
// 					x = i;
// 					break;
// 				}
// 			}
// 		}
// 		x = i;
// 	}
// 	for (int i = graph.fstarmatrix[ graph.arcs - 1 ].tail + 1; i <= graph.nodes; ++i)
// 	{
// 		graph.fstarposition[i] = graph.arcs;
// 	}
// 	x = 0;
// 	while(x < graph.arcs)
// 	{
// 		int i;
// 		int y = graph.rstarmatrix[x].head;
// 		graph.rstarposition[y] = x;
// 		for (i = x; i < graph.arcs; ++i)
// 		{
// 			if (graph.rstarmatrix[i].head==y)
// 			{
// 				continue;
// 			}
// 			else
// 			{
// 				if (graph.rstarmatrix[i].head == y+1)
// 				{
// 					x = i;
// 					break;
// 				}
// 				else
// 				{
// 					for (int j = y+1; j < graph.rstarmatrix[i].head; ++j)
// 					{
// 						graph.rstarposition[j] = i;
// 					}
// 					x = i;
// 					break;
// 				}
// 			}
// 		}
// 		x = i;
// 	}
// 	for (int i = graph.rstarmatrix[ graph.arcs - 1 ].head + 1; i <= graph.nodes; ++i)
// 	{
// 		graph.rstarposition[i] = graph.arcs;
// 	}
// 	graph.fstarposition[graph.nodes] = graph.arcs;
// 	graph.rstarposition[graph.nodes] = graph.arcs;	
// }

GRAPH network::reduce_graph(GRAPH& maingraph, int source, int sink, int k, vector<int>& new_node, vector<int>& old_node)
{
	GRAPH subgraph;
	PATHLIST P;
	vector<int> fheap, bheap;
	vector<BESTPATH> n;
	int fheapsize, bheapsize;
	vector<bool> visited;

	for (int i = 0; i < maingraph.nodes; ++i)
	{
		n.push_back(BESTPATH());
		n[i].fweight = 32767;
		n[i].bweight = 32767;
		n[i].fposition = -1;
		n[i].bposition = -1; 
		n[i].nodeindex = i;
		visited.push_back(0);
	}

	fheap.push_back(source);
	n[source].fpath = {source};
	n[source].fweight = 0;
	n[source].fposition = 0;

	bheap.push_back(sink);
	n[sink].bpath = {sink};
	n[sink].bweight = 0;
	n[sink].bposition = 0;

	fheapsize = fheap.size();
	bheapsize = bheap.size();

	while(fheapsize>0)
	{
		int root = fheap[0];
		n[fheap[fheapsize-1]].fposition = 0;
		swap(fheap[0],fheap[fheapsize-1]);
		n[root].fposition = -1;
		fheap.pop_back();
		fheapsize = fheap.size();
		if (fheapsize==2)
		{
			if (n[fheap[0]].fweight>n[fheap[1]].fweight)
			{
				swap(fheap[0],fheap[1]);
				swap(n[fheap[0]].fposition,n[fheap[1]].fposition);
			}
		}
		if (fheapsize>2)
		{
			kspath::heapify(fheap,fheapsize,0,n,1);
		}
		for (int i = maingraph.fstarposition[root]; i < maingraph.fstarposition[root+1]; ++i)
		{
			if (maingraph.fstarmatrix[i].weight>32000)
			{
				continue;
			}
			if (n[root].fweight+maingraph.fstarmatrix[i].weight < n[maingraph.fstarmatrix[i].head].fweight)
			{
				n[maingraph.fstarmatrix[i].head].fweight = n[root].fweight + maingraph.fstarmatrix[i].weight;
				n[maingraph.fstarmatrix[i].head].fpath = n[root].fpath;
				n[maingraph.fstarmatrix[i].head].fpath.push_back(maingraph.fstarmatrix[i].head);
				if (n[maingraph.fstarmatrix[i].head].fposition==-1)
				{
					fheap.push_back(maingraph.fstarmatrix[i].head);
					fheapsize = fheap.size();
					n[maingraph.fstarmatrix[i].head].fposition = fheapsize-1;  
					for (int j = fheapsize-1; j > 0 ; j=(j-1)/2)
					{
						if (n[fheap[j]].fweight<n[fheap[(j-1)/2]].fweight)
						{
							swap(fheap[j],fheap[(j-1)/2]);
							swap(n[fheap[j]].fposition,n[fheap[(j-1)/2]].fposition);
						}
					}
				}
				else
				{
					int headposition = n[maingraph.fstarmatrix[i].head].fposition;
					for (int j = headposition; j > 0; j=(j-1)/2)
					{
						if (n[fheap[j]].fweight<n[fheap[(j-1)/2]].fweight)
						{
							swap(fheap[j],fheap[(j-1)/2]);
							swap(n[fheap[j]].fposition,n[fheap[(j-1)/2]].fposition);
						}
					}
				}
			}
		}
		fheapsize = fheap.size();
	}
	while(bheapsize>0)
	{
		int root = bheap[0];
		
		n[bheap[bheapsize-1]].bposition = 0;
		swap(bheap[0],bheap[bheapsize-1]);
		n[root].bposition = -1;

		bheap.pop_back();
		bheapsize = bheap.size();
		if (bheapsize==2)
		{
			if (n[bheap[0]].bweight>n[bheap[1]].bweight)
			{
				swap(bheap[0],bheap[1]);
				swap(n[bheap[0]].bposition,n[bheap[1]].bposition);
			}
		}
		if (bheapsize>2)
		{
			kspath::heapify(bheap,bheapsize,0,n,0);
		}
		for (int i = maingraph.rstarposition[root]; i < maingraph.rstarposition[root+1]; ++i)
		{
			if (maingraph.rstarmatrix[i].weight>32000)
			{
				continue;
			}
			if (n[root].bweight+maingraph.rstarmatrix[i].weight < n[maingraph.rstarmatrix[i].tail].bweight)
			{
				n[maingraph.rstarmatrix[i].tail].bweight = n[root].bweight + maingraph.rstarmatrix[i].weight;
				n[maingraph.rstarmatrix[i].tail].bpath = n[root].bpath;
				n[maingraph.rstarmatrix[i].tail].bpath.push_back(maingraph.rstarmatrix[i].tail);
				if (n[maingraph.rstarmatrix[i].tail].bposition==-1)
				{
					bheap.push_back(maingraph.rstarmatrix[i].tail);
					bheapsize = bheap.size();
					n[maingraph.rstarmatrix[i].tail].bposition = bheapsize-1;  
					for (int j = bheapsize-1; j > 0 ; j=(j-1)/2)
					{
						if (n[bheap[j]].bweight<n[bheap[(j-1)/2]].bweight)
						{
							swap(bheap[j],bheap[(j-1)/2]);
							swap(n[bheap[j]].bposition,n[bheap[(j-1)/2]].bposition);
						}
					}
				}
				else
				{
					int headposition = n[maingraph.rstarmatrix[i].tail].bposition;
					for (int j = headposition; j > 0; j=(j-1)/2)
					{
						if (n[bheap[j]].bweight<n[bheap[(j-1)/2]].bweight)
						{
							swap(bheap[j],bheap[(j-1)/2]);
							swap(n[bheap[j]].bposition,n[bheap[(j-1)/2]].bposition);
						}
					}
				}
			}
		}
		bheapsize = bheap.size();
	}
	sort(n.begin(), n.end(),bestweightsort());
	ofstream best;
	best.open("best.txt");
	
	int bestpaths = 0;
	vector<int> path_index;
	bool repeated = 0;
	ofstream bestpath;
	bestpath.open("bestpath.txt");	
	for (int i = 0; i < maingraph.nodes; ++i)
	{
		if (bestpaths>=k)
		{
			break;
		}
		if (kspath::acyclic(n[i],maingraph.nodes))
		{
			int pathindexsize = path_index.size();
			repeated = 0;
			for (int j = pathindexsize-1; j >= 0 ; --j)
			{
				if (kspath::same_path(n[i],n[path_index[j]]))
				{
					repeated = 1;
					break;
				}
			}	
			if (repeated==0)
			{
				bestpaths+=1;
				path_index.push_back(i);
			}
		}
	}
	if (bestpaths<k)
	{
		reduced = 0;
		return subgraph;
	}
	for (int i = 0; i < k; ++i)
	{
		int pathsize = n[path_index[i]].fpath.size();
		for (int j = 0; j < pathsize; ++j)
		{
			visited[n[path_index[i]].fpath[j]] = 1;
		}
		pathsize = n[path_index[i]].bpath.size();
		for (int j = 0; j < pathsize; ++j)
		{
			visited[n[path_index[i]].bpath[j]] = 1;
		}
	}

	subgraph.nodes = 0;
	subgraph.arcs = 0;
	int nodes = 0;

	for (int i = 0; i < graph.nodes; ++i)
	{
		if (visited[i])
		{
			old_node.push_back(i);
			new_node.push_back(subgraph.nodes);
			subgraph.nodes+=1;
			nodes+=1;
		}
		else
		{
			new_node.push_back(-1);
		}
	}
	for (int i = 0; i <= graph.nodes; ++i)
	{
		subgraph.fstarposition.push_back(0);
		subgraph.rstarposition.push_back(0);
	}
	
	subgraph.fstarposition[0] = 0;
	subgraph.rstarposition[0] = 0;
	int arcs = 0;
	int prev_node = 0;
	subgraph.fstarmatrix = {};
	subgraph.rstarmatrix = {};
	for (int i = 0; i < maingraph.arcs; ++i)
	{
		if ((visited[maingraph.fstarmatrix[i].tail])&&(visited[maingraph.fstarmatrix[i].head]))
		{
			subgraph.fstarmatrix.push_back(ARC());
			subgraph.fstarmatrix[arcs].tail = new_node[maingraph.fstarmatrix[i].tail];
			subgraph.fstarmatrix[arcs].head = new_node[maingraph.fstarmatrix[i].head];
			subgraph.fstarmatrix[arcs].weight = maingraph.fstarmatrix[i].weight;
			int tail = subgraph.fstarmatrix[arcs].tail;
			if (tail!=prev_node)
			{
				prev_node = tail;
				subgraph.fstarposition[tail] = arcs;
			}
			arcs+=1;
			subgraph.arcs+=1;
		}
	}
	arcs = 0;
	prev_node = 0;
	for (int i = 0; i < maingraph.arcs; ++i)
	{
		if ((visited[maingraph.rstarmatrix[i].tail])&&(visited[maingraph.rstarmatrix[i].head]))
		{
			subgraph.rstarmatrix.push_back(ARC());
			subgraph.rstarmatrix[arcs].tail = new_node[maingraph.rstarmatrix[i].tail];
			subgraph.rstarmatrix[arcs].head = new_node[maingraph.rstarmatrix[i].head];
			subgraph.rstarmatrix[arcs].weight = maingraph.rstarmatrix[i].weight;
			int head = subgraph.rstarmatrix[arcs].head;
			if (head!=prev_node)
			{
				prev_node = head;
				subgraph.rstarposition[head] = arcs;
			}
			arcs+=1;
		}
	}
	subgraph.fstarposition[nodes] = subgraph.arcs;
	subgraph.rstarposition[nodes] = subgraph.arcs;
	int outsize1 = subgraph.fstarmatrix.size();
	int outsize2 = subgraph.rstarmatrix.size();
	return subgraph;
}

void network::output_data()
{
	ofstream output;
	srand(time(NULL));
	ofstream time_out;
	output.open("values.csv");
	// cout<<"Enter the Origin: ";
	// cin>>Origin;
	// Origin--;
	// cout<<"Enter the Destination: ";
	// cin>>Destination;
	// Destination--;
	// cout<<"Enter the number of paths required: ";
	// cin>>K;
	int source[25], sink[25];
	for (int i = 0; i < 25; ++i)
	{
		source[i] = rand()%graph.nodes;
		sink[i] = rand()%graph.nodes;
	}
	cout<<"enter starting value of K"<<endl;
	int start;
	cin>>start;
	cout<<"enter step size"<<endl;
	int step;
	cin>>step;
	double i1 = 0;
	double i2 = 0;
	double i3 = 0;
	double i4 = 0;
	double i5 = 0;
	double i6 = 0;
	int steps_taken = 0;
	for (int i = start; i <= K; i+=step)
	{
		i1 = 0;
		i2 = 0;
		i3 = 0;
		i4 = 0;
		i5 = 0;
		i6 = 0;
		for (int j = 0; j < 5; ++j)
		{
			double t1 = clock();
			kspath::ksp_single(graph, source[j], sink[j], i);
			cout<<"1"<<endl;
			double t2 = clock();
			kspath::ksp_single1(graph, source[j], sink[j], i);
			cout<<"2"<<endl;
			double t3 = clock();
			kspath::ksp_single2(graph, source[j], sink[j], i);
			cout<<"3"<<endl;
			double t4 = clock();
			kspath::ksp_single12(graph, source[j], sink[j], i);
			cout<<"4"<<endl;
			double t5 = clock();
			// vector<int> new_node;
			// vector<int> old_node;
			// reduced = 1;
			// GRAPH subgraph = reduce_graph(graph, source[j], sink[j], i, new_node, old_node);
			// cout<<"reduced"<<endl;
			// if (reduced)
			// {
			// 	cout<<new_node[source[j]]<<' '<<new_node[sink[j]]<<' '<<subgraph.nodes<<endl;
			// 	kspath::ksp_bidirectional(subgraph, new_node[source[j]], new_node[sink[j]], i);
			// }
			// else
			// {
			// 	kspath::ksp_bidirectional(graph, source[j], sink[j], i);
			// }
			// cout<<"5"<<endl;
			// double t6 = clock();
			// kspath::yen(graph, source[j], sink[j], i);
			// cout<<"6"<<endl;
			// double t7 = clock();

			i1+=(t2-t1)/CLOCKS_PER_SEC;
			i2+=(t3-t2)/CLOCKS_PER_SEC;
			i3+=(t4-t3)/CLOCKS_PER_SEC;
			i4+=(t5-t4)/CLOCKS_PER_SEC;
			//i5+=(t6-t5)/CLOCKS_PER_SEC;
			//i6+=(t7-t6)/CLOCKS_PER_SEC;
		}
		i1/=5;
		i2/=5;
		i3/=5;
		i4/=5;
		//i5/=5;
		//i6/=5;
		output<<i1<<','<<i2<<','<<i3<<','<<i4<<','<<endl;
	}
}