#include "stdlib.h"

#include "common_lib.h"




void arrayCeltoOne(int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        array[i] = 1;
    }
}

int experiment(int *N, int length,double p)
{

    int counter = 0;

    for (int i = 0; i < length; i++)
    {
        if (N[i] == 1)
        {
            if (((double)rand() / (double)(RAND_MAX)) <= p)
            {
                N[i] = 0;
                counter++;
            }
        }
    }
    return counter;
}