#include <iostream>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <string>
#include "spath.h"
using namespace std;
#define min(a,b) a<b?a:b
double spath::bidijkstra(int nodes, int arcs, int **arcmatrix, double *weightmat, int Origin, int Destination)
{
	int iterations;
	int s, minindex, i, j, k, l;
	int *duplicate[5];
	double minvalue;
	double *dupweightmat;
	double *dupupdweightmat;
	double *distancef;//To store forward dijkstra distance
	double *distanceb;//To store backward dijkstra distance
	int *revarcmatrix[4];
	int *visited[2];
	int breakingvar = 0;
	double *distancethrough;
	double mindistance;
	int mindistindex,sf,sb;
	int *visitedf;
	int *visitedb;
	revarcmatrix[0] = new int[arcs];//To store the origin
	revarcmatrix[1] = new int[arcs];//To store the destination
	revarcmatrix[3] = new int[arcs];//To store accessibility
	for (i = 0; i < arcs; i++)
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
	distancef = new double[nodes];
	distanceb = new double[nodes];
	visited[0] = new int[nodes];//forward
	visited[1] = new int[nodes];//backward
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
	//dupweightmat = new double[arcs];//To store the weights
	//dupupdweightmat = new double[arcs];//To store the updated weights
	duplicate[4] = new int[arcs];//To store the position of the index in original matrix
	iterations = 0;
	while(true)//Maximum no. of iterations = nodes/2
	{
		iterations++;
		s = 0;//no. of accessible arcs
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
		distancef[duplicate[1][minindex]] = min(minvalue, distancef[duplicate[1][minindex]]);//storing the minimum distance values
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
		/*for (k = 0; k < arcs; k++)//accessibility turned 0 and 1
		{
			if ((arcmatrix[0][k] == duplicate[1][minindex])&&(arcmatrix[1][k]==duplicate[0][minindex]))
				arcmatrix[3][k] = 0;
		}*/
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
		distanceb[duplicate[1][minindex]] = min(minvalue, distanceb[duplicate[1][minindex]]);//storing the minimum distance values
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
		/*for (k = 0; k < arcs; k++)//accessibility turned 0 and 1
		{
			if ((revarcmatrix[0][k] == duplicate[1][minindex])&&(revarcmatrix[1][k]==duplicate[0][minindex]))
				revarcmatrix[3][k] = 0;
		}*/
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
	//l is the last node visited
	sf = 0;
	sb = 0;
	visitedf = new int[nodes];
	visitedb = new int[nodes];
	for (i = 0; i < nodes; i++)
	{
		if (visited[0][i])
		{
			visitedf[sf] = i;
			sf++;
		}
		if (visited[1][i])
		{
			visitedf[sb] = i;
			sb++;
		}
	}
	distancethrough = new double[nodes];
	for (i = 0; i < nodes; i++)
	{
		distancethrough[i] = 32767;
	}
	distancethrough[l] = distancef[l] + distanceb[l];
	for (i = 0; i < arcs; i++)
	{
		if (visited[0][arcmatrix[0][i]] * visited[1][arcmatrix[1][i]])
		{
			distancethrough[arcmatrix[0][i]] = min(distancethrough[arcmatrix[0][i]], (distancef[arcmatrix[0][i]] + weightmat[i] + distanceb[arcmatrix[1][i]]));
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
	return mindistance;
	cout <<"\nMeeting Point: "<<l<<"\nshortest path passes through " << mindistindex << " and the length is " << mindistance<<"\nno. of iterations = "<<iterations<<'\n';
	//cout << "Execution Time (Bidijkstra) : " << float(clock() - begin_time) << '\n';
}
double spath::dijkstra(int nodes, int arcs, int **arcmatrix, double *weightmat, int Origin, int Destination)
{
	int s, minindex, i, j, k;
	double minvalue;
	int *duplicate[5];
	double *distance;
	double *dupweightmat;
	double *dupupdweightmat;
	int *visited;
	visited = new int[nodes];
	for(i=0;i<nodes;i++)
	visited[i]=0;
	visited[Origin]=1;
	distance = new double[nodes];
	for (i = 0; i < arcs; i++)
	{
		if (arcmatrix[0][i] == Origin)
			arcmatrix[3][i] = 1;//initializing accessibility
		else
			arcmatrix[3][i] = 0;
	}
	for (i = 1; i<nodes; i++)
		distance[i] = 32767;//Declaring all other distances to maximum value of int
	distance[Origin] = 0;
	duplicate[0] = new int[arcs];//To store the origin
	duplicate[1] = new int[arcs];//To store the destination
	dupweightmat = new double[arcs];//To store the weights
	dupupdweightmat = new double[arcs];//To store the updated weights
	duplicate[4] = new int[arcs];//To store the position of the index in original matrix
	for (i = 0; i < nodes - 1; i++)//no. of iterations = nodes - 1
	{
		s = 0;//no. of accessible arcs
		for (j = 0; j < arcs; j++)//storing the accessible arcs in an array
		{
			if (arcmatrix[3][j] == 1)
			{
				duplicate[0][s] = arcmatrix[0][j];//origin duplicated
				duplicate[1][s] = arcmatrix[1][j];//destination duplicated
				dupweightmat[s] = weightmat[j];//weights duplicated
				dupupdweightmat[s] = weightmat[j] + distance[duplicate[0][s]];//updating weights
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
		visited[duplicate[1][minindex]]=1;
		distance[duplicate[1][minindex]] = min(minvalue, distance[duplicate[1][minindex]]);//storing the minimum distance values
		arcmatrix[3][duplicate[4][minindex]] = 0;
		if (i == nodes - 2)
		{
			for (k = 0; k < s; k++)
			{
				if (dupupdweightmat[k] < distance[duplicate[1][k]])
					distance[duplicate[1][k]] = dupupdweightmat[k];
			}
		}
		for (k = 0; k < arcs; k++)//accessibility turned 0 and 1
		{
			if (arcmatrix[0][k] == duplicate[1][minindex])
				arcmatrix[3][k] = 1;
		}
		for (k = 0; k < arcs; k++)//accessibility turned 0 and 1
		{
			if (visited[arcmatrix[0][k]]*visited[arcmatrix[1][k]])
				arcmatrix[3][k] = 0;
		}
		/*for (k = 0; k < arcs; k++)//accessibility turned 0 and 1
		{
			if ((arcmatrix[0][k] == duplicate[1][minindex])&&(arcmatrix[1][k]==duplicate[0][minindex]))
				arcmatrix[3][k] = 0;
		}*/
	}
	return distance[Destination];
	cout << "Origin: " << Origin << "\nDestination: " << Destination << "\n\nDistance[" << Destination << "]=" << distance[Destination]<<'\n';
	//for (i = 1; i < nodes; i++)
	//{
		//cout << '\n' << "distance[" << i << "]:" << distance[i] << ' ';
	//}
	//cout <<'\n'<< "Execution Time (Dijkstra) : " << float(clock() - begin_time) << '\n';
}
double spath::reversedijkstra(int nodes, int arcs, int **arcmatrix,double *weightmat, int Origin, int Destination)
{
	int s, minindex, i, j, k;
	double minvalue;
	int *visited;
	int *duplicate[5];
	int *revarcmatrix[4];
	double *distance;
	double *dupweightmat;
	double *dupupdweightmat;
	revarcmatrix[0] = new int[arcs];//To store the origin
	revarcmatrix[1] = new int[arcs];//To store the destination
	//weightmat = new double[arcs];//To store the weights
	revarcmatrix[3] = new int[arcs];//To store accessibility
  visited = new int[nodes];
	for(i=0;i<nodes;i++)
	visited[i]=0;
	visited[Destination]=1;
	distance = new double[nodes];
	for (i = 0; i < arcs; i++)
	{
		revarcmatrix[0][i] = arcmatrix[1][i];
		revarcmatrix[1][i] = arcmatrix[0][i];
		//weightmat[i] = weightmat[i];
		revarcmatrix[3][i] = arcmatrix[3][i];
	}
	for (i = 0; i < arcs; i++)
	{
		if (revarcmatrix[0][i] == Destination)
			revarcmatrix[3][i] = 1;//initializing accessibility
		else
			revarcmatrix[3][i] = 0;
	}
	for (i = nodes - 1; i >= 0; i--)
		distance[i] = 32767;//Declaring all other distances to maximum value of int
	distance[Destination] = 0;
	duplicate[0] = new int[arcs];//To store the origin
	duplicate[1] = new int[arcs];//To store the destination
	dupweightmat = new double[arcs];//To store the weights
	dupupdweightmat = new double[arcs];//To store the updated weights
	duplicate[4] = new int[arcs];//To store the position of the index in original matrix
	for (i = 0; i < nodes - 1; i++)//no. of iterations = nodes - 1
	{
		s = 0;//no. of accessible arcs
		for (j = 0; j < arcs; j++)//storing the accessible arcs in an array
		{
			if (revarcmatrix[3][j] == 1)
			{
				duplicate[0][s] = revarcmatrix[0][j];//origin duplicated
				duplicate[1][s] = revarcmatrix[1][j];//destination duplicated
				dupweightmat[s] = weightmat[j];//weights duplicated
				dupupdweightmat[s] = weightmat[j] + distance[duplicate[0][s]];//updating weights
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
		visited[duplicate[1][minindex]]=1;
		distance[duplicate[1][minindex]] = min(minvalue, distance[duplicate[1][minindex]]);//storing the minimum distance values
		revarcmatrix[3][duplicate[4][minindex]] = 0;
		if (i == nodes - 2)
		{
			for (k = 0; k < s; k++)
			{
				if (dupupdweightmat[k] < distance[duplicate[1][k]])
					distance[duplicate[1][k]] = dupupdweightmat[k];
			}
		}
		for (k = 0; k < arcs; k++)//accessibility turned 0 and 1
		{
			if (revarcmatrix[0][k] == duplicate[1][minindex])
				revarcmatrix[3][k] = 1;
		}
		for (k = 0; k < arcs; k++)//accessibility turned 0 and 1
		{
			if (visited[revarcmatrix[0][k]]*visited[revarcmatrix[1][k]])
				revarcmatrix[3][k] = 0;
		}


	}
	return distance[Origin];
	cout << "\nDistance[" << Origin << "]=" << distance[Origin] << '\n';
}
void spath::prims(int nodes, int arcs, int **arcmatrix, double* weightmat, int Origin, int Destination)
{
	int i, j, s, k, minindex;
	double minvalue;
	int *duplicate[4];
	int *output[2];
	double *outputd[2];
	int *visited;
	double *dupweightmat;
	double *dupupdweightmat;
	visited = new int[nodes];
	for (i = 0; i < arcs; i++)
	{
		if (arcmatrix[0][i] == Origin||arcmatrix[1][i] == Origin)
			arcmatrix[3][i] = 1;//initializing accessibility
		else
			arcmatrix[3][i] = 0;
	}
	for (i = 0; i < nodes; i++)
		visited[i] = 0;
	visited[Origin] = 1;
	duplicate[0] = new int[arcs];//To store the origin
	duplicate[1] = new int[arcs];//To store the destination
	dupweightmat = new double[arcs];//To store the weights
	dupupdweightmat = new double[arcs];//To store the position in original matrix
	output[0] = new int[nodes - 1];
	output[1] = new int[nodes - 1];
	outputd[0] = new double[nodes - 1];
	outputd[1] = new double[nodes - 1];
	for (i = 0; i < nodes - 1; i++)
	{
		s = 0;
		for (j = 0; j < arcs; j++)
		{
			if (arcmatrix[3][j] == 1)
			{
				duplicate[0][s] = arcmatrix[0][j];//origin duplicated
				duplicate[1][s] = arcmatrix[1][j];//destination duplicated
				dupweightmat[s] = weightmat[j];//weights duplicated
				dupupdweightmat[s] = j;//storing the index
				s++;
			}
		}
		minvalue = dupweightmat[0];
		minindex = 0;
		for (k = 0; k < s; k++)
		{
			if (dupweightmat[k] < minvalue)
			{
				minindex = k;
				minvalue = dupweightmat[k];
			}
		}
		output[0][i] = duplicate[0][minindex];
		output[1][i] = duplicate[1][minindex];
		outputd[0][i] = dupweightmat[minindex];
		outputd[1][i] = dupupdweightmat[minindex];
		visited[output[0][i]] = 1;
		visited[output[1][i]] = 1;
		for (k = 0; k < arcs; k++)
		{
			if ((visited[arcmatrix[0][k]] * visited[arcmatrix[1][k]] == 1) || ((visited[arcmatrix[0][k]] == 0) && (visited[arcmatrix[1][k]] == 0)))
				arcmatrix[3][k] = 0;
			else
				arcmatrix[3][k] = 1;
		}
	}
	if(Origin!=output[0][0])
	{
		int temp = output[0][0];
		output[0][0] = output[1][0];
		output[1][0] = temp;
	}
	for (i = 1; i < nodes - 1; i++)
	{
		if((output[0][i]==output[0][i-1])||(output[1][i]==output[1][i-1]))
		{
			int temp = output[0][i];
			output[0][i] = output[1][i];
			output[1][i] = temp;
		}
	}
	cout<<"PRIMS ALGORITHM :"<<endl;
	for (i = 0; i < nodes - 1; i++)
	{
		cout << '\n' << output[0][i] << ' ' << output[1][i];
	}
}