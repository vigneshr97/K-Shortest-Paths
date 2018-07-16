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
#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include "kspath.h"
using namespace boost::multiprecision;
using namespace std;
#define min(a,b) (a<b)?a:b
#define max(a,b) (a>b)?a:b

bool kspath::cyclic(PATH a, int b)
{
	// ofstream t;
	// t.open("prime.csv",std::ios_base::app);
	// srand(time(NULL));
	// double t1 = clock();
	// int size = a.product.size();
	// for (int i = 0; i < size; ++i)
	// {
	// 	if (a.product[i]%prime[b]==0)
	// 	{
	// 		// double t2 = clock();
	// 		// t<<size<<","<<(t2-t1)/CLOCKS_PER_SEC<<endl;
	// 		return 1;
	// 	}
	// }
	// double t2 = clock();
	// t<<size<<","<<(t2-t1)/CLOCKS_PER_SEC<<endl;
	if (a.product[b%20]%prime[b]==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool kspath::cyclic_classic(PATH a, int b)
{
	// ofstream t;
	// t.open("classic.csv",std::ios_base::app);
	// srand(time(NULL));
	// double t1 = clock();
	int size = a.path.size();
	for (int i = 0; i < size; ++i)
	{
		if (a.path[i]==b)
		{
			// double t2 = clock();
			// t<<size<<","<<(t2-t1)/CLOCKS_PER_SEC<<endl;
			return 1;
		}
	}
	// double t2 = clock();
	// t<<size<<","<<(t2-t1)/CLOCKS_PER_SEC<<endl;
	return 0;
}

bool kspath::acyclic(BESTPATH n, int nodes)
{
	vector<int> count;
	for (int i = 0; i < nodes; ++i)
	{
		count.push_back(0);
	}
	int fsize = n.fpath.size();
	int bsize = n.bpath.size();
	for (int i = 0; i < fsize; ++i)
	{
		if (count[n.fpath[i]]>0)
		{
			return 0;
		}
		else
		{
			count[n.fpath[i]]+=1;
		}
	}
	for (int i = 0; i < bsize-1; ++i)
	{
		if (count[n.bpath[i]]>0)
		{
			return 0;
		}
		else
		{
			count[n.bpath[i]]+=1;
		}
	}
	return 1;
}

bool kspath::cyclic(PATH P1, PATH P2)
{
	int p1size = P1.path.size();
	int p2size = P2.path.size();
	for (int i = 0; i < p1size-1; ++i)
	{
		if (find(P2.path.begin(),P2.path.end(),P1.path[i])!=P2.path.end())
		{
			return 1;
		}
	}
	return 0;
}

void kspath::heapify(vector<int> &heap, int n, int i, vector<BESTPATH> &path, bool forward = 1)
{
	int smallest = i;  
	int l = 2*i + 1;  
	int r = 2*i + 2;
	if (forward)
	{
		if (l<n)
		{
			if (path[heap[l]].fweight<path[heap[smallest]].fweight)
			{
				smallest = l;
			}
		}
		if (r<n)
		{
			if (path[heap[r]].fweight<path[heap[smallest]].fweight)
			{
				smallest = r;
			}
		}  
		if (smallest != i)
		{
			swap(heap[i],heap[smallest]);
			swap(path[heap[i]].fposition,path[heap[smallest]].fposition);
			heapify(heap, n, smallest, path,1);	
		}
	}
	else
	{
		int smallest = i;  
		int l = 2*i + 1;  
		int r = 2*i + 2;
		if (l<n)
		{
			if (path[heap[l]].bweight<path[heap[smallest]].bweight)
			{
				smallest = l;
			}
		}
		if (r<n)
		{
			if (path[heap[r]].bweight<path[heap[smallest]].bweight)
			{
				smallest = r;
			}
		}  
		if (smallest != i)
		{
			swap(heap[i],heap[smallest]);
			swap(path[heap[i]].bposition,path[heap[smallest]].bposition);
			heapify(heap, n, smallest, path,0);
		}
	}
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
		double lweight = node[heap[l]].minheap[0].weight;
		double sweight = node[heap[smallest]].minheap[0].weight;
		if (lweight<sweight)
		{
			smallest = l;
		}
	}
	if (r<n)
	{
		double rweight = node[heap[r]].minheap[0].weight;
		double sweight = node[heap[smallest]].minheap[0].weight;
		if (rweight<sweight)
		{
			smallest = r;
		}
	}
	if (smallest!=i)
	{
		swap(node[heap[i]].position, node[heap[smallest]].position);
		swap(heap[i],heap[smallest]);
		heapify(heap,n,smallest,node);
	}	
}

void kspath::minheapify(vector<PATH> &minheap, vector<PATH> &maxheap, int n, int i)
{
	int smallest = i;
	int l = 2*i+1;
	int r = 2*i+2;
	
	if (l<n)
	{
		if (minheap[l].weight<minheap[smallest].weight)
		{
			smallest = l;
		}
	}
	
	if (r<n)
	{
		if (minheap[r].weight<minheap[smallest].weight)
		{
			smallest = r;
		}
	}
	
	if (smallest!=i)
	{
		int ipos = minheap[i].pos;
		int smallpos = minheap[smallest].pos;
		maxheap[ipos].pos = smallest;
		maxheap[smallpos].pos = i;
		swap(minheap[i],minheap[smallest]);
		minheapify(minheap,maxheap,n,smallest);
	}	
}

void kspath::maxheapify(vector<PATH> &maxheap, vector<PATH> &minheap, int n, int i)
{
	int highest = i;
	int l = 2*i+1;
	int r = 2*i+2;
	
	if (l<n)
	{
		if (maxheap[l].weight>maxheap[highest].weight)
		{
			highest = l;
		}
	}
	
	if (r<n)
	{
		if (maxheap[r].weight>maxheap[highest].weight)
		{
			highest = r;
		}
	}
	
	if (highest!=i)
	{
		int ipos = maxheap[i].pos;
		int highpos = maxheap[highest].pos;
		minheap[ipos].pos = highest;
		minheap[highpos].pos = i;
		swap(maxheap[i],maxheap[highest]);
		maxheapify(maxheap,minheap,n,highest);
	}	
}

bool kspath::same_path(YENPATH a, YENPATH b)
{
	double diff = (a.weight>b.weight)?(a.weight-b.weight):(b.weight-a.weight);
	int asize = a.path.size();
	int bsize = b.path.size();
	if(diff>0.001)
		return 0;
	else
	{
		if(asize!=bsize)
			return 0;
		else
		{
			for(int i=0;i<asize;i++)
			{
				if(a.path[i]!=b.path[i])
					return 0;
			}
		}
	}
	return 1;
}

bool kspath::same_path(PATH a, PATH b)
{
	double diff = (a.weight>b.weight)?(a.weight-b.weight):(b.weight-a.weight);
	int asize = a.path.size();
	int bsize = b.path.size();
	if(diff>0.001)
		return 0;
	else
	{
		if(asize!=bsize)
			return 0;
		else
		{
			for(int i=0;i<asize;i++)
			{
				if(a.path[i]!=b.path[i])
					return 0;
			}
		}
	}
	return 1;
}

bool kspath::same_path(BESTPATH a, BESTPATH b)
{
	PATH P1, P2;
	P1.weight = a.fweight + a.bweight;
	P2.weight = b.fweight + b.bweight;
	int asize1 = a.fpath.size();
	int asize2 = a.bpath.size();
	int bsize1 = b.fpath.size();
	int bsize2 = b.bpath.size();
	for (int i = 0; i < asize1; ++i)
	{   
		P1.path.push_back(a.fpath[i]);
	}
	for (int i = asize2-2; i >= 0; --i)
	{
		P1.path.push_back(a.bpath[i]);
	}
	for (int i = 0; i < bsize1; ++i)
	{   
		P2.path.push_back(b.fpath[i]);
	}
	for (int i = bsize2-2; i >= 0; --i)
	{
		P2.path.push_back(b.bpath[i]);
	}
	return same_path(P1,P2);
}

YENPATH kspath::mergepath( YENPATH P1, YENPATH P2 )
{
	YENPATH P;
	int p1size = P1.path.size();
	int p2size = P2.path.size();
	P.weight = P1.weight + P2.weight;
	P.path.reserve(p1size+p2size-1);
	P.path.insert( P.path.end(), P1.path.begin(), P1.path.end() );
	P.path.insert( P.path.end(), P2.path.begin()+1, P2.path.end() );
	P.found = P2.found;
	return P;
}

PATH kspath::mergepath(PATH P1, PATH P2)
{
	PATH P;
	P.weight = P1.weight+P2.weight;
	int p1size = P1.path.size();
	int p2size = P2.path.size();
	for (int i = 0; i < p1size; ++i)
	{
		P.path.push_back(P1.path[i]);
	}
	for (int i = p2size-2; i >= 0; --i)
	{
		P.path.push_back(P2.path[i]);
	}
	return P;
}

YENPATH kspath::sp(GRAPH &graph, int Origin, int Destination)
{
	vector<YENPATH> path;
	bool *visited = new bool [graph.nodes];
	vector<int> heap;
	
	for (int i = 0; i < graph.nodes; ++i)
	{
		path.push_back(YENPATH());
		path[i].weight = 32767;
		visited[i] = 0;
		path[i].position = -1;
	}
	path[Origin].weight = 0;
	path[Origin].path.push_back(Origin);
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
		for (int i = graph.fstarposition[root]; i < graph.fstarposition[root+1]; ++i)
		{
			if (visited[graph.fstarmatrix[i].head])
			{
				continue;
			}
			if (graph.fstarmatrix[i].weight>32000)
			{
				continue;
			}
			if (path[root].weight+graph.fstarmatrix[i].weight < path[graph.fstarmatrix[i].head].weight)
			{
				path[graph.fstarmatrix[i].head].weight = path[root].weight + graph.fstarmatrix[i].weight;
				path[graph.fstarmatrix[i].head].path = path[root].path;
				path[graph.fstarmatrix[i].head].path.push_back(graph.fstarmatrix[i].head);
				if (path[graph.fstarmatrix[i].head].position==-1)
				{
					heap.push_back(graph.fstarmatrix[i].head);
					path[graph.fstarmatrix[i].head].position = heapsize-1;  
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
					int headposition = path[graph.fstarmatrix[i].head].position;
					for (int j = headposition; j > 0; j=(j-1)/2)
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

YENPATHLIST kspath::yen(GRAPH &graph, int Origin, int Destination, int K)
{
	GRAPH graphcopy;
	YENPATHLIST P;
	YENPATHLIST temp_P;
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
		graphcopy.fstarmatrix[i].tail = graph.fstarmatrix[i].tail;
		graphcopy.fstarmatrix[i].head = graph.fstarmatrix[i].head;
		graphcopy.fstarmatrix[i].weight = graph.fstarmatrix[i].weight;
	}
	for (int i = 0; i <= graphcopy.nodes; ++i)
	{
		graphcopy.fstarposition.push_back(0);
	}
	for (int i = 0; i <= graphcopy.nodes; ++i)
	{
		graphcopy.fstarposition[i] = graph.fstarposition[i];
	}

	P.pathlist.push_back(YENPATH());
	
	shortest_path = kspath::sp(graphcopy,Origin,Destination);
	P.pathlist[0] = shortest_path;

	while(paths_obtained<K)
	{
		YENPATH rootpath, spurpath;
		paths_obtained = P.pathlist.size();
		shortest_path = P.pathlist[ paths_obtained - 1 ];
		rootpath.weight = 0;
		spurpath.weight = 0;
		int spsize = shortest_path.path.size();
		for (int i = 0; i < spsize-1; ++i)
		{
			int spurnode = shortest_path.path[i];
			for (int j = 0; j <=i ; ++j)
			{
				rootpath.path.push_back(shortest_path.path[j]);
			}
			int rootpathsize = rootpath.path.size();
			for (int j = 0; j < paths_obtained; ++j)
			{
				bool vsamepath = 1;
				for (int k = 0; k <= i; ++k)
				{
					if (P.pathlist[j].path[k]==rootpath.path[k])
					{
						continue;
					}
					else
					{
						vsamepath = 0;
						break;
					}
				}
				if (vsamepath)
				{
					for (int k = graphcopy.fstarposition[P.pathlist[j].path[i]]; k < graphcopy.fstarposition[P.pathlist[j].path[i]+1]; ++k)
					{
						if (P.pathlist[j].path[i+1]==graphcopy.fstarmatrix[k].head)
						{
							graphcopy.fstarmatrix[k].weight = 32767;
						}
					}
				}
				rootpathsize = rootpath.path.size()-1;
				for (int k = 0; k < rootpathsize; ++k)
				{
					for (int l = graphcopy.fstarposition[rootpath.path[k]]; l < graphcopy.fstarposition[ rootpath.path[k] + 1 ]; ++l)
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
				for (int j = graph.fstarposition[shortest_path.path[i]]; j < graph.fstarposition[shortest_path.path[i]+1]; ++j)
				{
					if (shortest_path.path[i+1]==graph.fstarmatrix[j].head)
					{
						rootpath.weight+=graphcopy.fstarmatrix[j].weight;
					}
				}
				continue;
			}
			innershortpath = kspath::mergepath(rootpath,spurpath);
			temppsize = temp_P.pathlist.size();
			bool continuevar = 0;
			for (int j = 0; j < temppsize; ++j)
			{
				if (same_path(innershortpath,temp_P.pathlist[j]))
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
				for (int j = graph.fstarposition[shortest_path.path[i]]; j < graph.fstarposition[shortest_path.path[i]+1]; ++j)
				{
					if (shortest_path.path[i+1]==graph.fstarmatrix[j].head)
					{
						rootpath.weight+=graphcopy.fstarmatrix[j].weight;
					}
				}
				continue;
			}
			temp_P.pathlist.push_back(YENPATH());
			temp_P.pathlist[temppsize] = innershortpath;
			for (int j = 0; j < graphcopy.arcs; ++j)
			{
				graphcopy.fstarmatrix[j].weight = graph.fstarmatrix[j].weight;
			}
			for (int j = graph.fstarposition[shortest_path.path[i]]; j < graph.fstarposition[shortest_path.path[i]+1]; ++j)
			{
				if (shortest_path.path[i+1]==graph.fstarmatrix[j].head)
				{
					rootpath.weight+=graphcopy.fstarmatrix[j].weight;
				}
			}
		}
		temppsize = temp_P.pathlist.size();
		if (temppsize==0)
		{
			break;
		}
		sort(temp_P.pathlist.begin(),temp_P.pathlist.end(),yenweightsort());
		paths_obtained = P.pathlist.size();
		P.pathlist.push_back(YENPATH());
		P.pathlist[paths_obtained] = temp_P.pathlist[0];
		temp_P.pathlist.erase(temp_P.pathlist.begin());
		paths_obtained = P.pathlist.size();
	}
	return P;
}

void kspath::arc_processing_classic12(GRAPH &graph, vector<int> &heap, vector<NODE> &n, int K, bool forward = 1)
{
	// ofstream t;
	// t.open("list.csv",std::ios_base::app);
	// srand(time(NULL));
	// double t1 = clock();
	int root = heap[0];
	int heappathsize = n[root].minheap.size();
	int pathlistsize = n[root].pathlist.size();
	int heapsize = heap.size();

	n[root].permanent += 1;
	int rootp = n[root].permanent;
	int rootf = n[root].finite;
	n[root].pathlist.push_back(PATH());

	n[root].pathlist[pathlistsize] = n[root].minheap[0];

	for (int i = 0; i < heappathsize-1; ++i)
	{
		n[root].minheap[i] = n[root].minheap[i+1];
	}
	n[root].minheap.pop_back();
	
	n[heap[heapsize-1]].position = 0;
	n[root].position = -1;
	swap(heap[0],heap[heapsize-1]);
	heap.pop_back();

	heappathsize = n[root].minheap.size();
	int minheapsize;
	heapsize = heap.size();

	if (heapsize==2)
	{
		if (n[heap[0]].minheap[0].weight>n[heap[1]].minheap[0].weight)
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

	int start, end;
	double arcweight;
	int head;
	
	if (forward)
	{
		start = graph.fstarposition[root];
		end = graph.fstarposition[root+1];
	}
	else
	{
		start = graph.rstarposition[root];
		end = graph.rstarposition[root+1];	
	}


	// double t2 = clock();
	for (int i = start; i < end; ++i)
	{
		if (forward)
		{
			arcweight = graph.fstarmatrix[i].weight;
			head = graph.fstarmatrix[i].head;
		}
		else
		{
			arcweight = graph.rstarmatrix[i].weight;
			head = graph.rstarmatrix[i].tail;	
		}

		minheapsize = n[head].minheap.size();
		if (n[head].permanent == K)
		{
			continue;
		}

		if (n[head].finite == K)
		{
			if (n[head].minheap[minheapsize-1].weight <= n[root].pathlist[pathlistsize].weight + arcweight)
			{
				continue;
			}
		}
		if (cyclic_classic(n[root].pathlist[rootp-1],head)==0)
		{	
			if (n[head].finite == K)
			{
				n[head].minheap.pop_back();
			}
			n[head].minheap.push_back(PATH());
			minheapsize = n[head].minheap.size();
			n[head].minheap[minheapsize-1] = n[root].pathlist[pathlistsize];
			n[head].minheap[minheapsize-1].weight += arcweight;
			n[head].minheap[minheapsize-1].path.push_back(head);
			
			for (int j = minheapsize-1; j > 0 ; --j)
			{
				if (n[head].minheap[j].weight < n[head].minheap[j-1].weight)
				{
					swap(n[head].minheap[j],n[head].minheap[j-1]);
				}
			}
			
			if (n[head].finite < K)
			{
				n[head].finite += 1;
			}
			
			if (n[head].position==-1)
			{
				heap.push_back(head);
				heapsize = heap.size();
				n[head].position = heapsize-1;
			}

			for (int j = n[head].position; j > 0; j=(j-1)/2)
			{
				int parentkey = n[heap[(j-1)/2]].permanent;
				int parent_pathsfound = n[heap[(j-1)/2]].finite;
				int childkey = n[heap[j]].permanent;
				int child_pathsfound = n[heap[j]].finite;
				double parentweight,childweight;
				if (parentkey<parent_pathsfound)
				{
					parentweight = n[heap[(j-1)/2]].minheap[0].weight;
				}
				else
				{
					parentweight = 32767;
				}
				if (childkey<child_pathsfound)
				{
					childweight = n[heap[j]].minheap[0].weight;
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
	// double t3 = clock();
	if (n[root].permanent < n[root].finite)
	{
		heap.push_back(root);
		heapsize = heap.size();
		n[root].position = heapsize-1;
		for (int i = heapsize-1; i > 0; i=(i-1)/2)
		{
			int keyp = n[heap[(i-1)/2]].permanent;
			int ppfound = n[heap[(i-1)/2]].finite;
			int keyc = n[heap[i]].permanent;
			int cpfound = n[heap[i]].finite;
			double pweight,cweight;
			if (keyp<ppfound)
			{
				pweight = n[heap[(i-1)/2]].minheap[0].weight;
			}
			else
			{
				pweight = 32767;
			}
			if (keyc<cpfound)
			{
				cweight = n[heap[i]].minheap[0].weight;
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
	// double t4 = clock();
	// t<<heappathsize<<','<<minheapsize<<','<<(t2-t1)/CLOCKS_PER_SEC<<','<<(t3-t2)/CLOCKS_PER_SEC<<','<<(t4-t3)/CLOCKS_PER_SEC<<','<<endl;
}

PATHLIST kspath::ksp_single12(GRAPH &graph, int Origin, int Destination, int K)
{
	PATHLIST P;
	vector<int> heap;
	vector<NODE> n;
	int heapsize;
	n = {};

	for (int i = 0; i < graph.nodes; ++i)
	{
		n.push_back(NODE());
		n[i].permanent = 0;
		n[i].finite = 0;
		n[i].position = -1;
	}

	n[Origin].minheap.push_back(PATH());
	heap.push_back(Origin);
	n[Origin].position = 0;
	n[Origin].finite = 1;
	n[Origin].minheap[0].weight = 0;
	n[Origin].minheap[0].path.push_back(Origin);
	heapsize = heap.size();
	int forwardpasses = 0;
	
	while((n[Destination].permanent<K)&&(heapsize>0))
	{
		arc_processing_classic12(graph, heap, n, K, 1);
		heapsize = heap.size();
	}
	for (int i = 0; i < n[Destination].permanent; ++i)
	{
		P.pathlist.push_back(PATH());
		P.pathlist[i].weight = n[Destination].pathlist[i].weight;
		P.pathlist[i].path = n[Destination].pathlist[i].path;
	}
	return P;
}

void kspath::arc_processing_classic1(GRAPH &graph, vector<int> &heap, vector<NODE> &n, int K, bool forward = 1)
{
	int heapsize = heap.size();
	int root = heap[0];
	int heappathsize = n[root].minheap.size();
	int pathlistsize = n[root].pathlist.size();

	n[root].permanent+=1;
	int rootp = n[root].permanent;
	int rootf = n[root].finite;
	n[root].pathlist.push_back(PATH());
	n[root].pathlist[rootp-1] = n[root].minheap[0];
	for (int i = 0; i < heappathsize-1; ++i)
	{
		n[root].minheap[i] = n[root].minheap[i+1];
	}
	n[root].minheap.pop_back();
	
	n[heap[heapsize-1]].position = 0;
	n[root].position = -1;
	swap(heap[0],heap[heapsize-1]);
	heap.pop_back();

	heappathsize = n[root].minheap.size();
	heapsize = heap.size();

	if (heapsize==2)
	{
		if (n[heap[0]].minheap[0].weight>n[heap[1]].minheap[0].weight)
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

	int start, end;
	double arcweight;
	int head;
	
	if (forward)
	{
		start = graph.fstarposition[root];
		end = graph.fstarposition[root+1];
	}
	else
	{
		start = graph.rstarposition[root];
		end = graph.rstarposition[root+1];	
	}

	
	for (int i = start; i < end; ++i)
	{
		if (forward)
		{
			arcweight = graph.fstarmatrix[i].weight;
			head = graph.fstarmatrix[i].head;
		}
		else
		{
			arcweight = graph.rstarmatrix[i].weight;
			head = graph.rstarmatrix[i].tail;	
		}

		int headp = n[head].permanent;
		int headf = n[head].finite;
		int headheapsize = n[head].minheap.size();

		if (n[head].permanent == K)
		{
			continue;
		}

		if (n[head].finite == K)
		{
			if (n[head].minheap[headheapsize-1].weight <= n[root].pathlist[rootp-1].weight + arcweight)
			{
				continue;
			}
		}
		pathlistsize = n[root].pathlist.size();
		if (cyclic(n[root].pathlist[rootp-1],head)==0)
		{
			if (n[head].finite == K)
			{
				n[head].minheap.pop_back();
			}
			n[head].minheap.push_back(PATH());
			headheapsize = n[head].minheap.size();
			n[head].minheap[headheapsize-1] = n[root].pathlist[rootp-1];
			n[head].minheap[headheapsize-1].weight += arcweight;
			n[head].minheap[headheapsize-1].path.push_back(head);
			int path_size = n[head].minheap[headheapsize-1].path.size();
			//int product_size = n[head].minheap[headheapsize-1].product.size();
			
			// if (path_size%10==1)
			// {
			// 	n[head].minheap[headheapsize-1].product.push_back(prime[head]);
			// }
			// else
			// {
			// 	n[head].minheap[headheapsize-1].product[product_size-1] *= prime[head];
			// }
			n[head].minheap[headheapsize-1].product[head%20] *= prime[head];
			for (int j = headheapsize-1; j > 0 ; --j)
			{
				if (n[head].minheap[j].weight < n[head].minheap[j-1].weight)
				{
					swap(n[head].minheap[j],n[head].minheap[j-1]);
				}
				else
				{
					break;
				}
			}
			if (n[head].finite < K)
			{
				n[head].finite += 1;
			}
			
			if (n[head].position==-1)
			{
				heap.push_back(head);
				heapsize = heap.size();
				n[head].position = heapsize-1;
			}

			for (int j = n[head].position; j > 0; j=(j-1)/2)
			{
				int parentkey = n[heap[(j-1)/2]].permanent;
				int parent_pathsfound = n[heap[(j-1)/2]].finite;
				int childkey = n[heap[j]].permanent;
				int child_pathsfound = n[heap[j]].finite;
				double parentweight,childweight;
				if (parentkey<parent_pathsfound)
				{
					parentweight = n[heap[(j-1)/2]].minheap[0].weight;
				}
				else
				{
					parentweight = 32767;
				}
				if (childkey<child_pathsfound)
				{
					childweight = n[heap[j]].minheap[0].weight;
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
	if (n[root].permanent==K)
	{
		return;
	}
	if (n[root].permanent < n[root].finite)
	{
		heap.push_back(root);
		heapsize = heap.size();
		n[root].position = heapsize-1;
		for (int i = heapsize-1; i > 0; i=(i-1)/2)
		{
			int keyp = n[heap[(i-1)/2]].permanent;
			int ppfound = n[heap[(i-1)/2]].finite;
			int keyc = n[heap[i]].permanent;
			int cpfound = n[heap[i]].finite;
			double pweight,cweight;
			if (keyp<ppfound)
			{
				pweight = n[heap[(i-1)/2]].minheap[0].weight;
			}
			else
			{
				pweight = 32767;
			}
			if (keyc<cpfound)
			{
				cweight = n[heap[i]].minheap[0].weight;
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

PATHLIST kspath::ksp_single1(GRAPH &graph, int Origin, int Destination, int K)
{
	PATHLIST P;
	vector<int> heap;
	vector<NODE> n;
	int heapsize;
	for (int i = 0; i < graph.nodes; ++i)
	{
		n.push_back(NODE());
		n[i].permanent = 0;
		n[i].finite = 0;
		n[i].position = -1;
	}
	n[Origin].minheap.push_back(PATH());
	heap.push_back(Origin);
	n[Origin].position = 0;
	n[Origin].finite = 1;
	n[Origin].minheap[0].weight = 0;
	n[Origin].minheap[0].path.push_back(Origin);
	for (int i = 0; i < 20; ++i)
	{
		n[Origin].minheap[0].product.push_back(1);
	}
	n[Origin].minheap[0].product[Origin%20] = prime[Origin];
	heapsize = heap.size();
	int forwardpasses = 0;
	while((n[Destination].permanent<K)&&(heapsize>0))
	{
		arc_processing_classic1(graph, heap, n, K, 1);
		heapsize = heap.size();
	}
	for (int i = 0; i < n[Destination].permanent; ++i)
	{
		P.pathlist.push_back(PATH());
		P.pathlist[i] = {};
		P.pathlist[i].weight = n[Destination].pathlist[i].weight;
		P.pathlist[i].path = n[Destination].pathlist[i].path;
	}
	return P;
}

void kspath::arc_processing_classic2(GRAPH &graph, vector<int> &heap, vector<NODE> &n, int K, bool forward = 1)
{
	// ofstream t;
	// t.open("minmaxheap.csv",std::ios_base::app);
	// srand(time(NULL));
	// double t1 = clock();
	int heapsize = heap.size();
	int root = heap[0];
	int heappathsize = n[root].minheap.size();
	int pathlistsize = n[root].pathlist.size();

	n[root].permanent+=1;
	int rootp = n[root].permanent;
	int rootf = n[root].finite;
	n[root].pathlist.push_back(PATH());
	n[root].pathlist[rootp-1] = n[root].minheap[0];
	n[root].pathlist[rootp-1].last_scanned = 0;
	int minlastelementpos = n[root].minheap[heappathsize-1].pos;
	int maxlastelementpos = n[root].maxheap[heappathsize-1].pos;	
	int rootpos = n[root].minheap[0].pos;
	n[root].maxheap[minlastelementpos].pos = 0;
	n[root].minheap[maxlastelementpos].pos = rootpos;
	swap(n[root].maxheap[rootpos], n[root].maxheap[heappathsize-1]);
	swap(n[root].minheap[0], n[root].minheap[heappathsize-1]);
	n[root].minheap.pop_back();
	n[root].maxheap.pop_back();


	for (int i = rootpos; i > 0; i=((i-1)/2))
	{
		if (n[root].maxheap[i].weight > n[root].maxheap[(i-1)/2].weight)
		{
			int ppos = n[root].maxheap[(i-1)/2].pos;
			int cpos = n[root].maxheap[i].pos;
			swap(n[root].maxheap[i], n[root].maxheap[(i-1)/2]);
			n[root].minheap[ppos].pos = i;
			n[root].minheap[cpos].pos = (i-1)/2;
		}
		else
		{
			break;
		}
	}

	n[heap[heapsize-1]].position = 0;
	n[root].position = -1;
	swap(heap[0],heap[heapsize-1]);
	heap.pop_back();
	int headheapsize;
	heappathsize = n[root].minheap.size();
	heapsize = heap.size();
	//t<<heappathsize<<',';
	if (heappathsize==2)
	{
		if (n[root].minheap[1].weight < n[root].minheap[0].weight)
		{
			swap(n[root].minheap[0], n[root].minheap[1]);
			n[root].maxheap[0].pos = 1;
			n[root].maxheap[1].pos = 0;
		}
	}

	if (heappathsize>2)
	{
		minheapify(n[root].minheap,n[root].maxheap,heappathsize,0);
	}

	
	if (heapsize==2)
	{
		if (n[heap[0]].minheap[0].weight>n[heap[1]].minheap[0].weight)
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

	int start, end;
	double arcweight;
	int head;
	
	if (forward)
	{
		start = graph.fstarposition[root];
		end = graph.fstarposition[root+1];
	}
	else
	{
		start = graph.rstarposition[root];
		end = graph.rstarposition[root+1];	
	}

	// double t2 = clock();
	for (int i = start; i < end; ++i)
	{
		if (forward)
		{
			arcweight = graph.fstarmatrix[i].weight;
			head = graph.fstarmatrix[i].head;
		}
		else
		{
			arcweight = graph.rstarmatrix[i].weight;
			head = graph.rstarmatrix[i].tail;	
		}

		int headp = n[head].permanent;
		int headf = n[head].finite;
		headheapsize = n[head].minheap.size();

		if (n[head].permanent == K)
		{
			continue;
		}

		if (n[head].finite == K)
		{
			if (n[head].maxheap[0].weight <= n[root].pathlist[rootp-1].weight + arcweight)
			{
				continue;
			}
		}

		if (cyclic_classic(n[root].pathlist[rootp-1],head)==0)
		{
			heappathsize = n[head].minheap.size();
			if (n[head].finite == K)
			{
				maxlastelementpos = n[head].maxheap[heappathsize-1].pos;
				minlastelementpos = n[head].minheap[heappathsize-1].pos;
				rootpos = n[head].maxheap[0].pos;
				n[head].minheap[maxlastelementpos].pos = 0;
				n[head].maxheap[minlastelementpos].pos = rootpos;
				swap(n[head].minheap[rootpos], n[head].minheap[heappathsize-1]);
				swap(n[head].maxheap[0], n[head].maxheap[heappathsize-1]);
				n[head].maxheap.pop_back();
				n[head].minheap.pop_back();
				for (int i = rootpos; i > 0; i=((i-1)/2))
				{
					if (n[head].minheap[i].weight < n[head].minheap[(i-1)/2].weight)
					{
						int ppos = n[head].minheap[(i-1)/2].pos;
						int cpos = n[head].minheap[i].pos;
						swap(n[head].minheap[i], n[head].minheap[(i-1)/2]);
						n[head].maxheap[ppos].pos = i;
						n[head].maxheap[cpos].pos = (i-1)/2;
					}
					else
					{
						break;
					}
				}
				heappathsize = n[head].maxheap.size();
				if (heappathsize==2)
				{
					if (n[head].maxheap[1].weight > n[head].maxheap[0].weight)
					{
						swap(n[head].maxheap[0], n[head].maxheap[1]);
						n[head].minheap[0].pos = 1;
						n[head].minheap[1].pos = 0;
					}
				}
				if (heappathsize>2)
				{
					maxheapify(n[head].maxheap,n[head].minheap,heappathsize,0);
				}
			}
			n[head].minheap.push_back(PATH());
			n[head].maxheap.push_back(PATH());
			if (n[head].finite < K)
			{
				n[head].finite += 1;
			}
			headheapsize = n[head].minheap.size();
			n[head].minheap[headheapsize-1] = n[root].pathlist[rootp-1];
			n[head].minheap[headheapsize-1].weight += arcweight;
			n[head].minheap[headheapsize-1].path.push_back(head);
			n[head].minheap[headheapsize-1].pos = headheapsize-1;
			n[head].maxheap[headheapsize-1] = n[root].pathlist[rootp-1];
			n[head].maxheap[headheapsize-1].weight += arcweight;
			n[head].maxheap[headheapsize-1].path.push_back(head);
			n[head].maxheap[headheapsize-1].pos = headheapsize-1;

			for (int j = headheapsize-1; j > 0; j=(j-1)/2)
			{
				int ppos = n[head].minheap[(j-1)/2].pos;
				int cpos = n[head].minheap[j].pos;
				if (n[head].minheap[j].weight < n[head].minheap[(j-1)/2].weight)
				{
					swap(n[head].minheap[j], n[head].minheap[(j-1)/2]);
					n[head].maxheap[ppos].pos = j;
					n[head].maxheap[cpos].pos = (j-1)/2;
				}
				else
				{
					break;
				}
			}

			for (int j = headheapsize-1; j > 0; j=(j-1)/2)
			{
				int ppos = n[head].maxheap[(j-1)/2].pos;
				int cpos = n[head].maxheap[j].pos;
				if (n[head].maxheap[j].weight > n[head].maxheap[(j-1)/2].weight)
				{
					swap(n[head].maxheap[j], n[head].maxheap[(j-1)/2]);
					n[head].minheap[ppos].pos = j;
					n[head].minheap[cpos].pos = (j-1)/2;
				}
				else
				{
					break;
				}
			}
			
			if (n[head].position==-1)
			{
				heap.push_back(head);
				heapsize = heap.size();
				n[head].position = heapsize-1;
			}

			for (int j = n[head].position; j > 0; j=(j-1)/2)
			{
				int parentkey = n[heap[(j-1)/2]].permanent;
				int parent_pathsfound = n[heap[(j-1)/2]].finite;
				int childkey = n[heap[j]].permanent;
				int child_pathsfound = n[heap[j]].finite;
				double parentweight,childweight;
				if (parentkey<parent_pathsfound)
				{
					parentweight = n[heap[(j-1)/2]].minheap[0].weight;
				}
				else
				{
					parentweight = 32767;
				}
				if (childkey<child_pathsfound)
				{
					childweight = n[heap[j]].minheap[0].weight;
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
	// double t3 = clock();
	if (n[root].permanent < n[root].finite)
	{
		heap.push_back(root);
		heapsize = heap.size();
		n[root].position = heapsize-1;
		for (int i = heapsize-1; i > 0; i=(i-1)/2)
		{
			int keyp = n[heap[(i-1)/2]].permanent;
			int ppfound = n[heap[(i-1)/2]].finite;
			int keyc = n[heap[i]].permanent;
			int cpfound = n[heap[i]].finite;
			double pweight,cweight;
			if (keyp<ppfound)
			{
				pweight = n[heap[(i-1)/2]].minheap[0].weight;
			}
			else
			{
				pweight = 32767;
			}
			if (keyc<cpfound)
			{
				cweight = n[heap[i]].minheap[0].weight;
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
	// double t4 = clock();
	//t<<headheapsize<<','<<(t2-t1)/CLOCKS_PER_SEC<<','<<(t3-t2)/CLOCKS_PER_SEC<<','<<(t4-t3)/CLOCKS_PER_SEC<<','<<endl;
}

PATHLIST kspath::ksp_single2(GRAPH &graph, int Origin, int Destination, int K)
{
	PATHLIST P;
	vector<int> heap;
	vector<NODE> n;
	int heapsize;
	for (int i = 0; i < graph.nodes; ++i)
	{
		n.push_back(NODE());
		n[i].permanent = 0;
		n[i].finite = 0;
		n[i].position = -1;
	}
	n[Origin].minheap.push_back(PATH());
	n[Origin].maxheap.push_back(PATH());
	heap.push_back(Origin);
	n[Origin].position = 0;
	n[Origin].finite = 1;
	n[Origin].minheap[0].weight = 0;
	n[Origin].minheap[0].path.push_back(Origin);
	n[Origin].minheap[0].pos = 0;
	n[Origin].maxheap[0].weight = 0;
	n[Origin].maxheap[0].path.push_back(Origin);
	n[Origin].maxheap[0].pos = 0;
	heapsize = heap.size();
	int forwardpasses = 0;
	while((n[Destination].permanent<K)&&(heapsize>0))
	{
		arc_processing_classic2(graph, heap, n, K, 1);
		heapsize = heap.size();
	}
	for (int i = 0; i < n[Destination].permanent; ++i)
	{
		P.pathlist.push_back(PATH());
		P.pathlist[i].weight = n[Destination].pathlist[i].weight;
		P.pathlist[i].path = n[Destination].pathlist[i].path;
	}
	return P;
}

void kspath::arc_processing(GRAPH &graph, vector<int> &heap, vector<NODE> &n, int K, bool forward = 1)
{
	int heapsize = heap.size();
	int root = heap[0];
	int heappathsize = n[root].minheap.size();
	int pathlistsize = n[root].pathlist.size();

	n[root].permanent+=1;
	int rootp = n[root].permanent;
	int rootf = n[root].finite;
	n[root].pathlist.push_back(PATH());
	n[root].pathlist[rootp-1] = n[root].minheap[0];
	int minlastelementpos = n[root].minheap[heappathsize-1].pos;
	int maxlastelementpos = n[root].maxheap[heappathsize-1].pos;	
	int rootpos = n[root].minheap[0].pos;
	n[root].maxheap[minlastelementpos].pos = 0;
	n[root].minheap[maxlastelementpos].pos = rootpos;
	swap(n[root].maxheap[rootpos], n[root].maxheap[heappathsize-1]);
	swap(n[root].minheap[0], n[root].minheap[heappathsize-1]);
	n[root].minheap.pop_back();
	n[root].maxheap.pop_back();


	for (int i = rootpos; i > 0; i=((i-1)/2))
	{
		if (n[root].maxheap[i].weight > n[root].maxheap[(i-1)/2].weight)
		{
			int ppos = n[root].maxheap[(i-1)/2].pos;
			int cpos = n[root].maxheap[i].pos;
			swap(n[root].maxheap[i], n[root].maxheap[(i-1)/2]);
			n[root].minheap[ppos].pos = i;
			n[root].minheap[cpos].pos = (i-1)/2;
		}
		else
		{
			break;
		}
	}

	n[heap[heapsize-1]].position = 0;
	n[root].position = -1;
	swap(heap[0],heap[heapsize-1]);
	heap.pop_back();

	heappathsize = n[root].minheap.size();
	heapsize = heap.size();

	if (heappathsize==2)
	{
		if (n[root].minheap[1].weight < n[root].minheap[0].weight)
		{
			swap(n[root].minheap[0], n[root].minheap[1]);
			n[root].maxheap[0].pos = 1;
			n[root].maxheap[1].pos = 0;
		}
	}

	if (heappathsize>2)
	{
		minheapify(n[root].minheap,n[root].maxheap,heappathsize,0);
	}

	
	if (heapsize==2)
	{
		if (n[heap[0]].minheap[0].weight>n[heap[1]].minheap[0].weight)
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

	int start, end;
	double arcweight;
	int head;
	
	if (forward)
	{
		start = graph.fstarposition[root];
		end = graph.fstarposition[root+1];
	}
	else
	{
		start = graph.rstarposition[root];
		end = graph.rstarposition[root+1];	
	}

	
	for (int i = start; i < end; ++i)
	{
		if (forward)
		{
			arcweight = graph.fstarmatrix[i].weight;
			head = graph.fstarmatrix[i].head;
		}
		else
		{
			arcweight = graph.rstarmatrix[i].weight;
			head = graph.rstarmatrix[i].tail;	
		}

		int headp = n[head].permanent;
		int headf = n[head].finite;
		int headheapsize = n[head].minheap.size();

		if (n[head].permanent == K)
		{
			continue;
		}

		if (n[head].finite == K)
		{
			if (n[head].maxheap[0].weight <= n[root].pathlist[rootp-1].weight + arcweight)
			{
				continue;
			}
		}

		if (cyclic(n[root].pathlist[rootp-1],head)==0)
		{
			heappathsize = n[head].minheap.size();
			if (n[head].finite == K)
			{
				maxlastelementpos = n[head].maxheap[heappathsize-1].pos;
				minlastelementpos = n[head].minheap[heappathsize-1].pos;
				rootpos = n[head].maxheap[0].pos;
				n[head].minheap[maxlastelementpos].pos = 0;
				n[head].maxheap[minlastelementpos].pos = rootpos;
				swap(n[head].minheap[rootpos], n[head].minheap[heappathsize-1]);
				swap(n[head].maxheap[0], n[head].maxheap[heappathsize-1]);
				n[head].maxheap.pop_back();
				n[head].minheap.pop_back();
				for (int i = rootpos; i > 0; i=((i-1)/2))
				{
					if (n[head].minheap[i].weight < n[head].minheap[(i-1)/2].weight)
					{
						int ppos = n[head].minheap[(i-1)/2].pos;
						int cpos = n[head].minheap[i].pos;
						swap(n[head].minheap[i], n[head].minheap[(i-1)/2]);
						n[head].maxheap[ppos].pos = i;
						n[head].maxheap[cpos].pos = (i-1)/2;
					}
					else
					{
						break;
					}
				}
				heappathsize = n[head].maxheap.size();
				if (heappathsize==2)
				{
					if (n[head].maxheap[1].weight > n[head].maxheap[0].weight)
					{
						swap(n[head].maxheap[0], n[head].maxheap[1]);
						n[head].minheap[0].pos = 1;
						n[head].minheap[1].pos = 0;
					}
				}
				if (heappathsize>2)
				{
					maxheapify(n[head].maxheap,n[head].minheap,heappathsize,0);
				}
			}
			n[head].minheap.push_back(PATH());
			n[head].maxheap.push_back(PATH());
			if (n[head].finite < K)
			{
				n[head].finite += 1;
			}
			headheapsize = n[head].minheap.size();
			n[head].minheap[headheapsize-1] = n[root].pathlist[rootp-1];
			n[head].minheap[headheapsize-1].weight += arcweight;
			n[head].minheap[headheapsize-1].path.push_back(head);
			n[head].minheap[headheapsize-1].pos = headheapsize-1;
			n[head].maxheap[headheapsize-1] = n[root].pathlist[rootp-1];
			n[head].maxheap[headheapsize-1].weight += arcweight;
			n[head].maxheap[headheapsize-1].path.push_back(head);
			n[head].maxheap[headheapsize-1].pos = headheapsize-1;
			
			int path_size = n[head].minheap[headheapsize-1].path.size();
			// int product_size = n[head].minheap[headheapsize-1].product.size();
			// if (path_size%10==1)
			// {
			// 	n[head].minheap[headheapsize-1].product.push_back(prime[head]);
			// 	n[head].maxheap[headheapsize-1].product.push_back(prime[head]);
			// }
			// else
			// {
			// 	n[head].minheap[headheapsize-1].product[product_size-1] *= prime[head];
			// 	n[head].maxheap[headheapsize-1].product[product_size-1] *= prime[head];	
			// }
			n[head].minheap[headheapsize-1].product[head%20] *= prime[head];
			n[head].maxheap[headheapsize-1].product[head%20] *= prime[head];

			for (int j = headheapsize-1; j > 0; j=(j-1)/2)
			{
				int ppos = n[head].minheap[(j-1)/2].pos;
				int cpos = n[head].minheap[j].pos;
				if (n[head].minheap[j].weight < n[head].minheap[(j-1)/2].weight)
				{
					swap(n[head].minheap[j], n[head].minheap[(j-1)/2]);
					n[head].maxheap[ppos].pos = j;
					n[head].maxheap[cpos].pos = (j-1)/2;
				}
				else
				{
					break;
				}
			}

			for (int j = headheapsize-1; j > 0; j=(j-1)/2)
			{
				int ppos = n[head].maxheap[(j-1)/2].pos;
				int cpos = n[head].maxheap[j].pos;
				if (n[head].maxheap[j].weight > n[head].maxheap[(j-1)/2].weight)
				{
					swap(n[head].maxheap[j], n[head].maxheap[(j-1)/2]);
					n[head].minheap[ppos].pos = j;
					n[head].minheap[cpos].pos = (j-1)/2;
				}
				else
				{
					break;
				}
			}
			
			if (n[head].position==-1)
			{
				heap.push_back(head);
				heapsize = heap.size();
				n[head].position = heapsize-1;
			}

			for (int j = n[head].position; j > 0; j=(j-1)/2)
			{
				int parentkey = n[heap[(j-1)/2]].permanent;
				int parent_pathsfound = n[heap[(j-1)/2]].finite;
				int childkey = n[heap[j]].permanent;
				int child_pathsfound = n[heap[j]].finite;
				double parentweight,childweight;
				if (parentkey<parent_pathsfound)
				{
					parentweight = n[heap[(j-1)/2]].minheap[0].weight;
				}
				else
				{
					parentweight = 32767;
				}
				if (childkey<child_pathsfound)
				{
					childweight = n[heap[j]].minheap[0].weight;
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
	if (n[root].permanent < n[root].finite)
	{
		heap.push_back(root);
		heapsize = heap.size();
		n[root].position = heapsize-1;
		for (int i = heapsize-1; i > 0; i=(i-1)/2)
		{
			int keyp = n[heap[(i-1)/2]].permanent;
			int ppfound = n[heap[(i-1)/2]].finite;
			int keyc = n[heap[i]].permanent;
			int cpfound = n[heap[i]].finite;
			double pweight,cweight;
			if (keyp<ppfound)
			{
				pweight = n[heap[(i-1)/2]].minheap[0].weight;
			}
			else
			{
				pweight = 32767;
			}
			if (keyc<cpfound)
			{
				cweight = n[heap[i]].minheap[0].weight;
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

PATHLIST kspath::ksp_single(GRAPH &graph, int Origin, int Destination, int K)
{
	PATHLIST P;
	vector<int> heap;
	vector<NODE> n;
	int heapsize;
	for (int i = 0; i < graph.nodes; ++i)
	{
		n.push_back(NODE());
		n[i].permanent = 0;
		n[i].finite = 0;
		n[i].position = -1;
	}
	n[Origin].minheap.push_back(PATH());
	n[Origin].maxheap.push_back(PATH());
	heap.push_back(Origin);
	n[Origin].position = 0;
	n[Origin].finite = 1;
	n[Origin].minheap[0].weight = 0;
	n[Origin].minheap[0].path.push_back(Origin);
	for (int i = 0; i < 20; ++i)
	{
		n[Origin].minheap[0].product.push_back(1);
		n[Origin].maxheap[0].product.push_back(1);
	}
	n[Origin].minheap[0].product[Origin%20] = prime[Origin];
	n[Origin].maxheap[0].product[Origin%20] = prime[Origin];
	n[Origin].minheap[0].pos = 0;
	n[Origin].maxheap[0].weight = 0;
	n[Origin].maxheap[0].path.push_back(Origin);
	n[Origin].maxheap[0].product.push_back(prime[Origin]);
	n[Origin].maxheap[0].pos = 0;
	heapsize = heap.size();
	int forwardpasses = 0;
	while((n[Destination].permanent<K)&&(heapsize>0))
	{
		heapsize = heap.size();
		int path_size = n[heap[0]].minheap[0].path.size();
		int root = heap[0];
		int minheapsize = n[heap[0]].minheap.size();
		int pathlistsize = n[heap[0]].pathlist.size();
		arc_processing(graph, heap, n, K, 1);
		heapsize = heap.size();
		minheapsize = n[root].minheap.size();
		pathlistsize = n[root].pathlist.size();
	}
	for (int i = 0; i < n[Destination].permanent; ++i)
	{
		P.pathlist.push_back(PATH());
		P.pathlist[i].weight = n[Destination].pathlist[i].weight;
		P.pathlist[i].path = n[Destination].pathlist[i].path;
	}
	return P;
}

PATHLIST kspath::ksp_bidirectional(GRAPH &graph, int Origin, int Destination, int K)
{
	PATHLIST P;
	vector<int> h1;
	vector<int> h2;
	vector<NODE> n1;
	vector<NODE> n2;
	int h1size;
	int h2size;
	for (int i = 0; i < graph.nodes; ++i)
	{
		n1.push_back(NODE());
		n1[i].permanent = 0;
		n1[i].finite = 0;
		n1[i].position = -1;
		n2.push_back(NODE());
		n2[i].permanent = 0;
		n2[i].finite = 0;
		n2[i].position = -1;
	}
	n1[Origin].minheap.push_back(PATH());
	n1[Origin].maxheap.push_back(PATH());
	h1.push_back(Origin);
	n1[Origin].position = 0;
	n1[Origin].finite = 1;
	n1[Origin].minheap[0].weight = 0;
	n1[Origin].minheap[0].path.push_back(Origin);
	n1[Origin].minheap[0].pos = 0;
	n1[Origin].maxheap[0].weight = 0;
	n1[Origin].maxheap[0].path.push_back(Origin);
	n1[Origin].maxheap[0].pos = 0;
	h1size = h1.size();

	n2[Destination].minheap.push_back(PATH());
	n2[Destination].maxheap.push_back(PATH());
	h2.push_back(Destination);
	n2[Destination].position = 0;
	n2[Destination].finite = 1;
	n2[Destination].minheap[0].weight = 0;
	n2[Destination].minheap[0].path.push_back(Destination);
	n2[Destination].minheap[0].pos = 0;
	n2[Destination].maxheap[0].weight = 0;
	n2[Destination].maxheap[0].path.push_back(Destination);
	n2[Destination].maxheap[0].pos = 0;
	h2size = h2.size();
	
	int psize = P.pathlist.size();
	double bound1, bound2;
	PATHLIST P1;
	while((psize<K)&&(h1size>0)&&(h2size>0))
	{
		if (n1[Destination].permanent>=K)
		{
			for (int i = 0; i < n1[Destination].permanent; ++i)
			{
				P1.pathlist.push_back(PATH());
				P1.pathlist[i].weight = n1[Destination].pathlist[i].weight;
				P1.pathlist[i].path = n1[Destination].pathlist[i].path;
			}
			return P1;
		}
		for (int i = 0; i < 20; ++i)
		{
			bound1 = n1[h1[0]].minheap[0].weight;
			arc_processing_classic2(graph, h1, n1, K, 1);
			h1size = h1.size();
			bound2 = n2[h2[0]].minheap[0].weight;
			arc_processing_classic2(graph, h2, n2, K, 0);
			h2size = h2.size();
		}
		double bound_weight = bound1 + bound2;
		for (int i = 0; i < graph.nodes; ++i)
		{
			for (int j = 0; j < n1[i].permanent; ++j)
			{
				if (n1[i].pathlist[j].weight>bound_weight)
				{
					continue;
				}
				for (int k = n1[i].pathlist[j].last_scanned; k < n2[i].permanent; ++k)
				{
					if (n1[i].pathlist[j].weight+n2[i].pathlist[k].weight<=bound_weight)
					{
						n1[i].pathlist[j].last_scanned = k+1;
						if (cyclic(n1[i].pathlist[j],n2[i].pathlist[k]))
						{
							continue;
						}
						PATH newpath = kspath::mergepath(n1[i].pathlist[j],n2[i].pathlist[k]);
						bool continuevar = 0;
						psize = P.pathlist.size();
						for (int l = psize-1; l >= 0; --l)
						{
							if (same_path(P.pathlist[l],newpath))
							{
								continuevar = 1;
								break;
							}
						}
						if (continuevar)
						{
							continue;
						}
						P.pathlist.push_back(PATH());
						P.pathlist[psize] = newpath;
					}
					else
					{
						break;
					}
				}
				int minheapsize = n2[i].minheap.size();
				for (int k = 0; k < minheapsize; ++k)
				{
					if (n1[i].pathlist[j].weight+n2[i].minheap[k].weight<=bound_weight)
					{
						if (cyclic(n1[i].pathlist[j],n2[i].minheap[k]))
						{
							continue;
						}
						PATH newpath = kspath::mergepath(n1[i].pathlist[j],n2[i].minheap[k]);
						bool continuevar = 0;
						psize = P.pathlist.size();
						for (int l = psize-1; l >= 0; --l)
						{
							if (same_path(P.pathlist[l],newpath))
							{
								continuevar = 1;
								break;
							}
						}
						if (continuevar)
						{
							continue;
						}
						P.pathlist.push_back(PATH());
						P.pathlist[psize] = newpath;
					}	
				}
			}
		}
		psize = P.pathlist.size();
	}
	psize = P.pathlist.size();
	cout<<"bidirection path size: "<<psize<<endl;
	return P;	
}
