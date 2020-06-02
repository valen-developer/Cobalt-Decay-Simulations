#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "../lib/common_lib.h"
#include "../lib/common_3_4.h"

void gnuplot(int M, char *output_name);

int main(int argc, char *argv[])
{
    //verificamos inputs
    if (argc != 5)
    {
        printf("%s <N_0> <p> <step> <M> \n", argv[0]);
        exit(0);
    }

    //semilla para numeros aleatorios
    srand(time(NULL));

    //Asignamos valores por consola a variables modelo
    int N_0 = atoi(argv[1]);
    double p = atof(argv[2]);
    int step = atoi(argv[3]);
    int M = atoi(argv[4]);
    char output_name[256];
    snprintf(output_name, sizeof(output_name), "dataM%i.dat", M);

    //definimos array con numero de atomos e inicializamos a 1
    int *N = (int *)malloc(sizeof(int) * N_0);
    arrayCeltoOne(N, N_0);

    //Creamos memoria dinamica para almacenar la suma de N_k(j) (se ira redimensionando el array con realloc)
    long int *summN = (long int *)calloc(1, sizeof(long int));
    summN[0] = (N_0) * (M);

    /*Creamos array dinamico para guardar los tiempos. De igual forma, se redimensionara segun se vayan realizando pasos.
    Para no hacer el proceso en todas las repeticiones(aunque no consume muchos recursos), se realizara en la primera repeticion (M=1)*/
    double *savedTimes = (double *)calloc(1, sizeof(double));
    double t = 0;

    /*
        Obtenemos la sumatoria N_k(j) y tiempos.
        Podriamos trabajar perfectamente con los datos devueltos. 
    */
    SummAndTimesData summ_times_data = getSummAndTimes(N_0, p, M, t, summN, savedTimes);
    int arrayLength = summ_times_data.length;
    summN = summ_times_data.summN;
    savedTimes = summ_times_data.savedTimes;

    //Guardamos datos en fichero
    FILE *data = fopen(output_name, "w");
    for (int i = 0; i <= arrayLength; i += step)
    {
        long double F = (((double)N_0 - (double)summN[i] / (double)M) / (double)N_0);

        fprintf(data, "%f %Lf\n", savedTimes[i], F);
    }

    fclose(data);
    free(N);
    free(summN);
    free(savedTimes);

    //Generamos grafica
    gnuplot(M, output_name);

    return 0;
}

void gnuplot(int M, char *output_name)
{

    FILE *gnuplot = popen("gnuplot", "w");

    fprintf(gnuplot, "set xlabel 't: tiempo(años)'\n");
    fprintf(gnuplot, "set ylabel 'F(t): prob(X<=t).'\n");
    fprintf(gnuplot, "plot '%s' w p pointtype 5 ps 0.09, (1-exp(-(0.13*x))) title 'F(t)'\n", output_name);
    fprintf(gnuplot, "set terminal pdf\n");
    fprintf(gnuplot, "set output 'grafM%i.pdf'\n", M);
    fprintf(gnuplot, "rep");
    fclose(gnuplot);
}