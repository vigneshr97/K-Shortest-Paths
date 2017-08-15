#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <time.h>
#include "kspath.h"
#include "basic.h"
using namespace std;
#define min(a,b) (a<b)?a:b
#define max(a,b) (a>b)?a:b

bool kspath::cyclic(SPATH a)
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

bool kspath::cyclic(YENPATH a)
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

bool kspath::cyclic(SPATH a, bool *mn)
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

bool kspath::same_path(SPATH a, SPATH b)
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

bool kspath::same_path(YENPATH a, YENPATH b)
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

YENPATH kspath::mergepath( YENPATH P1, YENPATH P2 )
{
	YENPATH P;
	int p1size = P1.pathlist.size();
	int p2size = P2.pathlist.size();
	P.weight = P1.weight + P2.weight;
	P.pathlist.reserve(p1size+p2size-1);
	P.pathlist.insert( P.pathlist.end(), P1.pathlist.begin(), P1.pathlist.end() );
	P.pathlist.insert( P.pathlist.end(), P2.pathlist.begin()+1, P2.pathlist.end() );
	P.found = P2.found;
	return P;
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

SPATH kspath::mergepath(SPATH P1, SPATH P2, double connectingweight=0)
{
	SPATH P;
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

YENPATH kspath::sp(GRAPH graph, int Origin, int Destination)
{
	int s = 0;
	bool *visited;
	YENPATH P;
	visited = new bool [graph.nodes];

	YENPATHMAT path;

	int minindex;
	double minweight;

	for (int i = 0; i < graph.nodes; ++i)
	{
		path.pathmat.push_back(YENPATH());
		path.pathmat[i].weight = 32767;
		visited[i] = 0;
	}

	for (int i = graph.fstar[Origin]; i < graph.fstar[Origin + 1]; ++i)
	{
		if (graph.fstarmatrix[i].weight<32000)
		{
			graph.fstarmatrix[i].faccess = 1;
			s+=1;
		}
		else
		{
			graph.fstarmatrix[i].faccess = 0;
		}
	}

	if (s==0)
	{
		P.found = 0;
		return P;
	}

	visited[Origin] = 1;
	path.pathmat[Origin].weight = 0;
	path.pathmat[Origin].pathlist.push_back(Origin);
	path.pathmat[Origin].arcindex = {};
	bool found = 1;
	if (visited[Destination])
	{
		P.found = 1;
		P = path.pathmat[Origin];
		return P;
	}
	int i = 0;
	while(i<graph.arcs)
	{
		i+=1;
		s = 0;
		for (int j = 0; j < graph.arcs; ++j)
		{
			if (graph.fstarmatrix[j].faccess)
			{
				if (s==0)
				{
					minindex = j;
					minweight = path.pathmat[graph.fstarmatrix[j].head].weight+graph.fstarmatrix[j].weight;
				}
				else
				{
					if ((path.pathmat[graph.fstarmatrix[j].head].weight+graph.fstarmatrix[j].weight)<minweight)
					{
						minindex = j;
						minweight = path.pathmat[graph.fstarmatrix[j].head].weight+graph.fstarmatrix[j].weight;
					}
				}
				s+=1;
			}
		}
		if (s==0)
		{
			found = 0;
			break;
		}
		visited[graph.fstarmatrix[minindex].tail] = 1;
		graph.fstarmatrix[minindex].faccess = 0;
		if (minweight < path.pathmat[graph.fstarmatrix[minindex].tail].weight)
		{
			path.pathmat[graph.fstarmatrix[minindex].tail].weight = minweight;
			path.pathmat[graph.fstarmatrix[minindex].tail].pathlist = path.pathmat[graph.fstarmatrix[minindex].head].pathlist;
			path.pathmat[graph.fstarmatrix[minindex].tail].pathlist.push_back(graph.fstarmatrix[minindex].tail);
			path.pathmat[graph.fstarmatrix[minindex].tail].arcindex = path.pathmat[graph.fstarmatrix[minindex].head].arcindex;
			path.pathmat[graph.fstarmatrix[minindex].tail].arcindex.push_back(minindex);
		}
		if (visited[Destination])
		{
			break;
		}
		for (int j = graph.fstar[graph.fstarmatrix[minindex].tail]; j < graph.fstar[graph.fstarmatrix[minindex].tail+1]; ++j)
		{
			if (graph.fstarmatrix[j].weight<32000)
			{
				graph.fstarmatrix[j].faccess = 1;
			}
			if (graph.fstarmatrix[j].weight>=32000)
			{
				graph.fstarmatrix[j].faccess = 0;
			}
			if (visited[graph.fstarmatrix[j].tail])
			{
				graph.fstarmatrix[j].faccess = 0;
			}
		}
	}
	if (found==0)
	{
		P.found = 0;
		return P;
	}
	else
	{
		P = path.pathmat[Destination];
		if (P.weight<32000)
		{
			P.found = 1;
		}
		else
		{
			P.found = 0;
		}
	}
	return P;
}

	

YENPATHMAT kspath::yen(GRAPH graph, int Origin, int Destination, int K)
{
	GRAPH graphcopy;
	YENPATHMAT P;
	YENPATHMAT temp_P;
	YENPATH shortest_path;
	YENPATH innershortpath;
	
	int paths_obtained = 1;
	int temppathmatsize;
	int temppsize;

	graphcopy.nodes = graph.nodes;
	graphcopy.arcs = graph.arcs;
	for (int i = 0; i < graph.arcs; ++i)
	{
		graphcopy.fstarmatrix.push_back(ARC());
		graphcopy.fstarmatrix[i].head = graph.fstarmatrix[i].head;
		graphcopy.fstarmatrix[i].tail = graph.fstarmatrix[i].tail;
		graphcopy.fstarmatrix[i].weight = graph.fstarmatrix[i].weight;
	}

	graphcopy.fstar = new int [graphcopy.nodes+1];
	for (int i = 0; i <= graphcopy.nodes; ++i)
	{
		graphcopy.fstar[i] = graph.fstar[i];
	}

	P.pathmat.push_back(YENPATH());
	shortest_path = kspath::sp(graphcopy,Origin,Destination);
	P.pathmat[0] = shortest_path;

	while(paths_obtained<K)
	{
		YENPATH rootpath, spurpath;
		paths_obtained = P.pathmat.size();
		shortest_path = P.pathmat[ paths_obtained - 1 ];
		rootpath.weight = 0;
		spurpath.weight = 0;
		int spsize = shortest_path.pathlist.size();
		for (int i = 0; i < spsize-1; ++i)
		{
			int spurnode = shortest_path.pathlist[i];
			rootpath.pathlist = {};
			for (int j = 0; j <=i ; ++j)
			{
				rootpath.pathlist.push_back(shortest_path.pathlist[j]);
			}
			int rootpathsize = rootpath.pathlist.size();
			for (int j = 0; j < paths_obtained; ++j)
			{
				bool vsamepath = 1;
				for (int k = 0; k <= i; ++k)
				{
					if (P.pathmat[j].pathlist[k]==rootpath.pathlist[k])
					{
						continue;
					}
					else
					{
						vsamepath = 0;
						break;
					}
				}
				//if (P.pathmat[j].pathlist.size()<i+2)
				//{
				//	vsamepath = 0;
				//}
				if (vsamepath)
				{
					for (int k = graphcopy.fstar[P.pathmat[j].pathlist[i]]; k < graphcopy.fstar[P.pathmat[j].pathlist[i]+1]; ++k)
					{
						if (P.pathmat[j].pathlist[i+1]==graphcopy.fstarmatrix[k].tail)
						{
							graphcopy.fstarmatrix[k].weight = 32767;
						}
					}
				}
				rootpathsize = rootpath.pathlist.size()-1;
				for (int k = 0; k < rootpathsize; ++k)
				{
					for (int l = graphcopy.fstar[rootpath.pathlist[k]]; l < graphcopy.fstar[ rootpath.pathlist[k] + 1 ]; ++l)
					{
						graphcopy.fstarmatrix[l].weight = 32767;
					}
				}
			}
			spurpath = kspath::sp(graphcopy,spurnode,Destination);
			if (spurpath.found==0)
			{
				for (int j = 0; j < graphcopy.arcs; ++j)
				{
					graphcopy.fstarmatrix[j].weight = graph.fstarmatrix[j].weight;
				}
				for (int j = graph.fstar[shortest_path.pathlist[i]]; j < graph.fstar[shortest_path.pathlist[i]+1]; ++j)
				{
					if (shortest_path.pathlist[i+1]==graph.fstarmatrix[j].tail)
					{
						rootpath.weight+=graphcopy.fstarmatrix[j].weight;
					}
				}
				continue;
			}
			innershortpath = kspath::mergepath(rootpath,spurpath);
			temppsize = temp_P.pathmat.size();
			bool continuevar = 0;
			for (int j = 0; j < temppsize; ++j)
			{
				if (same_path(innershortpath,temp_P.pathmat[j]))
				{
					continuevar = 1;
					break;
				}
			}
			if (continuevar)
			{
				for (int j = 0; j < graphcopy.arcs; ++j)
				{
					graphcopy.fstarmatrix[j].weight = graph.fstarmatrix[j].weight;
				}
				for (int j = graph.fstar[shortest_path.pathlist[i]]; j < graph.fstar[shortest_path.pathlist[i]+1]; ++j)
				{
					if (shortest_path.pathlist[i+1]==graph.fstarmatrix[j].tail)
					{
						rootpath.weight+=graphcopy.fstarmatrix[j].weight;
					}
				}
				continue;
			}
			temp_P.pathmat.push_back(YENPATH());
			temp_P.pathmat[temppsize] = innershortpath;
			for (int j = 0; j < graphcopy.arcs; ++j)
			{
				graphcopy.fstarmatrix[j].weight = graph.fstarmatrix[j].weight;
			}
			for (int j = graph.fstar[shortest_path.pathlist[i]]; j < graph.fstar[shortest_path.pathlist[i]+1]; ++j)
			{
				if (shortest_path.pathlist[i+1]==graph.fstarmatrix[j].tail)
				{
					rootpath.weight+=graphcopy.fstarmatrix[j].weight;
				}
			}
		}
		temppsize = temp_P.pathmat.size();
		if (temppsize==0)
		{
			break;
		}
		sort(temp_P.pathmat.begin(),temp_P.pathmat.end(),cw());
		paths_obtained = P.pathmat.size();
		P.pathmat.push_back(YENPATH());
		P.pathmat[paths_obtained] = temp_P.pathmat[0];
		temp_P.pathmat.erase(temp_P.pathmat.begin());
		paths_obtained = P.pathmat.size();
	}
	return P;
}



SPATHMAT kspath::bidijkstra(GRAPH graph, int Origin, int Destination, int K)
{
	int s;
	int paths_obtained = 0;
	bool *cpp, *mn;
	SPATHMAT P, P1, P2, tempforwardpathlist, tempreversepathlist;
	
	cpp = new bool[graph.nodes];
	mn = new bool[graph.nodes];

	P1.pathmat.push_back(SPATH());
	P2.pathmat.push_back(SPATH());
	tempforwardpathlist.pathmat.push_back(SPATH());
	tempreversepathlist.pathmat.push_back(SPATH());

	P1.pathmat[0].weight = 0;
	P2.pathmat[0].weight = 0;
	tempforwardpathlist.pathmat[0].weight = 0;
	tempreversepathlist.pathmat[0].weight = 0;

	P1.pathmat[0].pathlist.push_back(Origin);
	P1.pathmat[0].end = Origin;
	P2.pathmat[0].pathlist.push_back(Destination);
	P2.pathmat[0].end = Destination;

	tempforwardpathlist.pathmat[0].pathlist.push_back(Origin);
	tempforwardpathlist.pathmat[0].end = Origin;
	tempreversepathlist.pathmat[0].pathlist.push_back(Destination);
	tempreversepathlist.pathmat[0].end = Destination;
	
	double minweightf = 32767;
	double minweightb = 32767;
	tempforwardpathlist.pathmat[0].bestweight = 32767;
	tempreversepathlist.pathmat[0].bestweight = 32767;
	tempforwardpathlist.pathmat[0].accessible_arcs = {};
	tempreversepathlist.pathmat[0].accessible_arcs = {};

	for (int i = graph.fstar[Origin]; i < graph.fstar[Origin+1]; ++i)
	{
		tempforwardpathlist.pathmat[0].accessible_arcs.push_back(i);
		if( graph.fstarmatrix[i].weight < tempforwardpathlist.pathmat[0].bestweight )
		{
			tempforwardpathlist.pathmat[0].bestweight = graph.fstarmatrix[i].weight;
			tempforwardpathlist.pathmat[0].bestarc = i;
			tempforwardpathlist.pathmat[0].bestnode = graph.fstarmatrix[i].tail;
		}
	}

	for (int i = graph.rstar[Destination]; i < graph.rstar[Destination+1]; ++i)
	{
		tempreversepathlist.pathmat[0].accessible_arcs.push_back(i);
		if( graph.rstarmatrix[i].weight < tempreversepathlist.pathmat[0].bestweight )
		{
			tempreversepathlist.pathmat[0].bestweight = graph.rstarmatrix[i].weight;
			tempreversepathlist.pathmat[0].bestarc = i;
			tempreversepathlist.pathmat[0].bestnode = graph.rstarmatrix[i].head;
		}
	}

	for (int i = 0; i < graph.nodes; i++)
	{
		cpp[i] = 0;
		mn[i] = 0;
	}

	cpp[Origin] = 1;
	cpp[Destination] = 1;
	
	bool allarcsvisited = 0;
	int P1sz, P2sz, Psz, psize, p1size, p2size;
	bool startfromforward = 1;

	srand(time(NULL));

	while(paths_obtained<K)
	{
		int mp1, mp2;//Meeting Point
		bool breakingvar = 0;
		double t1 = clock();
		while(true)
		{
			int tpsz = tempforwardpathlist.pathmat.size();
			int bpsz = tempreversepathlist.pathmat.size();
			cout<<"temp_f size = "<<tpsz<<endl;
			cout<<"temp_b size = "<<bpsz<<endl;
			if (tpsz*bpsz==0)
			{
				allarcsvisited = 1;
				break;
			}
			bool breakingvarinloop = 0;

			SPATH bestfpath, bestbpath;
			P1sz = P1.pathmat.size();
			P2sz = P2.pathmat.size();

			if(startfromforward)
			{	
				sort(tempforwardpathlist.pathmat.begin(), tempforwardpathlist.pathmat.end(),bestweightsort());
				bestfpath.weight = tempforwardpathlist.pathmat[0].bestweight;
				bestfpath.pathlist = tempforwardpathlist.pathmat[0].pathlist;
				bestfpath.pathlist.push_back(tempforwardpathlist.pathmat[0].bestnode);
				bestfpath.end = tempforwardpathlist.pathmat[0].bestnode;
				bestfpath.accessible_arcs = {};
				tempforwardpathlist.pathmat[0].accessible_arcs.erase(std::remove(tempforwardpathlist.pathmat[0].accessible_arcs.begin(), tempforwardpathlist.pathmat[0].accessible_arcs.end(), tempforwardpathlist.pathmat[0].bestarc), tempforwardpathlist.pathmat[0].accessible_arcs.end());
				int tempfpsz = tempforwardpathlist.pathmat[0].accessible_arcs.size();
				//UPDATING BEST ACCESSIBLE ARC OR REMOVING THE PATH IF ACCESSIBLE ARC LIST IS EMPTY
				if(tempfpsz == 0)
				{
					tempforwardpathlist.pathmat.erase(tempforwardpathlist.pathmat.begin());
				}
				else
				{
					double mintempweight = 32767;
					for (int i = 0; i < tempfpsz; ++i)
					{
						int arcnumber = tempforwardpathlist.pathmat[0].accessible_arcs[i];
						double testweight  = tempforwardpathlist.pathmat[0].weight+graph.fstarmatrix[arcnumber].weight;
						if ( testweight < mintempweight )
						{
							mintempweight = testweight;
							tempforwardpathlist.pathmat[0].bestweight = mintempweight;
							tempforwardpathlist.pathmat[0].bestarc = arcnumber;
							tempforwardpathlist.pathmat[0].bestnode = graph.fstarmatrix[arcnumber].tail;
						}
					}
				}
				//GIVING THE BEST AND ACCESSIBLE VALUES OF THE BEST PATH
				int tempfsz = tempforwardpathlist.pathmat.size();
				minweightf = 32767;
				s = 0;
				for (int i = graph.fstar[bestfpath.end]; i < graph.fstar[bestfpath.end + 1]; ++i)
				{
					if(find(bestfpath.pathlist.begin(),bestfpath.pathlist.end(),graph.fstarmatrix[i].tail)==bestfpath.pathlist.end())
					{
						bestfpath.accessible_arcs.push_back(i);
						if(bestfpath.weight+graph.fstarmatrix[i].weight < minweightf)
						{
							s+=1;
							bestfpath.bestweight = bestfpath.weight+graph.fstarmatrix[i].weight;
							minweightf = bestfpath.weight+graph.fstarmatrix[i].weight;
							bestfpath.bestarc = i;
							bestfpath.bestnode = graph.fstarmatrix[i].tail;
						}
					}
				}	

				breakingvarinloop = 0;

				if (s!=0)
				{
					P1.pathmat.push_back(SPATH());
					tempforwardpathlist.pathmat.push_back(SPATH());
					P1.pathmat[P1sz] = bestfpath;
					tempforwardpathlist.pathmat[tempfsz] = bestfpath;
					for (int i = 0; i < P2sz; ++i)
					{	
						if ((P1.pathmat[P1sz].end == P2.pathmat[i].end)&&(mn[P2.pathmat[i].end]==0))
						{
							mn[P2.pathmat[i].end] = 1;
							if (cpp[P2.pathmat[i].end]==0)
							{
								if(kspath::cyclic(mergepath(P1.pathmat[P1sz],P2.pathmat[i]),mn)==0)
								{
									mp1 = P1sz;
									mp2 = i;
									breakingvarinloop = 1;
									break;
								}
							}
						}
					}
				}
				tempfsz = tempforwardpathlist.pathmat.size();
				if (tempfsz==0)
				{
					allarcsvisited = 1;
					break;
				}
				if (breakingvarinloop)
				{
					startfromforward = 0;
					break;
				}
			}
			startfromforward = 1;
			sort(tempreversepathlist.pathmat.begin(), tempreversepathlist.pathmat.end(),bestweightsort());
			bestbpath.weight = tempreversepathlist.pathmat[0].bestweight;
			bestbpath.pathlist = tempreversepathlist.pathmat[0].pathlist;
			bestbpath.pathlist.push_back(tempreversepathlist.pathmat[0].bestnode);
			bestbpath.end = tempreversepathlist.pathmat[0].bestnode;
			bestbpath.accessible_arcs = {};
			tempreversepathlist.pathmat[0].accessible_arcs.erase(std::remove(tempreversepathlist.pathmat[0].accessible_arcs.begin(), tempreversepathlist.pathmat[0].accessible_arcs.end(), tempreversepathlist.pathmat[0].bestarc), tempreversepathlist.pathmat[0].accessible_arcs.end());
			int tempbpsz = tempreversepathlist.pathmat[0].accessible_arcs.size();
			if(tempbpsz == 0)
			{
				tempreversepathlist.pathmat.erase(tempreversepathlist.pathmat.begin());
			}
			else
			{
				double mintempweight = 32767;
				for (int i = 0; i < tempbpsz; ++i)
				{
					int arcnumber = tempreversepathlist.pathmat[0].accessible_arcs[i];
					double testweight  = tempreversepathlist.pathmat[0].weight+graph.rstarmatrix[arcnumber].weight;
					if ( testweight < mintempweight)
					{
						mintempweight = testweight;
						tempreversepathlist.pathmat[0].bestweight = mintempweight;
						tempreversepathlist.pathmat[0].bestarc = arcnumber;
						tempreversepathlist.pathmat[0].bestnode = graph.rstarmatrix[arcnumber].head;
					}
				}
			}
			int tempbsz = tempreversepathlist.pathmat.size();
			minweightb = 32767;
			s = 0;
			for (int i = graph.rstar[bestbpath.end]; i < graph.rstar[bestbpath.end+1]; ++i)
			{
				if(find(bestbpath.pathlist.begin(),bestbpath.pathlist.end(),graph.rstarmatrix[i].head)==bestbpath.pathlist.end())
				{
					bestbpath.accessible_arcs.push_back(i);
					if(bestbpath.weight+graph.rstarmatrix[i].weight < minweightb)
					{
						s+=1;
						bestbpath.bestweight = bestbpath.weight+graph.rstarmatrix[i].weight;
						minweightb = bestbpath.weight+graph.rstarmatrix[i].weight;
						bestbpath.bestarc = i;
						bestbpath.bestnode = graph.rstarmatrix[i].head;
					}
				}
			}
			breakingvarinloop = 0;
			P1sz = P1.pathmat.size();
			if (s!=0)
			{
				P2.pathmat.push_back(SPATH());
				tempreversepathlist.pathmat.push_back(SPATH());
				P2.pathmat[P2sz] = bestbpath;
				tempreversepathlist.pathmat[tempbsz] = bestbpath;
				for (int i = 0; i < P1sz; ++i)
				{
					if ((P2.pathmat[P2sz].end == P1.pathmat[i].end)&&(mn[P1.pathmat[i].end]==0))
					{
						mn[P1.pathmat[i].end] = 1;
						if (cpp[P1.pathmat[i].end]==0)
						{
							if(kspath::cyclic(mergepath(P1.pathmat[i],P2.pathmat[P2sz]),mn)==0)
							{
								mp1 = i;
								mp2 = P2sz;
								breakingvarinloop = 1;
								break;
							}
						}
					}
				}
			}
			tempbsz = tempreversepathlist.pathmat.size();
			if (tempbsz==0)
			{
				allarcsvisited = 1;
				break;
			}
			if (breakingvarinloop)
			{
				break;
			}
		}
		double t2 = clock();
		paths_obtained = P.pathmat.size();
		if (paths_obtained<K)
		{
			if (allarcsvisited)
			{
				SPATH temppath;
				bool samepath = 0;
				Psz = P.pathmat.size();
				P1sz = P1.pathmat.size();
				P2sz = P2.pathmat.size();
				for (int i = 0; i < P1sz; ++i)
				{
					for (int j = 0; j < P2sz; ++j)
					{
						double connectingweight;
						int arcindex;
						if (P1.pathmat[i].end == P2.pathmat[j].end)
						{
							temppath = mergepath(P1.pathmat[i],P2.pathmat[j]);
							samepath = 0;
							Psz = P.pathmat.size();
							for (int k = 0; k < Psz; ++k)
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
							Psz = P.pathmat.size();
							P.pathmat.push_back(SPATH());
							P.pathmat[Psz] = temppath;
							sort(P.pathmat.begin(), P.pathmat.end(), weightsort());
						}
						else
						{
							arcindex = -1;
							for (int k = graph.fstar[P1.pathmat[i].end]; k < graph.fstar[ P1.pathmat[i].end + 1 ]; ++k)
							{
								if (P2.pathmat[j].end==graph.fstarmatrix[k].tail)
								{
									arcindex = k;
									connectingweight = graph.fstarmatrix[k].weight;
								}	
							}
							if (arcindex == -1)
							{
								continue;
							}
							temppath = mergepath(P1.pathmat[i], P2.pathmat[j], connectingweight);
							int psize = P.pathmat.size();
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
							
							P.pathmat.push_back(SPATH());
							P.pathmat[psize] = temppath;
							sort(P.pathmat.begin(), P.pathmat.end(),weightsort());
						}
					}
				}
			}
			else
			{
				double boundweight = P1.pathmat[mp1].weight + P2.pathmat[mp2].weight;
				SPATH temppath = mergepath(P1.pathmat[mp1],P2.pathmat[mp2]);
				int temppathsize = temppath.pathlist.size();
				int psize = P.pathmat.size();
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
				P.pathmat.push_back(SPATH());
				P.pathmat[psize] = temppath;
				sort(P.pathmat.begin(), P.pathmat.end(),weightsort());
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
							P.pathmat.push_back(SPATH());
							P.pathmat[psize] = temppath;
							sort(P.pathmat.begin(),P.pathmat.end(),weightsort());
						}
						else
						{
							arcindex = -1;
							for (int k = graph.fstar[P1.pathmat[i].end]; k < graph.fstar[ P1.pathmat[i].end + 1 ]; ++k)
							{
								//if((P1.pathmat[i].end==graph.fstarmatrix[k].head)&&(P2.pathmat[j].end==graph.fstarmatrix[k].tail))
								if(P2.pathmat[j].end==graph.fstarmatrix[k].tail)
								{
									arcindex = k;
									connectingweight = graph.fstarmatrix[k].weight;
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
								P.pathmat.push_back(SPATH());
								P.pathmat[psize] = temppath;
								sort(P.pathmat.begin(), P.pathmat.end(),weightsort());
							}
						}
					}
				}
			}
		}
		else
		{
			break;
		}
		double t3 = clock();
		//cout<<"Preprocessing time:"<<(t2 - t1) / CLOCKS_PER_SEC<<endl;
		//cout<<"Postprocessing time:"<<(t3 - t2) / CLOCKS_PER_SEC<<endl;
		paths_obtained = P.pathmat.size();
		if (allarcsvisited)
		{
			break;
		}
	}
	/*int p1ss = P1.pathmat.size();
	int p2ss = P2.pathmat.size();
	cout<<"P1:\n";
	for (int i = 0; i < p1ss; ++i)
	{
		int p1list = P1.pathmat[i].pathlist.size();
		cout<<"Weight:"<<P1.pathmat[i].weight<<' '<<"PATH:";
		for (int j = 0; j < p1list; ++j)
		{
			cout<<P1.pathmat[i].pathlist[j]<<' ';
		}
		cout<<endl;
	}
	cout<<"P2:\n";
	for (int i = 0; i < p2ss; ++i)
	{
		int p2list = P2.pathmat[i].pathlist.size();
		cout<<"Weight:"<<P2.pathmat[i].weight<<' '<<"PATH:";
		for (int j = 0; j < p2list; ++j)
		{
			cout<<P2.pathmat[i].pathlist[j]<<' ';
		}
		cout<<endl;
	}*/
	cout<<"paths_obtained:"<<paths_obtained<<endl;
	return P;
}