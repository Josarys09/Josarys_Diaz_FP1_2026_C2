#include <stdio.h>

int main() {

    //  Aqui declaramos las matrices
    int matrizA[10][10];
    int matrizB[10][10];
    int resultado[10][10];

    // creamos las variables para guardar las filas y columnas.
    int filasA, columnasA;
    int filasB, columnasB;

    int i, j, k;

    // Aca pedimos el tamano de la primera matriz
    printf("Ingrese el numero de filas de la matriz A: ");
    scanf("%d", &filasA);

    printf("Ingrese el numero de columnas de la matriz A: ");
    scanf("%d", &columnasA);

    // de la segunda matriz
    printf("\nIngrese el numero de filas de la matriz B: ");
    scanf("%d", &filasB);

    printf("Ingrese el numero de columnas de la matriz B: ");
    scanf("%d", &columnasB);

    // Ahora para poder multiplicar las matrices, las columnas de A deben ser iguales a las filas de B
    if (columnasA != filasB) {

        printf("\nNo se pueden multiplicar las matrices.\n");

        return 0;
    }

    // ponemos los valores de la matriz A.
    printf("\nIngrese los valores de la matriz A:\n");

    for (i = 0; i < filasA; i++) {

        for (j = 0; j < columnasA; j++) {

            printf("A[%d][%d]: ", i, j);
            scanf("%d", &matrizA[i][j]);
        }
    }

    // ahora los valores de la matriz B
    printf("\nIngrese los valores de la matriz B:\n");

    for (i = 0; i < filasB; i++) {

        for (j = 0; j < columnasB; j++) {

            printf("B[%d][%d]: ", i, j);
            scanf("%d", &matrizB[i][j]);
        }
    }

    // Aqui realizamos la multiplicacion de las matrices.
    for (i = 0; i < filasA; i++) {

        for (j = 0; j < columnasB; j++) {

            // Inicializamos cada posicion del resultado en cero.
            resultado[i][j] = 0;

            // Hacemos las multiplicaciones y sumamos los resultados.
            for (k = 0; k < columnasA; k++) {

                resultado[i][j] = resultado[i][j]
                                + matrizA[i][k] * matrizB[k][j];
            }
        }
    }

    // Mostramos la matriz resultado
    printf("\nResultado de la multiplicacion:\n");

    for (i = 0; i < filasA; i++) {

        for (j = 0; j < columnasB; j++) {

            printf("%d\t", resultado[i][j]);
        }

        printf("\n");
    }

    return 0;
}