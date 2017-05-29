#include <iostream>
#include <math.h>
#include "basic.h"
using namespace std;
double basic::min(double a, double b)
{
	if(a<b)
	return a;
	else
	return b;
}
int basic::min(int a, int b)
{
	if(a<b)
	return a;
	else
	return b;
}
double basic::mean(double *arr,int n)
{
	double MEAN = 0;
	for (int i = 0; i < n; i++)
	{
		MEAN += arr[i];
	}
	MEAN=MEAN/n;
	return MEAN;
}
double basic::mean(int *arr,int n)
{
	double MEAN = 0;
	for (int i = 0; i < n; i++)
	{
		MEAN += arr[i];
	}
	MEAN=MEAN/n;
	return MEAN;
}
double basic::SD(double *arr, int n)
{
	double VAR=0;
	double MEAN = mean(arr, n);
	for (int i = 0; i < n; i++)
	{
		VAR += (arr[i] - MEAN)*(arr[i] - MEAN);
	}
	double STDDEV = sqrt(VAR)/sqrt(n-1);
	return STDDEV;
}
double basic::SD(int *arr, int n)
{
	double VAR=0;
	double MEAN = mean(arr, n);
	for (int i = 0; i < n; i++)
	{
		VAR += (arr[i] - MEAN)*(arr[i] - MEAN);
	}
	double STDDEV = sqrt(VAR)/sqrt(n-1);
	return STDDEV;
}
void basic::merge(double *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    double L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
} 
void basic::mergeSort(double *arr, int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
void basic::merge(int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
} 
void basic::mergeSort(int *arr, int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
double basic::minarrvalue(double *arr, int n)
{
  double *restarr;
  restarr = new double[n-1];
  for(int i=0;i<n-1;i++)
  {
    restarr[i]=arr[i+1];
  }
  if(n>1)
    return min(arr[0],minarrvalue(restarr,n-1));
  else
    return arr[0];
}