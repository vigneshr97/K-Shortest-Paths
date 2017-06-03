#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <string>
#include "basic.h"
#include "spath.h"
#include "network.h"
#include "kspath.h"
void network::otdata()
{
	int i,j;
	double *distmatrix;
	distmatrix = new double[nodes];
	arcmatrixcopy[0] = new int[arcs];//To store the origin
	arcmatrixcopy[1] = new int[arcs];//To store the destination
	weightmatcopy = new double[arcs];//To store the weights
	arcmatrixcopy[3] = new int[arcs];//To store accessibility ( in case of bidirectional dijkstra it is for forward direction)
	for(i=0;i<arcs;i++)
	{
		arcmatrixcopy[0][i] = arcmatrix[0][i];
		arcmatrixcopy[1][i] = arcmatrix[1][i];
		weightmatcopy[i] = weightmat[i];
		arcmatrixcopy[3][i] = arcmatrix[3][i];
	}
	int **pathmatrin = new int*[nodes];
	for(i=0;i<nodes;i++)
	{
		pathmatrin[i] = new int[nodes];
	}
	int xstar = nodes-1;
	kspath::bidijkstra(nodes, arcs, arcmatrix,weightmat, 0, xstar);
	distmatrix[0] = kspath::minimum_dist;
	temp = new int[nodes];
	temp[0] = kspath::numarcs;
	for(i=0;i<=temp[0];i++)
		pathmatrin[0][i] = kspath::spathmat[i];
	cout<<distmatrix[0]<<' ';
	for(i=0;i<=temp[0];i++)
		cout<<pathmatrin[0][i]<<' ';
	cout<<endl;
	cout<<"no. of arcs: "<<temp[0]<<endl;
	tempindex = new int[kspath::numarcs];
	for(i=0;i<kspath::numarcs;i++)
	{
		tempindex[i] = kspath::arcindex[i];
	}
	int iter;
	int it = 0;
	for(iter=0;iter<temp[0];iter++)
	{
		kspath::numarcs = 0;
		for(j=0;j<arcs;j++)
		{
			arcmatrixcopy[0][j] = arcmatrix[0][j];
			arcmatrixcopy[1][j] = arcmatrix[1][j];
			weightmatcopy[j] = weightmat[j];
			arcmatrixcopy[3][j] = arcmatrix[3][j];
		}
		weightmatcopy[tempindex[iter]] = 32767;
		kspath::bidijkstra(nodes,arcs,arcmatrix,weightmatcopy,0,xstar);
		temp[it+1] = kspath::numarcs;
		distmatrix[it+1] = kspath::minimum_dist;
		for(j=0;j<=kspath::numarcs;j++)
			pathmatrin[it+1][j] = kspath::spathmat[j];
		for(j=0;j<=it;j++)
		{
			if((basic::same_mat(pathmatrin[it+1],pathmatrin[j],temp[it+1]+1,temp[j]+1))||(distmatrix[it+1]>32000))
				it--;
		}
		it++;
	}
	for(i=1;i<=it;i++)
	{
		cout<<distmatrix[i]<<' ';
		for(j=0;j<=temp[i];j++)
			cout<<pathmatrin[i][j]<<' ';
		cout<<endl;
		delete[] pathmatrin[i];
	}
}
void network::outputdata()
{
	int i,j;
	srand(time(NULL));
	int origin_mat[25];
	int destination_mat[25];
	iterations = 25;
	dijtime = new double[iterations];
	revdijtime = new double[iterations];
	bidijtime = new double[iterations];
	primstime = new double[iterations];
	for(i=0;i<iterations;i++)
	{
		origin_mat[i]=rand()%nodes;
		destination_mat[i]=rand()%nodes;
	}
	double x[25], y[25], z[25];
	for (i = 0; i < iterations; i++)
	{
		t1 = 0;
		t2 = 0;
		t1 = clock();
		x[i]=spath::dijkstra(nodes, arcs, arcmatrix,weightmat, origin_mat[i], destination_mat[i]);
		cout<<"\nDistance(dijkstra): "<<x[i];
		t2 = clock();
		dijtime[i] = (t2 - t1) / CLOCKS_PER_SEC;
	}
	cout << "\nMean Time (Dijkstra): " << basic::mean(dijtime,iterations)<<"\nStandard Deviation(Dijkstra): "<<basic::SD(dijtime,iterations);
	for (i = 0; i < iterations; i++)
	{
		t1 = 0;
		t2 = 0;
		t1 = clock();
		y[i]=spath::reversedijkstra(nodes, arcs, arcmatrix,weightmat, origin_mat[i], destination_mat[i]);
		cout << "\nDistance(Revdijkstra): " << y[i];
		t2 = clock();
		revdijtime[i] = (t2 - t1) / CLOCKS_PER_SEC;
	}
	cout << "\nMean Time (RevDijkstra): " << basic::mean(revdijtime, iterations) << "\nStandard Deviation(RevDijkstra): " << basic::SD(revdijtime, iterations);
	for (i = 0; i < iterations; i++)
	{
		t1 = 0;
		t2 = 0;
		t1 = clock();
		z[i]=spath::bidijkstra(nodes, arcs, arcmatrix,weightmat, origin_mat[i], destination_mat[i]);
		cout << "\nDistance(Bidijkstra): " << z[i];
		t2 = clock();
		bidijtime[i] = (t2 - t1) / CLOCKS_PER_SEC;
	}
	cout << "\nMean Time (BiDijkstra): " << basic::mean(bidijtime, iterations) << "\nStandard Deviation(BiDijkstra): " << basic::SD(bidijtime, iterations)<<endl;
	double success=0;
	for(i=0;i<iterations;i++)
	{
		if(((int)x[i]==(int)y[i])&&((int)z[i]==(int)y[i]))
		{
			success+=100/iterations;
		}
	}
	cout<<"SUCCESS PERCENTAGE: "<<success<<endl;
	/*for (i = 0; i < iterations; i++)
	{
		t1 = 0;
		t2 = 0;
		t1 = clock();
		spath::prims(nodes, arcs, arcmatrix,weightmat, origin_mat[i], destination_mat[i]);
		t2 = clock();
		primstime[i] = (t2 - t1) / CLOCKS_PER_SEC;
	}
	cout << "\nMean Time (Prims): " << basic::mean(primstime, iterations) << "\nStandard Deviation(Prims): " << basic::SD(primstime, iterations)<<endl;*/
}
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
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> nodes;
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> dummyf;
	in >> dummyc[0]>> dummyc[1]>> dummyc[2] >> arcs;
	for(i=0;i<3;i++)
	in>>dummyc[i];
	arcmatrix[0] = new int[arcs];//To store the origin
	arcmatrix[1] = new int[arcs];//To store the destination
	weightmat = new double[arcs];//To store the weights
	arcmatrix[3] = new int[arcs];//To store accessibility ( in case of bidirectional dijkstra it is for forward direction)
	cout << "Nodes: "<<nodes<<'\n'<<"Arcs: "<<arcs<<'\n';
	for (i = 0; i < arcs; i++)
	{
	  in>>arcmatrix[0][i]>>arcmatrix[1][i]>>dummyf>>weightmat[i]>>dummyfl[0]>>dummyfl[1]>>dummyfl[2]>>dummyfl[3]>>dummyfl[4]>>dummyfl[5]>>dummyc[1];
	}
	for(i=0;i<arcs;i++)
	{
		arcmatrix[0][i]--;
		arcmatrix[1][i]--;
	}
}
void network::maninputdata()
{
	int i,j;
	cout<<"Enter the number of nodes"<<endl;
	cin>>nodes;
	cout<<"Enter the number of arcs"<<endl;
	cin>>arcs;
	arcmatrix[0] = new int[arcs];//To store the origin
	arcmatrix[1] = new int[arcs];//To store the destination
	weightmat = new double[arcs];//To store the weights
	arcmatrix[3] = new int[arcs];//To store accessibility ( in case of bidirectional dijkstra it is for forward direction)
	cout << "Nodes: 1 to "<<nodes<<"\nEnter the arcs (maximum value of weight:32766)\nFormat : origin destination weight\nE.g: 1 2 3 indicates arc from 1 to 2 whose cost is 3\n";
	for (i = 0; i < arcs; i++)
		cin>>arcmatrix[0][i]>>arcmatrix[1][i]>>weightmat[i];
	for(i=0;i<arcs;i++)
	{
		arcmatrix[0][i]--;
		arcmatrix[1][i]--;
	}
}
void network::manoutputdata()
{
	int i,j;
	srand(time(NULL));
	int origin_mat[25];
	int destination_mat[25];
	iterations = 1;
	dijtime = new double[iterations];
	revdijtime = new double[iterations];
	bidijtime = new double[iterations];
	primstime = new double[iterations];
	for(i=0;i<iterations;i++)
	{
		//origin_mat[i]=rand()%nodes;
		//destination_mat[i]=rand()%nodes;
		origin_mat[i]=0;
		destination_mat[i]=nodes-1;
	}
	double x[25], y[25], z[25];
	for (i = 0; i < iterations; i++)
	{
		t1 = 0;
		t2 = 0;
		t1 = clock();
		x[i]=spath::dijkstra(nodes, arcs, arcmatrix,weightmat, origin_mat[i], destination_mat[i]);
		cout<<"\nDistance(dijkstra): "<<x[i];
		t2 = clock();
		dijtime[i] = (t2 - t1) / CLOCKS_PER_SEC;
	}
	cout << "\nMean Time (Dijkstra): " << basic::mean(dijtime,iterations)<<"\nStandard Deviation(Dijkstra): "<<basic::SD(dijtime,iterations);
	for (i = 0; i < iterations; i++)
	{
		t1 = 0;
		t2 = 0;
		t1 = clock();
		y[i]=spath::reversedijkstra(nodes, arcs, arcmatrix,weightmat, origin_mat[i], destination_mat[i]);
		cout << "\nDistance(Revdijkstra): " << y[i];
		t2 = clock();
		revdijtime[i] = (t2 - t1) / CLOCKS_PER_SEC;
	}
	cout << "\nMean Time (RevDijkstra): " << basic::mean(revdijtime, iterations) << "\nStandard Deviation(RevDijkstra): " << basic::SD(revdijtime, iterations);
	for (i = 0; i < iterations; i++)
	{
		t1 = 0;
		t2 = 0;
		t1 = clock();
		z[i]=spath::bidijkstra(nodes, arcs, arcmatrix,weightmat, origin_mat[i], destination_mat[i]);
		cout << "\nDistance(Bidijkstra): " << z[i];
		t2 = clock();
		bidijtime[i] = (t2 - t1) / CLOCKS_PER_SEC;
	}
	cout << "\nMean Time (BiDijkstra): " << basic::mean(bidijtime, iterations) << "\nStandard Deviation(BiDijkstra): " << basic::SD(bidijtime, iterations)<<endl;
	double success=0;
	for(i=0;i<iterations;i++)
	{
		if(((int)x[i]==(int)y[i])&&((int)z[i]==(int)y[i]))
		{
			success+=100/iterations;
		}
	}
	cout<<"SUCCESS PERCENTAGE: "<<success<<endl;
}