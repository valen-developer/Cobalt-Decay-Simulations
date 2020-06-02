/*
    Libreria usada en los ejercicios 3 y 4. Contiene los siguientes objetos:
        - Estructura usada para devolver datos al programa principal.
        - Funcion que calcula la sumatoria de atomos desintegrados en cada uno de los tiempos y los tiempos
            mismos, y devuelve esta informacion, en forma de puntero, y la longitud de estos punteros. 
*/



#if !defined(_COMMON_3_4_)
#define _COMMON_3_4_

//Creamos una estructura para poder devolver los nuevos punteros devueltos por realloc y "cuantos tiempos han pasado"
typedef struct SummAndTimesData
{
    int length;
    long int *summN;
    double *savedTimes;
}SummAndTimesData;
struct SummAndTimesData getSummAndTimes(int N_0, double p, int M, double t, long int *summN, double *savedTimes);




#endif // _COMMON_3_4_
