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
void kspath::kshortestpath(int nodes, int arcs, int **arcmatrix, double *weightmat, int Origin, int Destination)
{
	int iterations;
	int s, minindex, i, j, k, l, paths;
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
	int *visitedf;//to store the nodes visited in fdijkstra
	int *visitedb;//to store the nodes visited in bdijkstra
	int **pathmat = new int*[nodes*nodes];//to store the path 
	int **fpathmat = new int*[nodes*nodes];//to store the path in fdijkstra
	int **bpathmat = new int*[nodes*nodes];//to store the path in bdijkstra
	double *distmat;//to store the minimum weight in each iteration
	distmat = new int[nodes*nodes];
	pathmat[0] = new int [1];
	fpathmat[0] = new int [1];
	bpathmat[0] = new int [1];
	pathmat[0][0] = Origin;
	fpathmat[0][0] = Origin;
	bpathmat[0][0] = Destination;
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
	duplicate[0] = new int[arcs];//To store the origin
	duplicate[1] = new int[arcs];//To store the destination
	dupweightmat = new double[arcs];//To store the weights
	dupupdweightmat = new double[arcs];//To store the updated weights
	duplicate[4] = new int[arcs];//To store the position of the index in original matrix
	iterations = 0;
	i = 1;
	paths = 1;
	while(true)
	{
		iterations++;
		s = 0;
		int prepath = 0;
		for (j = 0; j < arcs; j++)//storing the accessible arcs in an array
		{
			if (arcmatrix[3][j] == 1)
			{
				duplicate[0][s] = arcmatrix[0][j];//origin duplicated
				duplicate[1][s] = arcmatrix[1][j];//destination duplicated
				dupweightmat[s] = weightmat[j];//weights duplicated
				dupupdweightmat[s] = weightmat[j] + distancef[duplicate[0][s]];//updating weights
				duplicate[4][s] = j;//arc matrix index in original matrix
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
		for(k=0;k<paths;k++)
		{
			if(fpathmat[k][(sizeof(fpathmat[k])/sizeof(fpathmat[k][0]))-1]==duplicate[0][minindex])
				prepath++;
		}
		paths+=prepath;
		distancef[duplicate[1][minindex]] = min(minvalue, distancef[duplicate[1][minindex]]);//storing the minimum distance values

	}
}