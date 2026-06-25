#include <stdio.h>
#include <stdlib.h>

int main()
{
    char frase[100];
    int codigo, i, opcion;

    printf("\nSelecciona una opcion: \n");
    printf("\n1. Codificar\n");
    printf("2. Decodificar\n\n");
    scanf("%d", &opcion);
    getchar();
    printf("Ingrese una frase: ");
    fgets(frase, 100, stdin);

    printf("Ingrese el numero del codigo: ");
    scanf("%d", &codigo);

    for(i=0; frase[i] != '\0'; i++)
    {
        if (opcion == 1)
        {
          if(frase[i] >= 'A' && frase[i] <= 'Z')
            frase[i] = ((frase[i] - 'A' + codigo) %26) + 'A';

         else if(frase[i] >= 'a' && frase[i] <= 'z')
         frase[i] = ((frase[i] - 'a' + codigo) % 26) + 'a';
        }
        else if (opcion == 2)
        {
            if (frase[i] >= 'A' && frase[i] <= 'Z')
                frase[i] = ((frase[i] - 'A' -codigo + 26) % 26) + 'A';
            else if (frase[i] >= 'a' && frase[i] <= 'z')
                frase[i] = ((frase[i] - 'a' - codigo + 26)% 26) + 'a';
        }
        }
        if (opcion == 1)
        printf("\nLa frase codificada es: %s", frase);
        else if (opcion == 2)
            printf("\nLa frase decodificada es: %s", frase);
        else
            printf("\nLa opcion no es valida.");

    return 0;
}
