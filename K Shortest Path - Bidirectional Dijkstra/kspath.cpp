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
#include <limits>
#include "kspath.h"
using namespace std;
#define min(a,b) (a<b)?a:b
#define max(a,b) (a>b)?a:b

bool kspath::acyclic(PATH a, int b)
{
	int size = a.pathlist.size();
	for (int i = 0; i < size; ++i)
	{
		if (a.pathlist[i]==b)
		{
			return 0;
		}
	}
	return 1;
}

void kspath::heapify(vector<int> &heap, int n, int i, vector<YENPATH> &path)
{
	int smallest = i;  
	int l = 2*i + 1;  
	int r = 2*i + 2;
	if (l<n)
	{
		if (path[heap[l]].weight<path[heap[smallest]].weight)
		{
			smallest = l;
		}
	}
	if (r<n)
	{
		if (path[heap[r]].weight<path[heap[smallest]].weight)
		{
			smallest = r;
		}
	}  
	if (smallest != i)
	{
		swap(heap[i],heap[smallest]);
		swap(path[heap[i]].position,path[heap[smallest]].position);
		heapify(heap, n, smallest, path);
	}
}

void kspath::heapify(vector<int> &heap, int n, int i, vector<NODE> &node)
{
	int smallest = i;
	int l = 2*i+1;
	int r = 2*i+2;
	if (l<n)
	{
		int lpos = node[heap[l]].permanent;
		int spos = node[heap[smallest]].permanent;
		double lweight = node[heap[l]].pathmat[lpos].weight;
		double sweight = node[heap[smallest]].pathmat[spos].weight;
		if (lweight<sweight)
		{
			smallest = l;
		}
	}
	if (r<n)
	{
		int rpos = node[heap[r]].permanent;
		int spos = node[heap[smallest]].permanent;
		double rweight = node[heap[r]].pathmat[rpos].weight;
		double sweight = node[heap[smallest]].pathmat[spos].weight;
		if (rweight<sweight)
		{
			smallest = r;
		}
	}
	if (smallest!=i)
	{
		swap(node[heap[i]].position,node[heap[smallest]].position);
		swap(heap[i],heap[smallest]);
		heapify(heap,n,smallest,node);
	}
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

YENPATH kspath::sp(GRAPH graph, int Origin, int Destination)
{
	vector<YENPATH> path;
	bool *visited = new bool [graph.nodes];
	vector<int> heap;
	//Initialization
	for (int i = 0; i < graph.nodes; ++i)
	{
		path.push_back(YENPATH());
		path[i].weight = 32767;
		path[i].pathlist = {};
		visited[i] = 0;
		path[i].position = -1;
	}
	path[Origin].weight = 0;
	path[Origin].pathlist.push_back(Origin);
	path[Origin].position = 0;
	visited[Origin] = 1;
	heap.push_back(Origin);
	int heapsize = heap.size();
	while(heapsize>0)
	{
		int root = heap[0];
		if (root==Destination)
		{
			path[Destination].found = 1;
			return path[Destination];
		}
		visited[root] = 1;
		path[heap[heapsize-1]].position = 0;
		swap(heap[0],heap[heapsize-1]);
		path[root].position = -1;
		heap.pop_back();
		heapsize = heap.size();
		if (heapsize==2)
		{
			if (path[heap[0]].weight>path[heap[1]].weight)
			{
				swap(heap[0],heap[1]);
				swap(path[heap[0]].position,path[heap[1]].position);
			}
		}
		if (heapsize>2)
		{
			heapify(heap,heapsize,0,path);
		}
		for (int i = graph.fstar[root]; i < graph.fstar[root+1]; ++i)
		{
			if (visited[graph.fstarmatrix[i].tail])
			{
				continue;
			}
			if (graph.fstarmatrix[i].weight>32000)
			{
				continue;
			}
			if (path[root].weight+graph.fstarmatrix[i].weight < path[graph.fstarmatrix[i].tail].weight)
			{
				path[graph.fstarmatrix[i].tail].weight = path[root].weight + graph.fstarmatrix[i].weight;
				path[graph.fstarmatrix[i].tail].pathlist = path[root].pathlist;
				path[graph.fstarmatrix[i].tail].pathlist.push_back(graph.fstarmatrix[i].tail);
				if (path[graph.fstarmatrix[i].tail].position==-1)
				{
					heap.push_back(graph.fstarmatrix[i].tail);
					path[graph.fstarmatrix[i].tail].position = heapsize-1; 	
					heapsize = heap.size();
					for (int j = heapsize-1; j > 0 ; j=(j-1)/2)
					{
						if (path[heap[j]].weight<path[heap[(j-1)/2]].weight)
						{
							swap(heap[j],heap[(j-1)/2]);
							swap(path[heap[j]].position,path[heap[(j-1)/2]].position);
						}
					}
				}
				else
				{
					int tailposition = path[graph.fstarmatrix[i].tail].position;
					for (int j = tailposition; j > 0; j=(j-1)/2)
					{
						if (path[heap[j]].weight<path[heap[(j-1)/2]].weight)
						{
							swap(heap[j],heap[(j-1)/2]);
							swap(path[heap[j]].position,path[heap[(j-1)/2]].position);
						}
					}
				}
			}
		}
		heapsize = heap.size();
	}
	if (visited[Destination]==0)
	{
		YENPATH P;
		P.found = 0;
		return P;
	}
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
	graphcopy.fstar = {};
	for (int i = 0; i <= graphcopy.nodes; ++i)
	{
		graphcopy.fstar.push_back(graph.fstar[i]);
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

PATHMAT kspath::dijkstra(GRAPH graph, int Origin, int Destination, int K)
{
	//Initialization Block
	PATHMAT P;
	vector<int> heap;
	vector<NODE> n;
	int heapsize;
	P.kn = 0;
	P.km = 0;
	
	for (int i = 0; i < graph.nodes; ++i)
	{
		n.push_back(NODE());
		n[i].permanent = 0;
		n[i].finite = 0;
		n[i].position = -1;
		for (int j = 0; j < K; ++j)
		{
			n[i].pathmat.push_back(PATH());
			n[i].pathmat[j].weight = 32767;
		}
	}

	heap.push_back(Origin);
	n[Origin].position = 0;
	n[Origin].finite = 1;
	n[Origin].pathmat[0].weight = 0;
	n[Origin].pathmat[0].pathlist = {};
	n[Origin].pathmat[0].pathlist.push_back(Origin);

	//Loop
	ofstream output;
	output.open("output.txt");
	heapsize = heap.size();
	while( (n[Destination].permanent < K) && (heapsize>0) )
	{
		P.kn+=1;
		heapsize = heap.size();
		int root = heap[0];
		int rootp = n[root].permanent;
		int rootp_sz = n[root].pathmat[rootp].pathlist.size();
		n[heap[heapsize-1]].position = 0;
		n[root].position = -1;
		swap(heap[0],heap[heapsize-1]);
		heap.pop_back();
		heapsize = heap.size();
		n[root].permanent+=1;

		if (heapsize==2)
		{
			int perm0 = n[heap[0]].permanent;
			int perm1 = n[heap[1]].permanent;
			if (n[heap[0]].pathmat[perm0].weight>n[heap[1]].pathmat[perm1].weight)
			{
				n[heap[0]].position = 1;
				n[heap[1]].position = 0;
				swap(heap[0],heap[1]);
			}
		}
		if (heapsize>2)
		{
			heapify(heap,heapsize,0,n);
		}
		for (int i = graph.fstar[root]; i < graph.fstar[root+1]; ++i)
		{
			P.km+=1;
			int tail = graph.fstarmatrix[i].tail;
			if (n[tail].pathmat[K-1].weight <= n[root].pathmat[rootp].weight+graph.fstarmatrix[i].weight)
			{
				continue;
			}
			if (acyclic(n[root].pathmat[rootp],tail))
			{
				int insert_pos = n[tail].permanent;
				for (int j = n[tail].finite-1; j >= n[tail].permanent; --j)
				{
					if (n[tail].pathmat[j].weight <= n[root].pathmat[rootp].weight + graph.fstarmatrix[i].weight)
					{
						insert_pos = j+1;
						break;
					}
				}
				for (int j = n[tail].finite; j > insert_pos ; --j)
				{
					if (j==K)
					{
						continue;
					}
					n[tail].pathmat[j] = n[tail].pathmat[j-1];
				}
				n[tail].pathmat[insert_pos] = n[root].pathmat[rootp];
				n[tail].pathmat[insert_pos].weight += graph.fstarmatrix[i].weight;
				n[tail].pathmat[insert_pos].pathlist.push_back(tail);
				if (n[tail].finite<K)
				{
					n[tail].finite+=1;
				}
				if (n[tail].position==-1)
				{
					heap.push_back(tail);
					heapsize = heap.size();
					n[tail].position = heapsize-1;
				}
				if (insert_pos==n[tail].permanent)
				{
					for (int j = n[tail].position; j > 0; j=(j-1)/2)
					{
						int parentkey = n[heap[(j-1)/2]].permanent;
						int childkey = n[heap[j]].permanent;
						double parentweight,childweight;
						if (parentkey<K)
						{
							parentweight = n[heap[(j-1)/2]].pathmat[parentkey].weight;
						}
						else
						{
							parentweight = 32767;
						}
						if (childkey<K)
						{
							childweight = n[heap[j]].pathmat[childkey].weight;
						}
						else
						{
							childweight = 32767;
						}
						if (childweight<parentweight)
						{
							swap(heap[j],heap[(j-1)/2]);
							swap(n[heap[j]].position,n[heap[(j-1)/2]].position);
						}
						else
						{
							break;
						}
					}
				}

			}
		}
		int curr_root_key_pos = n[root].permanent;
		
		if (curr_root_key_pos==K)
		{
			continue;
		}
		
		if (n[root].pathmat[curr_root_key_pos].weight<32000)
		{
			heap.push_back(root);
			heapsize = heap.size();
			n[root].position = heapsize-1;
			for (int i = heapsize-1; i > 0; i=(i-1)/2)
			{
				int keyp = n[heap[(i-1)/2]].permanent;
				int keyc = n[heap[i]].permanent;
				double pweight,cweight;
				if (keyp<K)
				{
					pweight = n[heap[(i-1)/2]].pathmat[keyp].weight;
				}
				else
				{
					pweight = 32767;
				}
				if (keyc<K)
				{
					cweight = n[heap[i]].pathmat[keyc].weight;
				}
				else
				{
					cweight = 32767;
				}
				if (cweight<pweight)
				{
					swap(n[heap[i]].position,n[heap[(i-1)/2]].position);
					swap(heap[i],heap[(i-1)/2]);
				}
				else
				{
					break;
				}
			}
		}
		
	}
	for (int i = 0; i < n[Destination].permanent; ++i)
	{
		P.pathmat.push_back(PATH());
		P.pathmat[i].weight = n[Destination].pathmat[i].weight;
		P.pathmat[i].pathlist = n[Destination].pathmat[i].pathlist;
	}
	return P;
}
