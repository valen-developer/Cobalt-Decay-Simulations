#include "stdio.h"
#include "stdlib.h"

#define N_0 10000
#define lambda 0.13

void gnuplot();

int main(int argc, char **argv)
{

    float p[4];
    p[0] = 0.5;
    p[1] = 0.1;
    p[2] = 0.01;
    p[3] = 0.001;

    int step = 1;

    char command[4][256];

    FILE *executor;

    for (int i = 0; i < 4; i++)
    {
        if(i>1){
            if(i>2){
                step = 10;
            }else{
                step = 5;
            }
        }

        //Se inicia el programa ejer2 para cada una de las situaciones. Se pasan los datos por linea de comandos. 
        snprintf(command[i], sizeof(command[i]), "./ejer2 %i %f %i 'data%i.dat'", N_0, p[i], step, (i + 1));
        executor = popen(command[i], "w");
        pclose(executor);
    }

    gnuplot();

    return 0;
}

void gnuplot()
{
    //Realizamos una grafica usando gnuplot

    char data[4][256];

    for (int i = 0; i < 4; i++)
    {
        snprintf(data[i], sizeof(data[i]), "data%i.dat", (i + 1));
    }

    FILE *gnuplot = popen("gnuplot", "w");

    fprintf(gnuplot, "set xlabel 't(años)'\n");
    fprintf(gnuplot, "set ylabel 'N(t). atomos sin desintegrar'\n");
    fprintf(gnuplot, "plot '%s' w l, '%s' w l, '%s' w l, '%s' w l, (%i)*(exp(-%f*x)) title 'N(t)' lt rgb '#ff2800'\n",
            data[0], data[1], data[2], data[3], N_0, lambda);
    fprintf(gnuplot, "set terminal pdf\n");
    fprintf(gnuplot, "set output 'graf.pdf'\n");
    fprintf(gnuplot, "rep\n");    
    pclose(gnuplot);

    gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "set xlabel 't(años)'\n");
    fprintf(gnuplot, "set ylabel 'N(t). atomos sin desintegrar'\n");
    fprintf(gnuplot, "set xrange [50:]\n");    
    fprintf(gnuplot, "plot '%s' w l, (%i)*(exp(-%f*x)) title 'N(t)' lt rgb '#ff2800'\n", data[3], N_0, lambda);
    fprintf(gnuplot, "set terminal pdf\n");
    fprintf(gnuplot, "set output 't50.pdf'\n"); //Debido a que p es pequeño, cuando quedan pocos atomos es muy improbable que se decaiga alguno. 
    fprintf(gnuplot, "rep\n");
    pclose(gnuplot);

}
