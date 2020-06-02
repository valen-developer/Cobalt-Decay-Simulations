#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "../lib/common_lib.h"
#include "../lib/common_3_4.h"



void gnuplot(int M, int l, double p,char *output_name);

int main(int argc, char *argv[])
{

    //verificamos inputs (se añade la posibilidad de elegir el nombre del archivo de salida)
    if (argc != 5)
    {
        printf("%s <N_0> <p> <l> <M> \n", argv[0]);
        exit(0);
    }

    //semilla para numeros aleatorios
    srand(time(NULL));

    int N_0 = atoi(argv[1]);
    double p = atof(argv[2]);
    int l = atoi(argv[3]);
    int M = atoi(argv[4]);
    char output_name[256];
    snprintf(output_name, sizeof(output_name), "dataM%i.dat", M);

    //definimos array con numero de atomos e inicializamos a 1
    int *N = (int *)malloc(sizeof(int) * N_0);
    arrayCeltoOne(N, N_0);

    //fichero donde guardaremos los datos de la simulacion
    FILE *data = fopen(output_name, "w");

    //Creamos memoria dinamica para almacenar la suma de N_k(j) (se ira redimensionando el array con realloc)
    long int *summN = (long int *)calloc(1, sizeof(long int));
    summN[0] = (N_0) * (M);

    /*Creamos array dinamico para guardar los tiempos. De igual forma, se redimensionara segun se vayan realizando pasos.
    Para no hacer el proceso en todas las repeticiones(aunque no consume muchos recursos), se realizara en la ultima repeticion (M-esima)*/
    double *savedTimes = (double *)calloc(1, sizeof(double));
    double t = 0;

    /*
        Obtenemos la sumatoria N_k(j) y tiempos.
        Podriamos trabajar perfectamente con los datos devueltos. 
    */
    SummAndTimesData summ_times_data = getSummAndTimes(N_0, p, M, t, summN, savedTimes);
    int arraylength = summ_times_data.length;
    summN = summ_times_data.summN;
    savedTimes = summ_times_data.savedTimes;

    //guardamos en fichero los datos obtenidos
    for (int i = 0; i <= arraylength - l; i += l)
    {
        double prob = (double)(((double)summN[i + l]) / ((double)summN[i]));

        fprintf(data, "%f %f\n", savedTimes[i], prob);
    }

    //Liberamos memoria
    fclose(data);
    free(N);
    free(summN);
    free(savedTimes);

    //Pintamos la grafica en pdf
    gnuplot(M, l, p, output_name );

    return 0;
}


void gnuplot(int M, int l, double p,char *output_name){

    FILE *gnuplot = popen("gnuplot", "w");

    fprintf(gnuplot, "set xlabel 't: tiempo(años)'\n");
    fprintf(gnuplot, "set ylabel 'prob(X>t+Dt|X>t)'\n");
    fprintf(gnuplot, "plot '%s' w p pt 5 ps 0.1, (exp(-%i*%f)) title 'F(t)'\n", output_name, l, p);
    fprintf(gnuplot, "set terminal pdf\n");
    fprintf(gnuplot, "set output 'grafM%i.pdf'\n", M);
    fprintf(gnuplot, "rep");
    fclose(gnuplot);




}