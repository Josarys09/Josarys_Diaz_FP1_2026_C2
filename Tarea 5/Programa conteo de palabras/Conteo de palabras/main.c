#include <stdio.h>
#include <stdlib.h>

int main()
{
    char frase[100];
    int i, palabras = 0;

    printf("\n Escribe una frase: \n");
    fgets(frase, 100, stdin);

    if (frase[0] != ' ' && frase[0] != '\n')
    {
        palabras++;
    }
    for (i= 1; frase[i] != '\0'; i++)
    {
        if(frase[i] != ' ' && frase [i+1] == ' ')
        {
            palabras++;
        }
    }

    printf("La frase tiene %d palabras. \n", palabras);
    return 0;
}
