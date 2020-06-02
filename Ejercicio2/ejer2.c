#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "../lib/common_lib.h"

#define lambda 0.13

void checkingArgs(int argc, char **argv);

int main(int argc, char **argv)
{

    //verificamos que se introduzcan los datos correctos por consola
    checkingArgs(argc, argv);

    //Generamos semilla para generar nº aleatorios en simulacion
    srand(time(NULL));

    //introducimos los valores por consola en variables modelo para trabajar facilmente
    int N_0 = atoi(argv[1]);
    double p = atof(argv[2]);
    int step = atof(argv[3]);
    double t = 0;
    char *output_name = argv[4];

    //Creamos int_array, que sera el numero de atomos, e inicializamos a 1(no desintegrado)
    int *N = (int *)malloc(sizeof(int) * N_0);
    arrayCeltoOne(N, N_0);

    //Archivo donde guardar los datos
    FILE *data = fopen(output_name, "w");
    fprintf(data, "0 %i\n", N_0); //en t=0, el numero de atomos sin desintegrar sera N_0

    printf("Inicia experimento\n");
    //Mientras exista algun atomo que no ha desintegrado sigue pasando el tiempo
    int decayedAtoms = 0;
    int i = 0; //usamos para elegir que pasos pintar
    while (decayedAtoms < N_0)
    {
        //random decay rule
        decayedAtoms += experiment(N, N_0, p);

        //Pasa el tiempo
        t += p / lambda;

        //Usamos esta condicion para elegir "pintar" menos datos, dependiendo del "paso"
        if ((i % step) == 0)
        {
            //"escribimos en fichero t vs #atomos sin desintegrar"
            fprintf(data, "%f %i\n", t, N_0 - decayedAtoms);
        }
        i++;
    }
    printf("Finaliza experimento\n");

    fclose(data);
    free(N);

    return 0;
}

void checkingArgs(int argc, char **argv)
{
    if (argc != 5)
    {
        printf("%s <N_0> <p> <step> <output_data_name>\n", argv[0]);
        exit(0);
    }
}
