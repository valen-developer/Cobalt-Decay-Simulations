
/*
    Libreria comun a todas las simulaciones. Se definen las funciones:
        -arrayCeltoOne: Inicializa todos lo valores de un array de enteros a 1
        -experiment: recorre los elementos de array (que representan atomos) y cambia valor dependiente de numero aleatorio comparado con p
*/


#if !defined(_COMMON_LIB_)
#define _COMMON_LIB_

void arrayCeltoOne(int *array, int length);
int experiment(int *N, int length,double p);




#endif // _COMMON_LIB_




