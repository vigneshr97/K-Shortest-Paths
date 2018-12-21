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
void network::outputdata()
{
	ofstream timevalue;
	ofstream time_n;
	ofstream time_yen;
	ofstream time_p;
	string timefile;
	time_n.open("time_comparison_k_100.csv");
	time_yen.open("yen_k_100.csv");
	time_p.open("proportion_100.csv");
	//timevalue.open("time.csv");
	int Origin, Destination, K;
	cout<<"Enter the greatest number of paths required"<<endl;
	cin>>K;
	//Origin = 0; 
	for (decider = 1; decider <= 22; ++decider)
	{
		switch(decider)
		{
			case 1:
			tntp="Networks/Anaheim_flow.tntp";
			timefile = "Time/time1.csv";
			break;
			case 2:
			tntp="Networks/Austin_net.tntp";
			timefile = "Time/time2.csv";
			break;
			case 3:
			tntp="Networks/Barcelona_net.tntp";
			timefile = "Time/time3.csv";
			break;
			case 4:
			tntp="Networks/berlin-center_net.tntp";
			timefile = "Time/time4.csv";
			break;
			case 5:
			tntp="Networks/friedrichshain-center_net.tntp";
			timefile = "Time/time5.csv";
			break;
			case 6:
			tntp="Networks/berlin-mitte-center_net.tntp";
			timefile = "Time/time6.csv";
			break;
			case 7:
			tntp="Networks/berlin-mitte-prenzlauerberg-friedrichshain-center_net.tntp";
			timefile = "Time/time7.csv";
			break;
			case 8:
			tntp="Networks/berlin-prenzlauerberg-center_net.tntp";
			timefile = "Time/time8.csv";
			break;
			case 9:
			tntp="Networks/berlin-tiergarten_net.tntp";
			timefile = "Time/time9.csv";
			break;
			case 10:
			tntp="Networks/Birmingham_Net.tntp";
			timefile = "Time/time10.csv";
			break;
			case 11:
			tntp="Networks/Braess_net.tntp";
			timefile = "Time/time11.csv";
			break;
			case 12:
			tntp="Networks/ChicagoSketch_net.tntp";
			timefile = "Time/time12.csv";
			break;
			case 13:
			tntp="Networks/EMA_net.tntp";
			timefile = "Time/time13.csv";
			break;
			case 14:
			tntp="Networks/Goldcoast_network_2016_01.tntp";
			timefile = "Time/time14.csv";
			break;
			case 15:
			tntp="Networks/Hessen-Asym_net.tntp";
			timefile = "Time/time15.csv";
			break;
			case 16:
			tntp="Networks/Philadelphia_net.tntp";
			timefile = "Time/time16.csv";
			break;
			case 17:
			tntp="Networks/SiouxFalls_net.tntp";
			timefile = "Time/time17.csv";
			break;
			case 18:
			tntp="Networks/Sydney_net.tntp";
			timefile = "Time/time18.csv";
			break;
			case 19:
			tntp="Networks/Terrassa-Asym_net.tntp";
			timefile = "Time/time19.csv";
			break;
			case 20:
			tntp="Networks/Winnipeg_net.tntp";
			timefile = "Time/time20.csv";
			break;
			case 21:
			tntp="Networks/Winnipeg-Asym_net.tntp";
			timefile = "Time/time21.csv";
			break;
			case 22:
			tntp="Networks/ChicagoRegional_net.tntp";
			timefile = "Time/time22.csv";
			break;
			default:
			cout<<"invalid";
		}
		cout<<"running "<<tntp<<endl;
		timevalue.open(timefile);
		ifstream in(tntp);
		if(!in) 
		{
		  cout << "Cannot open"<<tntp<< "file.\n";
		}
		in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> dummyf;
		in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> graph.nodes;
		in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> dummyf;
		in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> graph.arcs;
		//Destination = graph.nodes-1;
		for(int i=0;i<3;i++)
			in>>dummyc[i];
		graph.fstarmatrix = {};
		graph.fstar = {};
		for (int i = 0; i <= graph.nodes; ++i)
		{
			graph.fstar.push_back(0);
		}
		for (int i = 0; i < graph.arcs; i++)
		{
			graph.fstarmatrix.push_back(ARC());
			in>>graph.fstarmatrix[i].head>>graph.fstarmatrix[i].tail>>dummyf>>graph.fstarmatrix[i].weight>>dummyfl[0]>>dummyfl[1]>>dummyfl[2]>>dummyfl[3]>>dummyfl[4]>>dummyfl[5]>>dummyc[1];
			graph.fstarmatrix[i].head--;
			graph.fstarmatrix[i].tail--;
		}
		sort(graph.fstarmatrix.begin(), graph.fstarmatrix.end(), forwardstar());
		if (graph.fstarmatrix[0].head!=0)
		{
			for (int i = 0; i < graph.fstarmatrix[0].head; ++i)
			{
				graph.fstar[i] = 0;
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
		graph.fstar[graph.nodes] = graph.arcs;
		srand(time(NULL));
		vector<int> od1 = {};
		vector<int> od2 = {};
		for (int i = 0; i < 5; ++i)
		{
			od1.push_back(rand()%graph.nodes);
		}
		for (int i = 0; i < 5; ++i)
		{
			int x = rand()%graph.nodes;
			while((x==od1[0])||(x==od1[1])||(x==od1[2])||(x==od1[3])||(x==od1[4]))
			{
				x = rand()%graph.nodes;
			}
			od2.push_back(x);
		}
		for (int i = 1; i <= K; ++i)
		{
			double maxtime = 0;
			int maxpaths = 0;
			int od_1 = -1;
			int od_2 = -1;
			long int kn_max = 0;
			long int km_max = 0;
			long int KN_MAX = 0;
			long int KM_MAX = 0;
			for (int j = 0; j < 5; ++j)
			{
				Origin = od1[j];
				for (int k = 0; k < 5; ++k)
				{
					Destination = od2[k];
					double t1 = clock();
					cout<<"running Origin = "<<Origin<<" Destination = "<<Destination<<" K = "<<i<<endl;
					PATHMAT pathmatrix = kspath::dijkstra(graph,Origin,Destination,i);
					int paths_obtained = pathmatrix.pathmat.size();
					double t2 = clock();
					if ((t2-t1)/CLOCKS_PER_SEC>maxtime)
					{
						od_1 = Origin+1;
						od_2 = Destination+1;
						maxtime = (t2-t1)/CLOCKS_PER_SEC;
						maxpaths = pathmatrix.pathmat.size();
						kn_max = pathmatrix.kn;
						km_max = pathmatrix.km;
					}
				}
			}
			KN_MAX = maxpaths*graph.nodes;
			KM_MAX = maxpaths*graph.arcs;
			timevalue<<maxpaths<<','<<maxtime<<','<<od_1<<','<<od_2<<endl;
			if ((i==K)&&(maxpaths!=0))
			{
				double knratio = (double)kn_max/(double)KN_MAX;
				double kmratio = (double)km_max/(double)KM_MAX;
				time_n<<graph.nodes<<','<<graph.arcs<<','<<maxtime<<endl;
				time_p<<kn_max<<','<<KN_MAX<<','<<knratio<<','<<km_max<<','<<KM_MAX<<','<<kmratio<<endl;
			}
		}
		double t3 = clock();
		YENPATHMAT yenpathmatrix = kspath::yen(graph, Origin, Destination, K);
		double t4 = clock();
		time_yen<<graph.nodes<<','<<graph.arcs<<','<<(t4-t3)/CLOCKS_PER_SEC<<endl;
		timevalue.close();
	}
}