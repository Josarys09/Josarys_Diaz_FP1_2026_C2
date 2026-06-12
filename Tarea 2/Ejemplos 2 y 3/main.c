#include <stdio.h>

/*Promedio curso. El programa recibe el promedio del alumno. Si su promedio es mayor o igual a 6 escriibe aprobado.

PRO: variable de tipo real. */

void main(void)
{
    float PRO;
    printf("Ingrese el promedio del alumno: ");
    scanf("%f", &PRO);
    if (PRO >= 6)
        printf("\nAprobado");
}
