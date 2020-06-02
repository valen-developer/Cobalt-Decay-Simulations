#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

#include "../lib/common_lib.h"

#define M 1000000

void mainProcess(int _length_N, double p, char *output_name);
double findinArray(int *array, int query, int length);
int compareInt(const void *p, const void *q);
int verifyinData(int *array, int length, int query);
void gnuPlot();

int main(int argc, int argv[])
{

    //Definimos el numero de nucleos para cada experimento
    int *length_N = (int *)malloc(sizeof(int) * 4);
    length_N[0] = 20;
    length_N[1] = 50;
    length_N[2] = 100;
    length_N[3] = 1000;

    //Definimos el valor de p para cada experimento
    double *p = (double *)malloc(sizeof(double) * 4);
    p[0] = 0.5;
    p[1] = 0.2;
    p[2] = 0.1;
    p[3] = 0.01;

    char output_name[100];

    //Realizamos 4 experimentos con N-->inf y p-->0
    for (int i = 0; i < 4; i++)
    {
        snprintf(output_name, sizeof(output_name), "etapa%i.dat", (i + 1));
        printf("Inicia experimento %i\n", i);
        mainProcess(length_N[i], p[i], output_name);
        printf("Finaliza experimento %i\n", i);
    }

    //pintamos la grafica y la guardamos en pdf para Latex    
    gnuPlot();
    

    return 0;
}


void mainProcess(int _length_N, double p, char *output_name)
{
    //Inicializamos con semilla (tiempo actual) para generar posteriormente numeros aleatorios.
    srand(time(NULL));

    //Array de N elementos e inicializamos a 1
    int length_N = _length_N;
    int *N = (int *)malloc(sizeof(int) * length_N);
    arrayCeltoOne(N, length_N); //inicializamos a 1

    //fichero para guardar datos y representarlo en plot
    FILE *file_out = fopen(output_name, "w");

    //definimos array donde iremos guardando el numero de desintegraciones en casa experimento.
    int *x = (int *)malloc(sizeof(int) * M);

    //bucle en el que ejecutamos el mismo experimento un cierto numero de veces
    for (int j = 0; j < M; j++)
    {
        //realizamos experimento que devuelve cuantos atomos se han desintegrado en ese paso
        x[j] = experiment(N, length_N, p);
        //ponemos todos a 1 de nuevo para volver a realizar el experimento
        arrayCeltoOne(N, length_N); 
    }

    //ordenamos los datos de menor a mayor
    qsort(x, M, sizeof(int), &compareInt);

    //comprobamos la frecuencia de cada valor de x
    int *verify = (int *)calloc(M, sizeof(int)); //usamos este arreglo para que no se repitan los datos
    int verifyIndex = 0;
    for (int i = 0; i < M; i++)
    {

        //Comprobamos que no se repitan los datos
        if (verifyinData(verify, M, x[i]))
        {
            verify[verifyIndex] = x[i];
            verifyIndex++;
            double freq = findinArray(x, x[i], M) / M;
            fprintf(file_out, "%i %f\n", x[i], freq);
        }
    }

    fclose(file_out);
    free(N);
    free(verify);
    free(x);
}

//contamos veces que aparece la "query"
double findinArray(int *array, int query, int length)
{

    int counter = 0;

    for (int i = 0; i < length; i++)
    {
        if (array[i] == query)
            counter++;
    }
    return (double)counter;
}

/*Usamos esta funcion para el metodo de ordenacion "quicksort".
La cual recibe 2 punteros de elementos a comparar y devuelve
si es menor, mayor o igual.
Anterior a este metodo de ordenacion, se probo la implementacion
manual del metodo burbuja (para obtener habilidad con C), 
pero fue descartado por ineficiencia.
El metodo quicksort no se ha implementado manualmente 
por falta de tiempo.
*/
int compareInt(const void *_p, const void *_q)
{
    int *p, *q;
    p = (int *)_p;
    q = (int *)_q;
    return (*p - *q);
}

//verificamos que el valor de x no se duplica para plot
int verifyinData(int *array, int length, int query)
{

    for (int i = 0; i < length; i++)
    {
        if (array[i] == query && query != 0)
            return 0;
    }
    return 1;
}

//comando para pintar nuestra grafica
void gnuPlot()
{
    char data[4][100];

    for (int i = 0; i < 4; i++)
    {
        snprintf(data[i], sizeof(data[i]), "etapa%i.dat", (i + 1));        
    }
    FILE *gnuplot = popen("gnuplot", "w");

    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'p(x)'\n");
    fprintf(gnuplot, "plot '%s' w l,'%s' w l,'%s' w l,'%s' w l, ((10**x)*(exp(-10)))/gamma(x+1) title 'f(x)'\n",
            data[0], data[1], data[2], data[3]);
    fprintf(gnuplot, "%s\n", "set terminal pdf");
    fprintf(gnuplot, "%s\n", "set output 'graf.pdf'");
    fprintf(gnuplot, "%s\n", "rep");
    fprintf(gnuplot, "exit");
    pclose(gnuplot);
    printf("Grafico generado\n");
}

