#include <stdio.h>
#include <stdlib.h>

/*Cubo-3
Este progrema calcula el cubo de los primeros 10 numeros naturales con la
ayuda de una funcion y utilizando parametros por valor. */

int cubo (int);

void main(void)
{
    int I;
    for (I = 1; I <= 10; I++)
        printf("\nEl cubo de I es:%d", cubo(I));
    /*Llamada de la funcion cubo. el paso del parametro es por valor. */
}

int cubo(int K)
{
    return(K*K*K);
}
