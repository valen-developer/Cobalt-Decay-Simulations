## PEC LENGUAJE C - GRADO FISICA

Se realizan una serie de simulaciones sobre el proceso de desintegracion del atomo de cobalto-60

Para realizar las diferentes simulaciones: 

# Simulacion 1 (Ejercicio 1): 

	Navegar hasta la carpeta "Ejercicio1"

``
cd Ejercicio1/
``

	Compilar: 

``
gcc ejer1.c ../lib/common_lib.c -o ejer1
``

	Ejecutar programa(realizará todas las etapas automaticamente):

``
./ejer1 
``

# Simulacion 2 (Ejercicio 2):

	Navegar hasta la carpeta "Ejercicio2"
``
cd Ejercicio2/
``

	Compilar simulacion: 
``
gcc ejer2.c ../lib/common_lib.c -o ejer2
``

	Podemos realizar las simulaciones introduciendo los datos manualmente o usar el "executor" para automatizar las salidas pedidas en el ejercicio.
	
	Ejecutar manualmente:

``
./ejer2 <N_0> <p> <step> <output_data_name>
``

	Ejecutar mediante "executor":
	1-Compilamos executor:

``
gcc -o executor executor.c
``
	2-Ejecutamos "executor":
``
./executor
``

# Simulacion 3 (Ejercicio 3):

	Navegar hasta la carpeta "Ejercicio1"

``
cd Ejercicio3/
``

	Compilar: 

``
gcc ejer1.c ../lib/common_lib.c ../lib/common_3_4.c -o ejer3
``

	Ejecutar programa:

``
./ejer3 <N_0> <p> <step> <M> <output_data_name>
``

# Simulacion 4 (Ejercicio 4):

	Naavegar hasta la carpeta "Ejercicio1"

``
cd Ejercicio4/
``

	Compilar: 

``
gcc ejer1.c ../lib/common_lib.c ../lib/common_3_4.c -o ejer3
``

	Ejecutar programa:
	
``
./ejer3 <N_0> <p> <l> <M> <output_data_name> 
``
