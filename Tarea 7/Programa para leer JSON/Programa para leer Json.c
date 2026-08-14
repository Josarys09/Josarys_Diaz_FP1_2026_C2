#include <stdio.h>

int main() {

    // Primero se abre el archivo json en modo lectura
    FILE *archivo = fopen("Archivos con datos de numeros.json", "r");

    // chequeamos si realmente se puede abrir
    if (archivo == NULL) {

        printf("No se pudo abrir el archivo.\n");

        return 0;
    }

    // Arreglo para contar cuantas veces aparece cada numero y como van de 0 a 100, necesitamos 101 posiciones
    int cantidad[101] = {0};

    //  guardamos la posicion donde aparece cada numero
    int posiciones[101][100];

    // las vaariables que necesitamos para trabajar con el archivo
    int numero;
    int posicion = 0;

    // Leemos el archivo numero por numero
    while (fscanf(archivo, "%*[^0-9]%d", &numero) == 1) {

        // tecesitamos comprobar que el numero este entre 0 y 100
        if (numero >= 0 && numero <= 100) {

            // Aumentamos la cantidad de veces que aparece ese numero
            cantidad[numero]++;

            // Guardamos la posicion donde aparecio.
            posiciones[numero][cantidad[numero] - 1] = posicion;

            // Aumentamos la posicion.
            posicion++;
        }
    }

    // se cierra el archivo
    fclose(archivo);

    // Variables para guardar los tres numeros que mas se repiten
    int primero = -1;
    int segundo = -1;
    int tercero = -1;

    int i;

    for (i = 0; i <= 100; i++) {     // se busca el primer numero  que mas se repite

        if (cantidad[i] > cantidad[primero]) {

            primero = i;
        }
    }

    // luego el segundo numero que mass se repite
   

    for (i = 0; i <= 100; i++) {

        if (i != primero && cantidad[i] > cantidad[segundo]) {

            segundo = i;
        }
    }

    for (i = 0; i <= 100; i++) {         //Se busca el tercer numro que mas se repite 

        if (i != primero &&
            i != segundo &&
            cantidad[i] > cantidad[tercero]) {

            tercero = i;
        }
    }
    // Mostramos cual es el resultado
   

    printf("\nLos tres numeros que mas se repiten son:\n");

    printf("\n1. Numero: %d", primero);
    printf("\n   Se repite: %d veces", cantidad[primero]);

    printf("\n   Posiciones: ");

    for (i = 0; i < cantidad[primero]; i++) {

        printf("%d ", posiciones[primero][i]);
    }

    printf("\n");

    printf("\n2. Numero: %d", segundo);
    printf("\n   Se repite: %d veces", cantidad[segundo]);

    printf("\n   Posiciones: ");

    for (i = 0; i < cantidad[segundo]; i++) {

        printf("%d ", posiciones[segundo][i]);
    }

    printf("\n");

    printf("\n3. Numero: %d", tercero);
    printf("\n   Se repite: %d veces", cantidad[tercero]);

    printf("\n   Posiciones: ");

    for (i = 0; i < cantidad[tercero]; i++) {

        printf("%d ", posiciones[tercero][i]);
    }

    printf("\n");

    return 0;
}