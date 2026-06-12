#include <stdio.h>

/*Promedio curso. Este programa al recibir como dato el promedio de un alumno en un curso universitario, escribe aprobado si su
promedio es mayor o igual a 6, o reprobado en caro contrario.

PRO: Variable de tipo real. */

void main (void)
{
    float PRO;
    printf("Ingrese el promedio del alumno: ");
    scanf("%f", &PRO);
    if (PRO >= 6.0)
        printf("\nAprobado");
    else
        printf("\nReprobado");
}
