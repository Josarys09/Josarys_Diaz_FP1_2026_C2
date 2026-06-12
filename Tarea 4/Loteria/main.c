#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
   int opcion = 0;
   int cantidadjugadas = 1;

   srand(time(NULL));

   while (opcion != 3)
   {
       printf("\n ------Menu-------\n");
       printf("1. Jugar\n");
       printf("2. Elegir cantidad de jugadas\n");
       printf("3. Salir\n");
       printf("Selecciona una opcion: ");
       scanf("%d", &opcion);

       switch(opcion)
       {
       case 1:
        for (int i = 1; i <= cantidadjugadas; i++)
        {
            int numerousuario;
            int dinero;
            int numerorandom;
            int ganado = 0;

            printf("\nJugada#%d\n", i);

            printf("Ingrese un numero del 1 al 40: ");

            scanf("%d", &numerousuario);

            while (numerousuario < 1 || numerousuario > 40)
            {
                printf("Numero invalido. Elige otro, por favor: ");
                scanf("%d", &numerousuario);
            }
            printf("Ingrese cantidad aportada: ");
            scanf("%d", &dinero);

            numerorandom = rand()% 40 + 1;

            if (numerousuario == numerorandom)
            {
                ganado = dinero * 1000;
            }
    printf("\n Resultados \n");
    printf("Numero jugado: %d\n", numerousuario);
    printf("Numero ganador: %d\n", numerorandom);
    printf("Cantidad apostada: %d\n", dinero);
    printf("Cantidad ganada: %d\n", ganado);
        }
        break;
       case 2:
        printf("Ingrese cantidad de jugadas: ");
        scanf("%d", &cantidadjugadas);

        break;
       case 3:
        printf("Saliendo\n");
        break;

       default:
        printf("Opcion invalida.\n");
       }
   }

   return 0;
}
