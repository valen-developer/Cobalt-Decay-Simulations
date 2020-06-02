#include "common_3_4.h"
#include "common_lib.h"

#include "stdlib.h"
#include "stdio.h"

#define lambda 0.13

struct SummAndTimesData getSummAndTimes(int N_0, double p, int M, double t, long int *summN, double *savedTimes)
{

    int *N = (int *)malloc(sizeof(int) * N_0);
    arrayCeltoOne(N, N_0);

    //Usamos para ir guardando la longitud del array de tiempos o sumatorio
    int j_aux = 0;

    for (int k = 1; k <= M; k++)
    {

        int j = 0;
        //Mientras exista algun atomo sin desintegrar, el bucle continua
        int decayedAtoms = 0;
        while (decayedAtoms < N_0)
        {
            //Realizamos el experimento mientras existan atomos sin desintegrar
            decayedAtoms += experiment(N, N_0, p);

            //reasignamos memoria (El tiempo se guarda en la primera ocasion y si exites un "tiempo nuevo")
            if (k == 1 || j >= j_aux)
            {

                summN = (long int *)realloc(summN, ((sizeof(long int)) * (j + 2)));
                savedTimes = (double *)realloc(savedTimes, ((sizeof(double)) * (j + 2)));
                //Comprobamos que se asigna correctamente memoria
                if (summN == NULL || savedTimes == NULL)
                {
                    printf("Asignacion de memoria fallo\n");
                    exit(1);
                }
                summN[j + 1] = 0;
                t += p / lambda;
                savedTimes[j + 1] = t;
            }

            summN[j + 1] += N_0 - decayedAtoms; 
            j++;
        }

        if (j_aux < j)
            j_aux = j;
        arrayCeltoOne(N, N_0);
    }

    SummAndTimesData summ_times_data;
    summ_times_data.length = j_aux;
    summ_times_data.summN = summN;
    summ_times_data.savedTimes = savedTimes;

    return summ_times_data;
}
