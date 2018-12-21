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

bool kspath::cyclic(vector<NODE> &n, int root, int index, int b)
{
	double t1 = clock();
	int rootpathpos = n[root].pathlist[index].pathpos;
	int i, predindex;
	if ((root%10)==(b%10))
	{
		i = root;
		predindex = index;
	}
	else
	{
		i = n[root].pathmatrix[rootpathpos].pred[b%10];
		predindex = n[root].pathmatrix[rootpathpos].index[b%10];
	}
	while(i!=-1)
	{
		int pos = n[i].pathlist[predindex].pathpos;
		if (n[i].pathmatrix[pos].product%prime[b]==0)
		{
			double t2 = clock();
			return 1;
		}
		else
		{
			int prev_i = i;
			int prev_index = predindex;
			i = n[prev_i].pathmatrix[pos].pred[b%10];
			predindex = n[prev_i].pathmatrix[pos].index[b%10];
		}
	}
	double t2 = clock();
	return 0;
}

bool kspath::cyclic_classic(vector<NODE> &n, int root, int index, int b)
{
	int i = root;
	int predindex = index;
	while(i != -1)
	{
		if (i==b)
		{
			return 1;
		}
		else
		{
			int prev_i = i;
			int prev_index = predindex;
			i = n[prev_i].pathlist[prev_index].pred_node;
			predindex = n[prev_i].pathlist[prev_index].pred_index;
		}
	}
	return 0;
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

void kspath::minheapify(vector<label> &minheap, vector<label> &maxheap, int n, int i)
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

void kspath::maxheapify(vector<label> &maxheap, vector<label> &minheap, int n, int i)
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

void kspath::arcprocessing(GRAPH &graph, vector<int> &heap, vector<NODE> &n, int K, bool forward = 1)
{
	int root = heap[0];
	int heappathsize = n[root].minheap.size();
	int pathlistsize = n[root].pathlist.size();
	int heapsize = heap.size();

	n[root].permanent += 1;
	int rootp = n[root].permanent;
	int rootf = n[root].finite;
	n[root].pathlist.push_back(label());

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
		//int rootpathpos = n[root].pathlist[rootp-1].pathpos;
		if (cyclic_classic(n,root,rootp-1,head)==0)
		{	
			if (n[head].finite == K)
			{
				n[head].minheap.pop_back();
			}

			n[head].minheap.push_back(label());
			//n[head].pathmatrix.push_back(PATH());
			//int headpathmatrixsize = n[head].pathmatrix.size();
			minheapsize = n[head].minheap.size();
			n[head].minheap[minheapsize-1] = n[root].pathlist[pathlistsize];
			n[head].minheap[minheapsize-1].weight += arcweight;
			n[head].minheap[minheapsize-1].pred_node = root;
			n[head].minheap[minheapsize-1].pred_index = rootp-1;
			//n[head].minheap[minheapsize-1].pathpos = headpathmatrixsize - 1;
			//n[head].pathmatrix[headpathmatrixsize-1] = n[root].pathmatrix[rootpathpos];
			//n[head].pathmatrix[headpathmatrixsize-1].path.push_back(head);
			
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

PATHLIST kspath::S(GRAPH &graph, int Origin, int Destination, int K)
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

	n[Origin].pathmatrix.push_back(PATH());
	n[Origin].minheap.push_back(label());
	n[Origin].minheap[0].pathpos = 0;
	n[Origin].minheap[0].weight = 0;
	//n[Origin].pathmatrix[0].path.push_back(Origin);
	n[Origin].minheap[0].pred_node = -1;
	n[Origin].minheap[0].pred_index = -1;
	heap.push_back(Origin);
	n[Origin].position = 0;
	n[Origin].finite = 1;
	heapsize = heap.size();
	int forwardpasses = 0;
	
	while((n[Destination].permanent<K)&&(heapsize>0))
	{
		arcprocessing(graph, heap, n, K, 1);
		heapsize = heap.size();
	}
	for (int i = 0; i < n[Destination].permanent; ++i)
	{
		P.pathlist.push_back(outpath());
		P.pathlist[i].weight = n[Destination].pathlist[i].weight;
		int j = n[Destination].pathlist[i].pred_node;
		int j_index = n[Destination].pathlist[i].pred_index;
		P.pathlist[i].path.push_back(Destination);
		while(j!=-1)
		{
			int prev_j = j;
			int prev_j_index = j_index;
			P.pathlist[i].path.push_back(j);
			j = n[prev_j].pathlist[prev_j_index].pred_node;
			j_index = n[prev_j].pathlist[prev_j_index].pred_index;
		}
	}
	return P;
}

void kspath::arcprocessing1(GRAPH &graph, vector<int> &heap, vector<NODE> &n, int K, bool forward = 1)
{
	int heapsize = heap.size();
	int root = heap[0];
	int heappathsize = n[root].minheap.size();
	int pathlistsize = n[root].pathlist.size();

	n[root].permanent+=1;
	int rootp = n[root].permanent;
	int rootf = n[root].finite;
	n[root].pathlist.push_back(label());
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
		int rootpathpos = n[root].pathlist[rootp-1].pathpos;
		if (cyclic(n,root,rootp-1,head)==0)
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
			n[head].minheap.push_back(label());
			n[head].maxheap.push_back(label());
			n[head].pathmatrix.push_back(PATH());
			if (n[head].finite < K)
			{
				n[head].finite += 1;
			}
			int headpathmatrixsize = n[head].pathmatrix.size();

			headheapsize = n[head].minheap.size();
			n[head].minheap[headheapsize-1] = n[root].pathlist[rootp-1];
			n[head].minheap[headheapsize-1].weight += arcweight;
			n[head].minheap[headheapsize-1].pathpos = headpathmatrixsize-1;
			n[head].minheap[headheapsize-1].pos = headheapsize-1;
			n[head].minheap[headheapsize-1].pred_node = root;
			n[head].minheap[headheapsize-1].pred_index = rootp-1;
			n[head].maxheap[headheapsize-1] = n[root].pathlist[rootp-1];
			n[head].maxheap[headheapsize-1].weight += arcweight;
			n[head].maxheap[headheapsize-1].pathpos = headpathmatrixsize-1;
			n[head].maxheap[headheapsize-1].pos = headheapsize-1;
			n[head].maxheap[headheapsize-1].pred_node = root;
			n[head].maxheap[headheapsize-1].pred_index = rootp-1;

			n[head].pathmatrix[headpathmatrixsize-1] = n[root].pathmatrix[rootpathpos];
			if ((head%10)==(root%10))
			{
				double logp = n[head].pathmatrix[headpathmatrixsize-1].log_product + (log(prime[head])/log(2));
				if (logp>127)
				{
					n[head].pathmatrix[headpathmatrixsize-1].product = prime[head];
					n[head].pathmatrix[headpathmatrixsize-1].log_product = log(prime[head])/log(2);
					n[head].pathmatrix[headpathmatrixsize-1].pred[head%10] = root;
					n[head].pathmatrix[headpathmatrixsize-1].index[head%10] = rootp-1;
				}
				else
				{
					n[head].pathmatrix[headpathmatrixsize-1].product *= prime[head];
					n[head].pathmatrix[headpathmatrixsize-1].log_product += log(prime[head])/log(2);
					n[head].pathmatrix[headpathmatrixsize-1].pred[head%10] = n[root].pathmatrix[rootpathpos].pred[root%10];
					n[head].pathmatrix[headpathmatrixsize-1].index[head%10] = n[root].pathmatrix[rootpathpos].index[root%10];
				}
			}
			else
			{
				n[head].pathmatrix[headpathmatrixsize-1].pred[root%10] = root;
				n[head].pathmatrix[headpathmatrixsize-1].index[root%10] = rootp-1;
				int pred = n[head].pathmatrix[headpathmatrixsize-1].pred[head%10];
				int index = n[head].pathmatrix[headpathmatrixsize-1].index[head%10];
				if (pred==-1)
				{
					n[head].pathmatrix[headpathmatrixsize-1].product = prime[head];
					n[head].pathmatrix[headpathmatrixsize-1].log_product = log(prime[head])/log(2);
					n[head].pathmatrix[headpathmatrixsize-1].pred[head%10] = pred;
					n[head].pathmatrix[headpathmatrixsize-1].index[head%10] = index;
				}
				else
				{
					int predpos = n[pred].pathlist[index].pathpos;
					double logp = n[pred].pathmatrix[predpos].log_product + (log(prime[head])/log(2));
					if (logp>127)
					{
						n[head].pathmatrix[headpathmatrixsize-1].product = prime[head];
						n[head].pathmatrix[headpathmatrixsize-1].log_product = log(prime[head])/log(2);
						n[head].pathmatrix[headpathmatrixsize-1].pred[head%10] = pred;
						n[head].pathmatrix[headpathmatrixsize-1].index[head%10] = index;
					}
					else
					{
						n[head].pathmatrix[headpathmatrixsize-1].product = n[pred].pathmatrix[predpos].product*prime[head];
						n[head].pathmatrix[headpathmatrixsize-1].log_product = logp;
						n[head].pathmatrix[headpathmatrixsize-1].pred[head%10] = n[pred].pathmatrix[predpos].pred[head%10];
						n[head].pathmatrix[headpathmatrixsize-1].index[head%10] = n[pred].pathmatrix[predpos].index[head%10];
					}
				}
			}
			
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

PATHLIST kspath::S1(GRAPH &graph, int Origin, int Destination, int K)
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
	n[Origin].pathmatrix.push_back(PATH());
	n[Origin].minheap.push_back(label());
	n[Origin].maxheap.push_back(label());
	heap.push_back(Origin);
	n[Origin].position = 0;
	n[Origin].finite = 1;
	n[Origin].minheap[0].weight = 0;
	n[Origin].minheap[0].pathpos = 0;
	n[Origin].maxheap[0].weight = 0;
	n[Origin].maxheap[0].pathpos = 0;
	n[Origin].minheap[0].pos = 0;
	n[Origin].maxheap[0].pos = 0;
	n[Origin].minheap[0].pred_node = -1;
	n[Origin].maxheap[0].pred_node = -1;
	n[Origin].minheap[0].pred_index = -1;
	n[Origin].maxheap[0].pred_index = -1;
	n[Origin].pathmatrix[0].product = prime[Origin];
	n[Origin].pathmatrix[0].log_product = log(prime[Origin])/log(2);
	for (int i = 0; i < 10; ++i)
	{
		n[Origin].pathmatrix[0].pred.push_back(-1);
		n[Origin].pathmatrix[0].index.push_back(-1);
	}
	heapsize = heap.size();
	while((n[Destination].permanent<K)&&(heapsize>0))
	{
		arcprocessing1(graph, heap, n, K, 1);
		heapsize = heap.size();
	}
	for (int i = 0; i < n[Destination].permanent; ++i)
	{
		P.pathlist.push_back(outpath());
		P.pathlist[i].weight = n[Destination].pathlist[i].weight;
		int j = n[Destination].pathlist[i].pred_node;
		int j_index = n[Destination].pathlist[i].pred_index;
		P.pathlist[i].path.push_back(Destination);
		while(j!=-1)
		{
			int prev_j = j;
			int prev_j_index = j_index;
			P.pathlist[i].path.push_back(j);
			j = n[prev_j].pathlist[prev_j_index].pred_node;
			j_index = n[prev_j].pathlist[prev_j_index].pred_index;
		}
	}
	return P;
}

void kspath::arcprocessing2(GRAPH &graph, vector<int> &heap, vector<NODE> &n, int K, bool forward = 1)
{
	int heapsize = heap.size();
	int root = heap[0];
	int heappathsize = n[root].minheap.size();
	int pathlistsize = n[root].pathlist.size();

	n[root].permanent+=1;
	int rootp = n[root].permanent;
	int rootf = n[root].finite;
	
	n[root].pathlist.push_back(label());
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
	int headheapsize;
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
		//int rootpathpos = n[root].pathlist[rootp-1].pathpos;
		if (cyclic_classic(n,root,rootp-1,head)==0)
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
			n[head].minheap.push_back(label());
			n[head].maxheap.push_back(label());
			//n[head].pathmatrix.push_back(PATH());
			if (n[head].finite < K)
			{
				n[head].finite += 1;
			}
			int headpathmatrixsize = n[head].pathmatrix.size();

			headheapsize = n[head].minheap.size();
			n[head].minheap[headheapsize-1] = n[root].pathlist[rootp-1];
			n[head].minheap[headheapsize-1].weight += arcweight;
			//n[head].minheap[headheapsize-1].path.push_back(head);
			n[head].minheap[headheapsize-1].pathpos = headpathmatrixsize-1;
			n[head].minheap[headheapsize-1].pos = headheapsize-1;
			n[head].minheap[headheapsize-1].pred_node = root;
			n[head].minheap[headheapsize-1].pred_index = rootp-1;
			n[head].maxheap[headheapsize-1] = n[root].pathlist[rootp-1];
			n[head].maxheap[headheapsize-1].weight += arcweight;
			//n[head].maxheap[headheapsize-1].path.push_back(head);
			n[head].maxheap[headheapsize-1].pathpos = headpathmatrixsize-1;
			n[head].maxheap[headheapsize-1].pos = headheapsize-1;
			n[head].maxheap[headheapsize-1].pred_node = root;
			n[head].maxheap[headheapsize-1].pred_index = rootp-1;

			//n[head].pathmatrix[headpathmatrixsize-1] = n[root].pathmatrix[rootpathpos];
			//n[head].pathmatrix[headpathmatrixsize-1].path.push_back(head);

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

PATHLIST kspath::S2(GRAPH &graph, int Origin, int Destination, int K)
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

	//n[Origin].pathmatrix.push_back(PATH());
	n[Origin].minheap.push_back(label());
	n[Origin].maxheap.push_back(label());
	heap.push_back(Origin);
	n[Origin].position = 0;
	n[Origin].finite = 1;
	n[Origin].minheap[0].weight = 0;
	n[Origin].minheap[0].pathpos = 0;
	n[Origin].maxheap[0].weight = 0;
	n[Origin].maxheap[0].pathpos = 0;
	//n[Origin].pathmatrix[0].path.push_back(Origin);
	n[Origin].minheap[0].pos = 0;
	n[Origin].maxheap[0].pos = 0;
	n[Origin].minheap[0].pred_node = -1;
	n[Origin].minheap[0].pred_index = -1;
	n[Origin].maxheap[0].pred_node = -1;
	n[Origin].maxheap[0].pred_index = -1;

	heapsize = heap.size();
	int forwardpasses = 0;
	while((n[Destination].permanent<K)&&(heapsize>0))
	{
		arcprocessing2(graph, heap, n, K, 1);
		heapsize = heap.size();
	}
	for (int i = 0; i < n[Destination].permanent; ++i)
	{
		P.pathlist.push_back(outpath());
		P.pathlist[i].weight = n[Destination].pathlist[i].weight;
		int j = n[Destination].pathlist[i].pred_node;
		int j_index = n[Destination].pathlist[i].pred_index;
		P.pathlist[i].path.push_back(Destination);
		while(j!=-1)
		{
			int prev_j = j;
			int prev_j_index = j_index;
			P.pathlist[i].path.push_back(j);
			j = n[prev_j].pathlist[prev_j_index].pred_node;
			j_index = n[prev_j].pathlist[prev_j_index].pred_index;
		}
	}
	return P;
}

void kspath::arcprocessing3(GRAPH &graph, vector<int> &heap, vector<NODE> &n, int K, bool forward = 1)
{
	int heapsize = heap.size();
	int root = heap[0];
	int heappathsize = n[root].minheap.size();
	int pathlistsize = n[root].pathlist.size();

	n[root].permanent+=1;
	int rootp = n[root].permanent;
	int rootf = n[root].finite;
	n[root].pathlist.push_back(label());
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
		int rootpathpos = n[root].pathlist[rootp-1].pathpos;
		
		if (cyclic(n,root,rootp-1,head)==0)
		{
			if (n[head].finite == K)
			{
				n[head].minheap.pop_back();
			}
			n[head].pathmatrix.push_back(PATH());
			n[head].minheap.push_back(label());

			headheapsize = n[head].minheap.size();
			n[head].minheap[headheapsize-1] = n[root].pathlist[rootp-1];
			n[head].minheap[headheapsize-1].weight += arcweight;
			n[head].minheap[headheapsize-1].pred_node = root;
			n[head].minheap[headheapsize-1].pred_index = rootp-1;
			int headpathmatrixsize = n[head].pathmatrix.size();
			n[head].minheap[headheapsize-1].pathpos = headpathmatrixsize-1;
			
			n[head].pathmatrix[headpathmatrixsize-1] = n[root].pathmatrix[rootpathpos];
			if ((head%10)==(root%10))
			{
				double logp = n[head].pathmatrix[headpathmatrixsize-1].log_product + (log(prime[head])/log(2));
				if (logp>127)
				{
					n[head].pathmatrix[headpathmatrixsize-1].product = prime[head];
					n[head].pathmatrix[headpathmatrixsize-1].log_product = log(prime[head])/log(2);
					n[head].pathmatrix[headpathmatrixsize-1].pred[head%10] = root;
					n[head].pathmatrix[headpathmatrixsize-1].index[head%10] = rootp-1;
					n[head].pathmatrix[headpathmatrixsize-1].prodsize[head%10] += 1;
				}
				else
				{
					n[head].pathmatrix[headpathmatrixsize-1].product *= prime[head];
					n[head].pathmatrix[headpathmatrixsize-1].log_product += log(prime[head])/log(2);
					n[head].pathmatrix[headpathmatrixsize-1].pred[head%10] = n[root].pathmatrix[rootpathpos].pred[root%10];
					n[head].pathmatrix[headpathmatrixsize-1].index[head%10] = n[root].pathmatrix[rootpathpos].index[root%10];
				}
			}
			else
			{
				n[head].pathmatrix[headpathmatrixsize-1].pred[root%10] = root;
				n[head].pathmatrix[headpathmatrixsize-1].index[root%10] = rootp-1;
				int pred = n[head].pathmatrix[headpathmatrixsize-1].pred[head%10];
				int index = n[head].pathmatrix[headpathmatrixsize-1].index[head%10];
				if (pred==-1)
				{
					n[head].pathmatrix[headpathmatrixsize-1].prodsize[head%10] += 1;
					n[head].pathmatrix[headpathmatrixsize-1].product = prime[head];
					n[head].pathmatrix[headpathmatrixsize-1].log_product = log(prime[head])/log(2);
					n[head].pathmatrix[headpathmatrixsize-1].pred[head%10] = pred;
					n[head].pathmatrix[headpathmatrixsize-1].index[head%10] = index;
				}
				else
				{
					int predpos = n[pred].pathlist[index].pathpos;
					double logp = n[pred].pathmatrix[predpos].log_product + (log(prime[head])/log(2));
					if (logp>127)
					{
						n[head].pathmatrix[headpathmatrixsize-1].prodsize[head%10] += 1;
						n[head].pathmatrix[headpathmatrixsize-1].product = prime[head];
						n[head].pathmatrix[headpathmatrixsize-1].log_product = log(prime[head])/log(2);
						n[head].pathmatrix[headpathmatrixsize-1].pred[head%10] = pred;
						n[head].pathmatrix[headpathmatrixsize-1].index[head%10] = index;
					}
					else
					{
						n[head].pathmatrix[headpathmatrixsize-1].product = n[pred].pathmatrix[predpos].product*prime[head];
						n[head].pathmatrix[headpathmatrixsize-1].log_product = logp;
						n[head].pathmatrix[headpathmatrixsize-1].pred[head%10] = n[pred].pathmatrix[predpos].pred[head%10];
						n[head].pathmatrix[headpathmatrixsize-1].index[head%10] = n[pred].pathmatrix[predpos].index[head%10];
					}
				}
			}
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

PATHLIST kspath::S3(GRAPH &graph, int Origin, int Destination, int K)
{
	ofstream out;
	out.open("values.csv",std::ios_base::app);
	//out.open("values.csv");
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
	n[Origin].pathmatrix.push_back(PATH());
	n[Origin].minheap.push_back(label());
	heap.push_back(Origin);
	n[Origin].position = 0;
	n[Origin].finite = 1;
	n[Origin].minheap[0].weight = 0;
	n[Origin].minheap[0].pathpos = 0;
	n[Origin].minheap[0].pred_node = -1;
	n[Origin].minheap[0].pred_index = -1;
	n[Origin].pathmatrix[0].product = prime[Origin];
	n[Origin].pathmatrix[0].log_product = log(prime[Origin])/log(2);
	for (int i = 0; i < 10; ++i)
	{
		n[Origin].pathmatrix[0].pred.push_back(-1);
		n[Origin].pathmatrix[0].index.push_back(-1);
		n[Origin].pathmatrix[0].prodsize.push_back(0);
	}
	heapsize = heap.size();
	int nodeselection_count = 0;
	int arcprocess_count = 0;
	while((n[Destination].permanent<K)&&(heapsize>0))
	{
		arcprocess_count += (graph.fstarposition[heap[0]+1] - graph.fstarposition[heap[0]]);
		arcprocessing3(graph, heap, n, K, 1);
		nodeselection_count += 1;
		heapsize = heap.size();
	}
	int pathsize_max = 0;
	for (int i = 0; i < n[Destination].permanent; ++i)
	{
		P.pathlist.push_back(outpath());
		P.pathlist[i].weight = n[Destination].pathlist[i].weight;
		int j = n[Destination].pathlist[i].pred_node;
		int j_index = n[Destination].pathlist[i].pred_index;
		P.pathlist[i].path.push_back(Destination);
		while(j!=-1)
		{
			int prev_j = j;
			int prev_j_index = j_index;
			P.pathlist[i].path.push_back(j);
			j = n[prev_j].pathlist[prev_j_index].pred_node;
			j_index = n[prev_j].pathlist[prev_j_index].pred_index;
		}
		int ppathsize = P.pathlist[i].path.size();
		if (ppathsize>pathsize_max)
		{
			pathsize_max = ppathsize;
		}
	}
	int sum_max = 0;
	int max_max = 0;
	for (int i = 0; i < graph.nodes; ++i)
	{
		int pathmatrixsize = n[i].pathmatrix.size();
		for (int j = 0; j < pathmatrixsize; ++j)
		{
			int sum = 0;
			int maximum = 0;
			for (int k = 0; k < 10; ++k)
			{
				int product_psize = n[i].pathmatrix[j].prodsize[k];
				sum+=product_psize;
				if (product_psize>maximum)
				{
					maximum = product_psize;
				}
			}
			if (sum>sum_max)
			{
				sum_max = sum;
			}
			if (maximum>max_max)
			{
				max_max = maximum;
			}
		}
	}
	P.n1 = pathsize_max;
	P.nbo = sum_max;
	P.nbmax = max_max;
	out<<nodeselection_count<<','<<arcprocess_count<<','<<P.n1<<','<<P.nbo<<','<<P.nbmax<<endl;
	return P;
}
