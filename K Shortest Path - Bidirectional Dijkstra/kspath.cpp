#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include "kspath.h"
#include "basic.h"
using namespace std;
#define min(a,b) (a<b)?a:b
#define max(a,b) (a>b)?a:b

bool kspath::cyclic(PATH a)
{
	int asize = a.pathlist.size();
	vector<int> v[2];
	for (int i = 0; i < asize; ++i)
	{
		if (find(v[0].begin(),v[0].end(),a.pathlist[i])!=v[0].end())
		{
			v[1][find(v[0].begin(),v[0].end(),a.pathlist[i])-v[0].begin()]+=1;
			return 1;			
		}
		else
		{
			v[0].push_back(a.pathlist[i]);
			v[1].push_back(1);
		}
	}
	return 0;
}

bool kspath::cyclic(PATH a, bool *mn)
{
	//std::find(v.begin(), v.end(), x) != v.end();
	//find(v.begin(), v.end(), old_name_) - v.begin();
	int asize = a.pathlist.size();
	vector<int> v[2];
	for (int i = 0; i < asize; ++i)
	{
		if (mn[a.pathlist[i]])
		{
			if (find(v[0].begin(),v[0].end(),a.pathlist[i])!=v[0].end())
			{
				v[1][find(v[0].begin(),v[0].end(),a.pathlist[i])-v[0].begin()]+=1;
				return 1;			
			}
			else
			{
				v[0].push_back(a.pathlist[i]);
				v[1].push_back(1);
			}
		}
	}
	return 0;
}

bool kspath::same_path(PATH a, PATH b)
{
	bool returnval = 1;
    double diff = (a.weight>b.weight)?(a.weight-b.weight):(b.weight-a.weight);
    int asize = a.pathlist.size();
    int bsize = b.pathlist.size();
    if(diff>0.001)
        returnval = 0;
    else
        {
            if(asize!=bsize)
            {
                returnval = 0;
            }
            else
                {
                    for(int i=0;i<asize;i++)
                        {
                            if(a.pathlist[i]!=b.pathlist[i])
                            {
                                returnval = 0;
                                break;
                            }
                        }
                }
        }
    return returnval;
}

PATH kspath::mergepath(PATH P1, PATH P2, double connectingweight = 0)
{
	PATH P;
	int p1size = P1.pathlist.size();
	int p2size = P2.pathlist.size();
	reverse(P2.pathlist.begin(),P2.pathlist.end());
	if( P1.end == P2.end)
	{
		P.weight = P1.weight+P2.weight;
		P.pathlist.reserve(p1size+p2size-1);
		P.pathlist.insert( P.pathlist.end(), P1.pathlist.begin(), P1.pathlist.end() );
		P.pathlist.insert( P.pathlist.end(), P2.pathlist.begin()+1, P2.pathlist.end() );
	}
	else
	{
		P.weight = P1.weight+P2.weight+connectingweight;
		P.pathlist.reserve(p1size+p2size);
		P.pathlist.insert( P.pathlist.end(), P1.pathlist.begin(), P1.pathlist.end() );
		P.pathlist.insert( P.pathlist.end(), P2.pathlist.begin(), P2.pathlist.end() );
	}
	return P;
}

PATH kspath::mergepath(SPATH P1, SPATH P2, double connectingweight=0)
{
	PATH P;
	int p1size = P1.pathlist.size();
	int p2size = P2.pathlist.size();
	reverse(P2.pathlist.begin(),P2.pathlist.end());
	if( P1.end == P2.end)
	{
		P.weight = P1.weight+P2.weight;
		P.pathlist.reserve(p1size+p2size-1);
		P.pathlist.insert( P.pathlist.end(), P1.pathlist.begin(), P1.pathlist.end() );
		P.pathlist.insert( P.pathlist.end(), P2.pathlist.begin()+1, P2.pathlist.end() );
	}
	else
	{
		P.weight = P1.weight+P2.weight+connectingweight;
		P.pathlist.reserve(p1size+p2size);
		P.pathlist.insert( P.pathlist.end(), P1.pathlist.begin(), P1.pathlist.end() );
		P.pathlist.insert( P.pathlist.end(), P2.pathlist.begin(), P2.pathlist.end() );
	}
	return P;
}

