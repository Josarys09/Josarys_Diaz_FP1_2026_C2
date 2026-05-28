#include <stdio.h>
#include <stdlib.h>

/*Promedio curso. El programa, al recibir como dato un promedio de un alumno universitario, escribe aprobado si su promedio es mayor a 6.
PRO: variable de tipo real. */

void main(void)
{
    float PRO;
    printf("Ingrese el promedio del alumno:");
    scanf("%f", &PRO);
    if (PRO >= 6)
        printf("\nAprovado");
}
