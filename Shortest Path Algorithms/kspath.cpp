#include <iostream>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <string>
#include "kspath.h"
using namespace std;
void kspath::bidijkstra(int nodes, int arcs, int **arcmatrix, double *weightmat, int Origin, int Destination)
{
	//cout<<"entered bidijkstra"<<endl;
	spathmat = new int [nodes];
	arcindex = new int [nodes];
	//cout<<"sizeof(spathmat): "<<sizeof(*spathmat)<<endl;
	int s,minindex,i,j,k,l,*duplicate[5],*visited[2],breakingvar,mindistindex,sf,sb;
	double minvalue,*dupweightmat,*dupupdweightmat,*distancef,*distanceb,*distancethrough,mindistance;
	breakingvar = 0;
	int *revarcmatrix[4];
	//cout<<"CP1 "<<sizeof(revarcmatrix)/sizeof(int)<<endl;
	revarcmatrix[0] = new int [arcs];
	//cout<<"CP2"<<endl;
	revarcmatrix[1] = new int [arcs];
	//cout<<"CP3"<<endl;
	revarcmatrix[3] = new int [arcs];
	int **fpathmat = new int*[nodes];
	int **bpathmat = new int*[nodes];
	int *fsizemat = new int[nodes];//to store the number of nodes in the shortest path to the node
	int *bsizemat = new int[nodes];
	distancethrough = new double[nodes];
	int **pathmat = new int*[nodes];
	int *sizemat = new int[nodes];
	fpathmat[Origin] = new int [1];
	bpathmat[Destination] = new int [1];
	distancef = new double[nodes];
	distanceb = new double[nodes];
	visited[0] = new int[nodes];//forward
	visited[1] = new int[nodes];//backward
	//cout<<"mem all over"<<endl;
/*	for(i=0;i<nodes;i++)
	{
		pathmat[i] = new int[nodes];
		fpathmat[i] = new int[nodes];
		bpathmat[i] = new int[nodes];
	}*/
	for(i=0;i<arcs;i++)
	{
		revarcmatrix[0][i] = arcmatrix[1][i];
		revarcmatrix[1][i] = arcmatrix[0][i];
		revarcmatrix[3][i] = arcmatrix[3][i];
	}
	for (i = 0; i < arcs; i++)
	{
		if (revarcmatrix[0][i] == Destination)
			revarcmatrix[3][i] = 1;//initializing accessibility
		else
			revarcmatrix[3][i] = 0;
	}
	for(i=0;i<nodes;i++)
	{
		fsizemat[i] = 0;
		bsizemat[i] = 0;
	}
	/*for(i=0;i<nodes;i++)
	{
		for(j=0;j<nodes;j++)
		{
			fpathmat[i][j] = -1;
			bpathmat[i][j] = -1;
		}
	}*/
	
	fpathmat[Origin][0] = Origin;
	fsizemat[Origin] = 1;
	bpathmat[Destination][0] = Destination;
	bsizemat[Destination] = 1;
	for (i = 0; i < nodes; i++)
	{
		visited[0][i] = 0;
	}
	for (i = nodes - 1; i >= 0; i--)
	{
		visited[1][i] = 0;
	}
	visited[0][Origin] = 1;
	visited[1][Destination] = 1;
	for (i = 0; i < arcs; i++)
	{
		if (arcmatrix[0][i] == Origin)
			arcmatrix[3][i] = 1;//initializing accessibility (forward dijkstra)
		else
			arcmatrix[3][i] = 0;
	}
	for (i = 0; i<nodes; i++)
		distancef[i] = 32767;//Declaring all other distances to maximum value of int
	for (i = nodes - 1; i >= 0; i--)
		distanceb[i] = 32767;//Declaring all other distances to maximum value of int
	distancef[Origin] = 0;
	distanceb[Destination] = 0;
	dupweightmat = new double[arcs];
	dupupdweightmat = new double[arcs];
	duplicate[0] = new int[arcs];//To store the origin
	duplicate[1] = new int[arcs];//To store the destination
	duplicate[4] = new int[arcs];//To store the position of the index in original matrix
	while(true)
	{
		s = 0;
		for (j = 0; j < arcs; j++)//storing the accessible arcs in an array
		{
			if (arcmatrix[3][j] == 1)
			{
				duplicate[0][s] = arcmatrix[0][j];//origin duplicated
				duplicate[1][s] = arcmatrix[1][j];//destination duplicated
				dupweightmat[s] = weightmat[j];//weights duplicated
				dupupdweightmat[s] = weightmat[j] + distancef[duplicate[0][s]];//updating weights
				duplicate[4][s] = j;
				s++;
			}
		}
		minindex = 0;
		minvalue = dupupdweightmat[0];
		for (k = 0; k < s; k++)//finding the lowest weight among accessible arcs
		{
			if (dupupdweightmat[k] < minvalue)
			{
				minindex = k;
				minvalue = dupupdweightmat[k];
			}
		}
		if(minvalue < distancef[duplicate[1][minindex]])
		{
			delete[] fpathmat[duplicate[1][minindex]];
			fsizemat[duplicate[1][minindex]] = fsizemat[duplicate[0][minindex]]+1;
			fpathmat[duplicate[1][minindex]] = new int [fsizemat[duplicate[1][minindex]]] ;
		}
		if(minvalue < distancef[duplicate[1][minindex]])
		{
			distancef[duplicate[1][minindex]] = minvalue;
			for(i = 0;i<fsizemat[duplicate[0][minindex]];i++)
			{
				fpathmat[duplicate[1][minindex]][i] = fpathmat[duplicate[0][minindex]][i];
			}
			fpathmat[duplicate[1][minindex]][i] = duplicate[1][minindex];
		}
		arcmatrix[3][duplicate[4][minindex]] = 0;
		visited[0][duplicate[1][minindex]] = 1;
		for (k = 0; k < arcs; k++)//accessibility turned 0 and 1
		{
			if (arcmatrix[0][k] == duplicate[1][minindex])
				arcmatrix[3][k] = 1;
		}
		for (k = 0; k < arcs; k++)//accessibility turned 0 and 1
		{
			if (visited[0][arcmatrix[0][k]]*visited[0][arcmatrix[1][k]])
				arcmatrix[3][k] = 0;
		}
		for (l = 0; l < nodes; l++)
		{
			if (visited[0][l] * visited[1][l])
			{
				//cout << "breaking after "<<iterations<<" iterations\n";
				breakingvar = 1;
				break;
			}
		}
		if (breakingvar)
			break;
		s = 0;//no. of accessible arcs
		for (j = 0; j < arcs; j++)//storing the accessible arcs in an array
		{
			if (revarcmatrix[3][j] == 1)
			{
				duplicate[0][s] = revarcmatrix[0][j];//origin duplicated
				duplicate[1][s] = revarcmatrix[1][j];//destination duplicated
				dupweightmat[s] = weightmat[j];//weights duplicated
				dupupdweightmat[s] = weightmat[j] + distanceb[duplicate[0][s]];//updating weights
				duplicate[4][s] = j;
				s++;
			}
		}
		minindex = 0;
		minvalue = dupupdweightmat[0];
		for (k = 0; k < s; k++)//finding the lowest weight among accessible arcs
		{
			if (dupupdweightmat[k] < minvalue)
			{
				minindex = k;
				minvalue = dupupdweightmat[k];
			}
		}
		//distanceb[duplicate[1][minindex]] = min(minvalue, distanceb[duplicate[1][minindex]]);//storing the minimum distance values
		if(minvalue < distanceb[duplicate[1][minindex]])
		{
			delete[] bpathmat[duplicate[1][minindex]];
			bsizemat[duplicate[1][minindex]] = bsizemat[duplicate[0][minindex]]+1;
			bpathmat[duplicate[1][minindex]] = new int [bsizemat[duplicate[1][minindex]]] ;
		}
		if(minvalue < distanceb[duplicate[1][minindex]])
		{
			distanceb[duplicate[1][minindex]] = minvalue;
			for(i = 0;i<bsizemat[duplicate[0][minindex]];i++)
			{
				bpathmat[duplicate[1][minindex]][i] = bpathmat[duplicate[0][minindex]][i];
			}
			bpathmat[duplicate[1][minindex]][i] = duplicate[1][minindex];
		}
		
		revarcmatrix[3][duplicate[4][minindex]] = 0;
		visited[1][duplicate[1][minindex]] = 1;
		for (k = 0; k < arcs; k++)//accessibility turned 0 and 1
		{
			if (revarcmatrix[0][k] == duplicate[1][minindex])
				revarcmatrix[3][k] = 1;
		}
		for (k = 0; k < arcs; k++)//accessibility turned 0 and 1
		{
			if (visited[1][revarcmatrix[0][k]]*visited[1][revarcmatrix[1][k]])
				revarcmatrix[3][k] = 0;
		}
		for (l = 0; l < nodes; l++)
		{
			if (visited[0][l] * visited[1][l])
			{
				//cout << "breaking after "<<iterations<<" iterations\n";
				breakingvar = 1;
				break;
			}
		}
		if (breakingvar)
			break;
	}
	sf = 0;
	sb = 0;
	for (i = 0; i < nodes; i++)
	{
		if (visited[0][i])
		{
			sf++;
		}
		if (visited[1][i])
		{
			sb++;
		}
	}

	for (i = 0; i < nodes; i++)
	{
		distancethrough[i] = 32767;
	}
	distancethrough[l] = distancef[l] + distanceb[l];
	for(i=0;i<nodes;i++)
	{
		sizemat[i] = 0;
	}
	/*for(i=0;i<nodes;i++)
	{
		for(j=0;j<nodes;j++)
		{
			pathmat[i][j] = -1;
		}
	}*/
	sizemat[l] = fsizemat[l]+bsizemat[l]-1;
	pathmat[l] = new int[sizemat[l]];
	for(i=0;i<fsizemat[l];i++)
	{
		pathmat[l][i] = fpathmat[l][i];
	}
	for(i=0;i<(bsizemat[l]-1);i++)
	{
		pathmat[l][fsizemat[l]+i]= bpathmat[l][bsizemat[l]-i-2];
	}
	for (i = 0; i < arcs; i++)
	{
		if (visited[0][arcmatrix[0][i]] * visited[1][arcmatrix[1][i]])
		{
			if((distancef[arcmatrix[0][i]] + weightmat[i] + distanceb[arcmatrix[1][i]])<distancethrough[arcmatrix[0][i]])
			{
				delete[] pathmat[arcmatrix[0][i]];
				sizemat[arcmatrix[0][i]] = fsizemat[arcmatrix[0][i]]+bsizemat[arcmatrix[1][i]];
				pathmat[arcmatrix[0][i]] = new int [sizemat[arcmatrix[0][i]]];
				for(j=0;j<fsizemat[arcmatrix[0][i]];j++)
				{
					pathmat[arcmatrix[0][i]][j] = fpathmat[arcmatrix[0][i]][j];
				}
				for(j=0;j<bsizemat[arcmatrix[1][i]];j++)
				{
					pathmat[arcmatrix[0][i]][fsizemat[arcmatrix[0][i]]+j]= bpathmat[arcmatrix[1][i]][bsizemat[arcmatrix[1][i]]-j-1];
				}
				distancethrough[arcmatrix[0][i]] = (distancef[arcmatrix[0][i]] + weightmat[i] + distanceb[arcmatrix[1][i]]);
			}
		}
	}
	mindistance = 32767;
	mindistindex = arcmatrix[0][0];
	for (i = 0; i < nodes; i++)
	{
		if (distancethrough[i] < mindistance)
		{
			mindistance = distancethrough[i];
			mindistindex = i;
		}
	}
	//cout<<"Shortest path is ";
	for(i=0;i<sizemat[mindistindex];i++)
		spathmat[i]=pathmat[mindistindex][i];
	//delete[] revarcmatrix;
	/*
	delete[] revarcmatrix[0];
	delete[] revarcmatrix[1];
	delete[] revarcmatrix[3];
	*/
	delete[] fpathmat;
	delete[] bpathmat;
	delete[] pathmat;
	numarcs = 0;
	for(i=0;i<sizemat[mindistindex]-1;i++)
	{
		for(j=0;j<arcs;j++)
		{
			if((spathmat[i]==arcmatrix[0][j])&&((spathmat[i+1]==arcmatrix[1][j])))
			{
				numarcs++;
				arcindex[i] = j;
			}
		}
	}
	minimum_dist = mindistance;
}