PATHMAT kspath::bidijkstra(GRAPH graph, int Origin, int Destination, int K)
{

	int s;
	double *weight[2];
	bool *visitednode[2];
	bool *visitedarc[2];
	int PATHS_OBTAINED = 0;
	bool *cpp;
	bool *mn;
	int mp;
	
	PATHMAT P;
	PATHMAT P1;
	PATHMAT P2;
	PATHMAT fp;
	PATHMAT bp;

	weight[0] = new double [graph.nodes];
	weight[1] = new double [graph.nodes];

	visitednode[0] = new bool [graph.nodes];
	visitednode[1] = new bool [graph.nodes];

	visitedarc[0] = new bool [graph.arcs];
	visitedarc[1] = new bool [graph.arcs];

	cpp = new bool [graph.nodes];
	mn = new bool [graph.nodes];

	for (int i = 0; i < graph.nodes; ++i)
	{
		weight[0][i] = 32767;
		weight[1][i] = 32767;
		visitednode[0][i] = 0;
		visitednode[1][i] = 0;
		cpp[i] = 0;
		mn[i] = 0;
	}
	weight[0][Origin] = 0;
	weight[1][Destination] = 0;
	visitednode[0][Origin] = 1;
	visitednode[1][Destination] = 1;
	cpp[Origin] = 1;
	cpp[Destination] = 1;
	for (int i = 0; i < graph.arcs; ++i)
	{
		visitedarc[0][i] = 0;
		visitedarc[1][i] = 0;
		if(graph.arcmatrix[0][i]==Origin)
		{
			graph.arcmatrix[2][i] = 1;
		}
		else
		{
			graph.arcmatrix[2][i] = 0;
		}
		if(graph.arcmatrix[1][i]==Destination)
		{
			graph.revarcmatrix[i] = 1;
		}
		else
		{
			graph.revarcmatrix[i] = 0;
		}
	}

	for (int i = 0; i < graph.nodes; ++i)
	{
		fp.pathmat.push_back(PATH());
		bp.pathmat.push_back(PATH());
	}

	fp.pathmat[Origin].weight = 0;
	bp.pathmat[Destination].weight = 0;
	fp.pathmat[Origin].pathlist.push_back(Origin);
	bp.pathmat[Destination].pathlist.push_back(Destination);
	fp.pathmat[Origin].end = Origin;
	bp.pathmat[Destination].end = Destination;
	P1.pathmat.push_back(PATH());
	P2.pathmat.push_back(PATH());
	P1.pathmat[0] = fp.pathmat[Origin];
	P2.pathmat[0] = bp.pathmat[Destination];
	bool allarcsvisited = 0;
	bool allarcsfvisited = 0;
	bool allarcsbvisited = 0;
	int minindex;
	double minweight;
	while(PATHS_OBTAINED<K)
	{
		while(true)
		{
			allarcsvisited	= 1;
			for (int i = 0; i < graph.arcs; ++i)
			{
				if ((visitednode[0][graph.arcmatrix[0][i]]*visitednode[0][graph.arcmatrix[1][i]])||(visitednode[1][graph.arcmatrix[0][i]]*visitednode[1][graph.arcmatrix[1][i]]))
				{
					continue;
				}
				else
				{
					allarcsvisited = 0;
					break;
				}
			}
			if (allarcsvisited)
			{
				break;
			}
			allarcsfvisited = 1;
			for (int i = 0; i < graph.arcs; ++i)
			{
				if (graph.arcmatrix[2][i]==1)
				{
					allarcsfvisited = 0;
				}
			}
			if (allarcsfvisited==0)
			{
				s = 0;
				for (int i = 0; i < graph.arcs; ++i)
				{
					if(graph.arcmatrix[2][i]==1)
					{
						if(s==0)
						{
							minindex = i;
							minweight = weight[0][graph.arcmatrix[0][i]]+graph.weightmat[i];
						}
						else
						{
							if(graph.weightmat[i]+weight[0][graph.arcmatrix[0][i]] < minweight)
							{
								minindex = i;
								minweight = graph.weightmat[i]+weight[0][graph.arcmatrix[0][i]];
							}
						}
						s+=1;
					}
				}
				visitedarc[0][minindex] = 1;
				visitednode[0][graph.arcmatrix[1][minindex]] = 1;
				if (minweight<weight[0][graph.arcmatrix[1][minindex]])
				{
					weight[0][graph.arcmatrix[1][minindex]] = minweight;
					fp.pathmat[graph.arcmatrix[1][minindex]].weight = minweight;
					fp.pathmat[graph.arcmatrix[1][minindex]].pathlist = fp.pathmat[graph.arcmatrix[0][minindex]].pathlist;
					fp.pathmat[graph.arcmatrix[1][minindex]].pathlist.push_back(graph.arcmatrix[1][minindex]);
					fp.pathmat[graph.arcmatrix[1][minindex]].end = graph.arcmatrix[1][minindex];
					int p1size = P1.pathmat.size();
					if (kspath::cyclic(fp.pathmat[graph.arcmatrix[1][minindex]])==0)
					{
						P1.pathmat.push_back(PATH());
						P1.pathmat[p1size] = fp.pathmat[graph.arcmatrix[1][minindex]];
					}
				}
				else
				{
					PATH tempfpath;
					tempfpath.weight = minweight;
					tempfpath.pathlist = fp.pathmat[graph.arcmatrix[0][minindex]].pathlist;
					tempfpath.pathlist.push_back(graph.arcmatrix[1][minindex]);
					tempfpath.end = graph.arcmatrix[1][minindex];
					int p1size = P1.pathmat.size();
					if (kspath::cyclic(tempfpath)==0)
					{
						P1.pathmat.push_back(PATH());
						P1.pathmat[p1size] = tempfpath;
					}
				}
				for (int i = 0; i < graph.arcs; ++i)
				{
					if (graph.arcmatrix[0][i]==graph.arcmatrix[1][minindex])
						graph.arcmatrix[2][i] = 1;
					if (visitedarc[0][i])
						graph.arcmatrix[2][i] = 0;
				}
				bool breakingvar = 0;
				for (int i = 0; i < graph.nodes; ++i)
				{
					if(visitednode[0][i]*visitednode[1][i])
					{
						mn[i] = 1;
						if(cpp[i]==0)
						{
							if(kspath::cyclic(mergepath(fp.pathmat[i],bp.pathmat[i]),mn)==0)
							{
								mp = i;
								breakingvar = 1;
								break;
							}
						}
					}
				}
				if(breakingvar)
					break;
			}
			allarcsbvisited = 1;
			for (int i = 0; i < graph.arcs; ++i)
			{
				if (graph.revarcmatrix[i]==1)
				{
					allarcsbvisited = 0;
				}
			}
			if (allarcsbvisited==0)
			{
				s = 0;
				for (int i = 0; i < graph.arcs; ++i)
				{
					if(graph.revarcmatrix[i]==1)
					{
						if(s==0)
						{
							minindex = i;
							minweight = graph.weightmat[i]+weight[1][graph.arcmatrix[1][i]];
						}
						else
						{
							if(graph.weightmat[i]+weight[1][graph.arcmatrix[1][i]] < minweight)
							{
								minindex = i;
								minweight = graph.weightmat[i]+weight[1][graph.arcmatrix[1][i]];
							}
						}
						s+=1;
					}
				}
				visitedarc[1][minindex] = 1;
				visitednode[1][graph.arcmatrix[0][minindex]] = 1;
				if (minweight<weight[1][graph.arcmatrix[0][minindex]])
				{
					weight[1][graph.arcmatrix[0][minindex]] = minweight;
					bp.pathmat[graph.arcmatrix[0][minindex]].weight = minweight;
					bp.pathmat[graph.arcmatrix[0][minindex]].pathlist = bp.pathmat[graph.arcmatrix[1][minindex]].pathlist;
					bp.pathmat[graph.arcmatrix[0][minindex]].pathlist.push_back(graph.arcmatrix[0][minindex]);
					bp.pathmat[graph.arcmatrix[0][minindex]].end = graph.arcmatrix[0][minindex];
					int p2size = P2.pathmat.size();
					if (kspath::cyclic(bp.pathmat[graph.arcmatrix[0][minindex]])==0)
					{
						P2.pathmat.push_back(PATH());
						P2.pathmat[p2size] = bp.pathmat[graph.arcmatrix[0][minindex]];
					}
				}
				else
				{
					PATH tempbpath;
					tempbpath.weight = minweight;
					tempbpath.pathlist = bp.pathmat[graph.arcmatrix[1][minindex]].pathlist;
					tempbpath.pathlist.push_back(graph.arcmatrix[0][minindex]);
					tempbpath.end = graph.arcmatrix[0][minindex];
					int p2size = P2.pathmat.size();
					if (kspath::cyclic(tempbpath)==0)
					{
						P2.pathmat.push_back(PATH());
						P2.pathmat[p2size] = tempbpath;
					}
				}
				for (int i = 0; i < graph.arcs; ++i)
				{
					if (graph.arcmatrix[1][i]==graph.arcmatrix[0][minindex])
						graph.revarcmatrix[i] = 1;
					if (visitedarc[1][i])
						graph.revarcmatrix[i] = 0;
				}
				bool breakingvar = 0;
				for (int i = 0; i < graph.nodes; ++i)
				{
					if(visitednode[0][i]*visitednode[1][i])
					{
						mn[i] = 1;
						if(cpp[i]==0)
						{
							if(kspath::cyclic(mergepath(fp.pathmat[i],bp.pathmat[i]),mn)==0)
							{
								mp = i;
								breakingvar = 1;
								break;
							}
						}
					}
				}
				if(breakingvar)
					break;
			}
		}
		if ((allarcsvisited)&&(PATHS_OBTAINED<K))
		{
			PATH temppath;
			bool samepath = 0;
			int psize = P.pathmat.size();
			int P1size = P1.pathmat.size();
			int P2size = P2.pathmat.size();
			for (int i = 0; i < P1size; ++i)
			{
				for (int j = 0; j < P2size; ++j)
				{
					double connectingweight;
					int arcindex;
					if(P1.pathmat[i].end==P2.pathmat[j].end)
					{
						temppath = mergepath(P1.pathmat[i],P2.pathmat[j]);
						psize = P.pathmat.size();
						samepath = 0;
						for (int k = 0; k < psize; ++k)
						{
							if (same_path(temppath,P.pathmat[k]))
							{
								samepath = 1;
								break;
							}
						}
						if (samepath)
						{
							continue;
						}
						if (kspath::cyclic(temppath,mn))
						{
							continue;
						}
						P.pathmat.push_back(PATH());
						P.pathmat[psize] = temppath;
						sort(P.pathmat.begin(),P.pathmat.end(),comparebyweight());
					}
					else
					{
						arcindex = -1;
						for (int k = 0; k < graph.arcs; ++k)
						{
							if((P1.pathmat[i].end==graph.arcmatrix[0][k])&&(P2.pathmat[j].end==graph.arcmatrix[1][k]))
							{
								arcindex = k;
								connectingweight = graph.weightmat[k];
							}
						}
						if (arcindex==-1)
						{
							continue;
						}
						temppath = mergepath(P1.pathmat[i], P2.pathmat[j], connectingweight);
						psize = P.pathmat.size();
						samepath = 0;
						for (int k = 0; k < psize; ++k)
						{
							if (same_path(temppath,P.pathmat[k]))
							{
								samepath = 1;
								break;
							}
						}
						if (samepath)
						{
							continue;
						}
						if (kspath::cyclic(temppath,mn))
						{
							continue;
						}
						P.pathmat.push_back(PATH());
						P.pathmat[psize] = temppath;
						sort(P.pathmat.begin(), P.pathmat.end(),comparebyweight());
					}
				}
			}
		}
		else
		{
			double boundweight = weight[0][mp] + weight[1][mp];
			//cout<<"BOUNDARY WEIGHT: "<<boundweight<<endl;
			int psize = P.pathmat.size();
			PATHS_OBTAINED = psize;
			PATH temppath = mergepath(fp.pathmat[mp],bp.pathmat[mp]);
			int temppathsize = temppath.pathlist.size();
			for (int i = 0; i < temppathsize; ++i)
			{
				cpp[temppath.pathlist[i]]=1;
			}
			bool samepath = 0;
			for (int i = 0; i < psize; ++i)
			{
				if(same_path(temppath,P.pathmat[i]))
				{
					samepath = 1;
					break;
				}
			}
			if (samepath)
			{
				continue;
			}
			if (kspath::cyclic(temppath,mn))
			{
				continue;
			}
			P.pathmat.push_back(PATH());
			P.pathmat[psize] = temppath;
			sort(P.pathmat.begin(), P.pathmat.end(),comparebyweight());
			int P1size = P1.pathmat.size();
			int P2size = P2.pathmat.size();
			for (int i = 0; i < P1size; ++i)
			{
				for (int j = 0; j < P2size; ++j)
				{
					double connectingweight;
					int arcindex;
					if(P1.pathmat[i].end==P2.pathmat[j].end)
					{
						temppath = mergepath(P1.pathmat[i],P2.pathmat[j]);
						psize = P.pathmat.size();
						samepath = 0;
						for (int k = 0; k < psize; ++k)
						{
							if (same_path(temppath,P.pathmat[k]))
							{
								samepath = 1;
								break;
							}
						}
						if (samepath)
						{
							continue;
						}
						if (kspath::cyclic(temppath,mn))
						{
							continue;
						}
						P.pathmat.push_back(PATH());
						P.pathmat[psize] = temppath;
						sort(P.pathmat.begin(),P.pathmat.end(),comparebyweight());
					}
					else
					{
						arcindex = -1;
						for (int k = 0; k < graph.arcs; ++k)
						{
							if((P1.pathmat[i].end==graph.arcmatrix[0][k])&&(P2.pathmat[j].end==graph.arcmatrix[1][k]))
							{
								arcindex = k;
								connectingweight = graph.weightmat[k];
							}
						}
						if (arcindex==-1)
						{
							continue;
						}
						if (P1.pathmat[i].weight+connectingweight+P2.pathmat[j].weight<=boundweight)
						{
							temppath = mergepath(P1.pathmat[i], P2.pathmat[j], connectingweight);
							psize = P.pathmat.size();
							samepath = 0;
							for (int k = 0; k < psize; ++k)
							{
								if (same_path(temppath,P.pathmat[k]))
								{
									samepath = 1;
									break;
								}
							}
							if (samepath)
							{
								continue;
							}
							if (kspath::cyclic(temppath,mn))
							{
								continue;
							}
							P.pathmat.push_back(PATH());
							P.pathmat[psize] = temppath;
							sort(P.pathmat.begin(), P.pathmat.end(),comparebyweight());
						}
					}
				}
			}
		}
		PATHS_OBTAINED = P.pathmat.size();
		//cout<<"PATHS OBTAINED : "<<PATHS_OBTAINED<<endl;
		//for (int i = 0; i < PATHS_OBTAINED; ++i)
		//{
		//	cout<<P.pathmat[i].weight<<endl;
		//}
		if (allarcsvisited)
		{
			break;
		}
	}
	/*int p1loop = P1.pathmat.size();
	int p2loop = P2.pathmat.size();
	cout<<"P1:"<<endl;
	for (int i = 0; i < p1loop; ++i)
	{
		int piloop = P1.pathmat[i].pathlist.size();
		for (int j = 0; j < piloop; ++j)
		{
			cout<<P1.pathmat[i].pathlist[j]<<"-->";
		}
		cout<<endl;
	}
	cout<<"P2:"<<endl;
	for (int i = 0; i < p2loop; ++i)
	{
		int piloop = P2.pathmat[i].pathlist.size();
		for (int j = 0; j < piloop; ++j)
		{
			cout<<P2.pathmat[i].pathlist[j]<<"-->";
		}
		cout<<endl;
	}
	cout<<"P2 OVER"<<endl;*/
	return P;
}


