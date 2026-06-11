#include <stdio.h>
#include <stdlib.h>

/* Prueba de parametro de referencia. */

void f1(int *);
/* Protocolo de funcion. El parametro es de tipo entero y por referencia observa el uso del operador de indireccion. */

void main(void)
{
    int I, K = 4;
    for ( I = 1; I <= 3; I++)
    {
        printf("\n\nValor de K antes de llamar a la funcion: %d", ++K);
        printf("\nValor de K despues de llamar a la funcion: %d", f1(&K));
        /* Llamada a la funcion f1. se pasa la direccion de la variable K, por medio del operador de direccion: &. */
    }
}
void f1(int *R)
/* la funcion f1 e=recibe un parametro por referencia. cada vez que el operador parametro se utiliza en la fucnion debe ir precedido por el operador de indireccion. */
{
    *R += *R;
}
