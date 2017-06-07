#include <iostream>
#include <math.h>
#include "basicarr.h"
using namespace std;
int basicarr::same_mat(int *a, int *b, int n,int m)
{
    int returnval = 1;
    if(m!=n)
        returnval = 0;
    else
        {
            for(int i=0;i<n;i++)
                {
                    if(a[i]!=b[i])
                    {
                        returnval = 0;
                        break;
                    }
                }
        }
    return returnval;
}