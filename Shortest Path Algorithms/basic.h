#pragma once
using namespace std;
class basic
{
public:
	double min( double , double );
	int min( int , int );
	double mean( double*, int );
	double SD( double*, int );
	double mean( int*, int );
	double SD( int*, int );
	void merge(double*, int, int, int);
	void mergeSort(double*, int, int);
	void merge(int*, int, int, int);
	void mergeSort(int*, int, int);
	double minarrvalue(double*, int);
};