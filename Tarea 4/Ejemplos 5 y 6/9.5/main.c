#include <stdio.h>
#include <stdlib.h>

/* Busqueda secuencial en arreglos desordenados. */

const int MAX=100;

void Lectura(int *, int);
int Busca(int *, int, int);

void main(void)
{
    int RES, ELE, TAM, VEC[MAX];
    do
    {
        printf("Ingrese el tamaño del arreglo: ");
        scanf("%d", &TAM);
    }
    while (TAM>MAX || TAM<1);  /*Se verifica que el tamano del arreglo sea correcto. */
    Lectura(VEC, TAM);
    printf("\nIngrese el elemento a buscar:  ");
    scanf("%d", &ELE);
    RES = Busca(VEC, TAM, ELE);
    if (RES)
        /* Si RES tiene un valor verdadero - diferente a 0-, se escribe la posicion en la que se encontro el elemento. */
        printf("\nEl elemento se encuentra en la posicion %d", RES);
    else
        printf("\nEl elemento no se encuentra en el arreglo");
}
void Lectura(int A[], int T)
/* La funcion Lectura se utiliza para leer un arreglo unidimensional de T elementos de tipo entero. */
{
    int I;
    for (I=0; I<T; I++)
    {
        printf("Ingrese el elemento %d: ", I+1);
        scanf("%d", &A[I]);
    }
}

int Busca(int A[], int T, int K)
{
    int I = 0, BAN = 0, RES;
    while (I < T && !BAN)
        if (A[I] == K)
        BAN++;
    else
        I++;
    if (BAN)
        RES = I + 1;
    /* Se asigna I+1 dado que las posiciones en el arreglo comienzo desde cero. */

    else
        RES = BAN;
    return (RES);
}
