#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOMBRE   50
#define TAM_DESC     150
#define TAM_TIPO     40
#define TAM_NIVEL    30
#define TAM_ARCHIVO  100

/*
   ESTRUCTURA: representa un riesgo y sus datos del metodo Mosler

   F = Funcion         S = Sustitucion
   P = Profundidad     E = Extension
   A = Agresion        V = Vulnerabilidad

   Cada uno se valora del 1 al 5. La suma (C = F+S+P+E+A+V) da
   un numero entre 6 y 30 que se traduce en un nivel de gravedad */

typedef struct {
    int  id;
    char nombre[TAM_NOMBRE];
    char descripcion[TAM_DESC];
    char tipo[TAM_TIPO];
    int  F, S, P, E, A, V;      /* parametros del metodo Mosler */
    int  resultado;             /* suma F+S+P+E+A+V             */
    char nivel[TAM_NIVEL];      /* texto de gravedad final      */
    int  calculado;             /* 1 si ya se calculo, 0 si no  */
} Riesgo;


Riesgo *riesgos = NULL;
int cantidad = 0;
int capacidad = 0;
int siguienteId = 1;
char archivoActual[TAM_ARCHIVO] = "riesgos.csv";

void mostrarMenu(void);
void limpiarBuffer(void);
int  leerEntero(const char *mensaje, int min, int max);
void leerCadena(const char *mensaje, char *destino, int tam);

void asegurarCapacidad(void);
int  buscarPorId(int id);

void crearRiesgo(void);
void modificarRiesgo(void);
void calcularMosler(Riesgo *r);
void calcularRiesgos(void);
void clasificarGravedad(Riesgo *r);
void imprimirUnRiesgo(const Riesgo *r);
void imprimirRiesgos(void);
void borrarRiesgo(void);

void seleccionarArchivo(void);
void crearArchivoNuevo(void);
void guardarRiesgos(void);
void cargarRiesgos(void);
void liberarMemoria(void);

int main(void) {
    int opcion;

    printf("=== SISTEMA DE EVALUACION DE RIESGOS (METODO MOSLER) ===\n");
    printf("Archivo de trabajo actual: %s\n", archivoActual);

    do {
        mostrarMenu();
        opcion = leerEntero("Elige una opcion: ", 1, 10);

        switch (opcion) {
            case 1:  crearRiesgo();        break;
            case 2:  modificarRiesgo();    break;
            case 3:  calcularRiesgos();    break;
            case 4:  imprimirRiesgos();    break;
            case 5:  borrarRiesgo();       break;
            case 6:  seleccionarArchivo(); break;
            case 7:  crearArchivoNuevo();  break;
            case 8:  guardarRiesgos();     break;
            case 9:  cargarRiesgos();      break;
            case 10:
                printf("Liberando memoria y saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
        printf("\n");
    } while (opcion != 10);

    liberarMemoria();
    return 0;
}


void mostrarMenu(void) {
    printf("----------------------------------------\n");
    printf(" 1. Crear riesgo\n");
    printf(" 2. Modificar parametros de un riesgo\n");
    printf(" 3. Calcular riesgos\n");
    printf(" 4. Imprimir los riesgos\n");
    printf(" 5. Borrar riesgo\n");
    printf(" 6. Seleccionar un archivo especifico\n");
    printf(" 7. Crear un archivo especifico\n");
    printf(" 8. Guardar riesgos\n");
    printf(" 9. Cargar riesgos desde disco\n");
    printf("10. Salir\n");
    printf("----------------------------------------\n");
}

/* Limpia el buffer de entrada (los caracteres sobrantes tras un scanf) */
void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {

    }
}
int leerEntero(const char *mensaje, int min, int max) {
    int valor;
    int correcto;

    do {
        printf("%s", mensaje);
        correcto = scanf("%d", &valor);
        limpiarBuffer();

        if (correcto != 1) {
            printf("Entrada invalida. Debes escribir un numero.\n");
            valor = min - 1; /* fuerza a repetir el ciclo */
        } else if (valor < min || valor > max) {
            printf("El valor debe estar entre %d y %d.\n", min, max);
        }
    } while (correcto != 1 || valor < min || valor > max);

    return valor;
}

/* Pide una cadena de texto y quita el salto de linea final */
void leerCadena(const char *mensaje, char *destino, int tam) {
    printf("%s", mensaje);
    fgets(destino, tam, stdin);
    destino[strcspn(destino, "\n")] = '\0'; /* elimina el '\n' */
}


void asegurarCapacidad(void) {
    if (cantidad < capacidad) {
        return;
    }

    int nuevaCapacidad = (capacidad == 0) ? 4 : capacidad * 2;
    Riesgo *temp = realloc(riesgos, nuevaCapacidad * sizeof(Riesgo));

    if (temp == NULL) {
        printf("ERROR: no se pudo reservar memoria.\n");
        exit(1);
    }

    riesgos = temp;
    capacidad = nuevaCapacidad;
}

int buscarPorId(int id) {
    int i;
    for (i = 0; i < cantidad; i++) {
        if (riesgos[i].id == id) {
            return i;
        }
    }
    return -1;
}

void crearRiesgo(void) {
    asegurarCapacidad();

    Riesgo *r = &riesgos[cantidad];

    r->id = siguienteId++;
    leerCadena("Nombre del riesgo: ", r->nombre, TAM_NOMBRE);
    leerCadena("Descripcion: ", r->descripcion, TAM_DESC);
    leerCadena("Tipo o categoria del riesgo: ", r->tipo, TAM_TIPO);

    printf("\n-- Parametros del metodo Mosler (valora cada uno de 1 a 5) --\n");
    r->F = leerEntero("Funcion (F): ", 1, 5);
    r->S = leerEntero("Sustitucion (S): ", 1, 5);
    r->P = leerEntero("Profundidad (P): ", 1, 5);
    r->E = leerEntero("Extension (E): ", 1, 5);
    r->A = leerEntero("Agresion (A): ", 1, 5);
    r->V = leerEntero("Vulnerabilidad (V): ", 1, 5);

    r->resultado = 0;
    strcpy(r->nivel, "Sin calcular");
    r->calculado = 0;

    cantidad++;
    printf("Riesgo creado con ID = %d.\n", r->id);
    printf("(Usa la opcion 3 para calcular su gravedad).\n");
}

void modificarRiesgo(void) {
    if (cantidad == 0) {
        printf("No hay riesgos registrados.\n");
        return;
    }

    int id = leerEntero("ID del riesgo a modificar: ", 1, 1000000);
    int pos = buscarPorId(id);

    if (pos == -1) {
        printf("No existe un riesgo con ese ID.\n");
        return;
    }

    Riesgo *r = &riesgos[pos];
    printf("Deja los datos como estan escribiendo un cambio nuevo.\n");

    leerCadena("Nuevo nombre: ", r->nombre, TAM_NOMBRE);
    leerCadena("Nueva descripcion: ", r->descripcion, TAM_DESC);
    leerCadena("Nuevo tipo: ", r->tipo, TAM_TIPO);

    printf("\n-- Nuevos valores del metodo Mosler (1 a 5) --\n");
    r->F = leerEntero("Funcion (F): ", 1, 5);
    r->S = leerEntero("Sustitucion (S): ", 1, 5);
    r->P = leerEntero("Profundidad (P): ", 1, 5);
    r->E = leerEntero("Extension (E): ", 1, 5);
    r->A = leerEntero("Agresion (A): ", 1, 5);
    r->V = leerEntero("Vulnerabilidad (V): ", 1, 5);


    r->calculado = 0;
    strcpy(r->nivel, "Sin calcular");

    printf("Riesgo modificado. Recuerda volver a calcularlo (opcion 3).\n");

    /* F = Funcion
       S = Sustitucion
       P = Profundidad
       E = Extension
       A = Agresion
       V = Vulnerabilidad

       I = F x S
       D = P x E
       C = I + D
       Pb = A x V
       ER = C x Pb */

}
  void calcularMosler(Riesgo *r) {
    int I;
    int D;
    int C;
    int Pb;
    int ER;

    I = r->F * r->S;
    D = r->P * r->E;

    C = I + D;

    Pb = r->A * r->V;

    ER = C * Pb;

    r->resultado = ER;

    clasificarGravedad(r);
    r->calculado = 1;

}

void clasificarGravedad(Riesgo *r) {
    int c = r ->resultado;

     if (c >= 2 && c <= 250) {
        strcpy(r->nivel, "Muy pequeno");
    } else if (c <= 500) {
        strcpy(r->nivel, "Pequeno");
    } else if (c <= 750) {
        strcpy(r->nivel, "Normal");
    } else if (c <= 1000) {
        strcpy(r->nivel, "Grande");
    } else if (c <= 1250) {
        strcpy(r->nivel, "Elevado");
    } else {
        strcpy(r->nivel, "Fuera de rango");
    }
}

/* Opcion 3 del menu: calcula uno o todos los riesgos */
void calcularRiesgos(void) {
    if (cantidad == 0) {
        printf("No hay riesgos registrados.\n");
        return;
    }

    printf("Escribe el ID del riesgo a calcular, o 0 para calcularlos todos.\n");
    int id = leerEntero("ID (0 = todos): ", 0, 1000000);

    if (id == 0) {
        int i;
        for (i = 0; i < cantidad; i++) {
            calcularMosler(&riesgos[i]);
        }
        printf("Se calcularon los %d riesgos.\n", cantidad);
    } else {
        int pos = buscarPorId(id);
        if (pos == -1) {
            printf("No existe un riesgo con ese ID.\n");
            return;
        }
        calcularMosler(&riesgos[pos]);
        printf("Calculo terminado:\n");
      int I, D, C, Pb;

      I = riesgos[pos].F * riesgos[pos].S;
      D = riesgos[pos].P * riesgos[pos].E;
      C = I + D;
      Pb = riesgos[pos].A * riesgos[pos].V;

      printf("\n--- CALCULO DEL METODO MOSLER ---\n");
      printf("I = F x S = %d x %d = %d\n",
       riesgos[pos].F, riesgos[pos].S, I);

      printf("D = P x E = %d x %d = %d\n",
       riesgos[pos].P, riesgos[pos].E, D);

      printf("C = I + D = %d + %d = %d\n",
       I, D, C);

      printf("Pb = A x V = %d x %d = %d\n",
       riesgos[pos].A, riesgos[pos].V, Pb);

      printf("ER = C x Pb = %d x %d = %d\n",
       C, Pb, riesgos[pos].resultado);

    printf("Clase de riesgo: %s\n", riesgos[pos].nivel);
    }
}


void imprimirUnRiesgo(const Riesgo *r) {
    printf("----------------------------------------\n");
    printf("ID: %d\n", r->id);
    printf("Nombre: %s\n", r->nombre);
    printf("Tipo: %s\n", r->tipo);
    printf("Descripcion: %s\n", r->descripcion);
    printf("Valores Mosler -> F:%d S:%d P:%d E:%d A:%d V:%d\n",
           r->F, r->S, r->P, r->E, r->A, r->V);

    if (r->calculado) {
        printf("Resultado (ER): %d\n", r->resultado);
        printf("Nivel de gravedad: %s\n", r->nivel);
    } else {
        printf("Resultado: aun no calculado\n");
    }
    printf("----------------------------------------\n");
}

void imprimirRiesgos(void) {
    if (cantidad == 0) {
        printf("No hay riesgos registrados.\n");
        return;
    }

    printf("Escribe un ID para ver un solo riesgo, o 0 para verlos todos.\n");
    int id = leerEntero("ID (0 = todos): ", 0, 1000000);

    if (id == 0) {
        int i;
        printf("\n=== LISTA DE RIESGOS (%d en total) ===\n", cantidad);
        for (i = 0; i < cantidad; i++) {
            imprimirUnRiesgo(&riesgos[i]);
        }
    } else {
        int pos = buscarPorId(id);
        if (pos == -1) {
            printf("No existe un riesgo con ese ID.\n");
        } else {
            imprimirUnRiesgo(&riesgos[pos]);
        }
    }
}


void borrarRiesgo(void) {
    if (cantidad == 0) {
        printf("No hay riesgos registrados.\n");
        return;
    }

    int id = leerEntero("ID del riesgo a eliminar: ", 1, 1000000);
    int pos = buscarPorId(id);

    if (pos == -1) {
        printf("No existe un riesgo con ese ID.\n");
        return;
    }

    char confirmacion[10];
    printf("Seguro que quieres eliminar el riesgo '%s'? (si/no): ", riesgos[pos].nombre);
    leerCadena("", confirmacion, sizeof(confirmacion));

    if (confirmacion[0] != 's' && confirmacion[0] != 'S') {
        printf("Operacion cancelada.\n");
        return;
    }

    /* Desplaza todos los riesgos posteriores una posicion a la izquierda */
    int i;
    for (i = pos; i < cantidad - 1; i++) {
        riesgos[i] = riesgos[i + 1];
    }
    cantidad--;

    /* Reduce la memoria reservada al nuevo tamanio exacto */
    if (cantidad == 0) {
        free(riesgos);
        riesgos = NULL;
        capacidad = 0;
    } else {
        Riesgo *temp = realloc(riesgos, cantidad * sizeof(Riesgo));
        if (temp != NULL) {
            riesgos = temp;
            capacidad = cantidad;
        }
    }

    printf("Riesgo eliminado correctamente.\n");
}


void seleccionarArchivo(void) {
    char nombre[TAM_ARCHIVO];
    leerCadena("Nombre del archivo existente a usar (ej. datos.csv): ", nombre, TAM_ARCHIVO);

    FILE *f = fopen(nombre, "r");
    if (f == NULL) {
        printf("Ese archivo no existe. Usa la opcion 7 para crearlo.\n");
        return;
    }
    fclose(f);

    strcpy(archivoActual, nombre);
    printf("Archivo activo ahora: %s\n", archivoActual);
}

void crearArchivoNuevo(void) {
    char nombre[TAM_ARCHIVO];
    leerCadena("Nombre del nuevo archivo (ej. datos.csv): ", nombre, TAM_ARCHIVO);

    FILE *f = fopen(nombre, "w"); /* "w" crea el archivo (vacio) */
    if (f == NULL) {
        printf("No se pudo crear el archivo.\n");
        return;
    }
    fclose(f);

    strcpy(archivoActual, nombre);
    printf("Archivo '%s' creado y seleccionado como activo.\n", archivoActual);
}

/* Guarda todos los riesgos en el archivo activo, una linea por riesgo */
void guardarRiesgos(void) {
    FILE *f = fopen(archivoActual, "w");
    if (f == NULL) {
        printf("No se pudo abrir '%s' para guardar.\n", archivoActual);
        return;
    }

    int i;
    for (i = 0; i < cantidad; i++) {
        Riesgo *r = &riesgos[i];
        fprintf(f, "%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%s\n",
                r->id, r->nombre, r->descripcion, r->tipo,
                r->F, r->S, r->P, r->E, r->A, r->V,
                r->resultado, r->nivel);
    }

    fclose(f);
    printf("Se guardaron %d riesgos en '%s'.\n", cantidad, archivoActual);
}

void cargarRiesgos(void) {
    FILE *f = fopen(archivoActual, "r");
    if (f == NULL) {
        printf("No se pudo abrir '%s'.\n", archivoActual);
        return;
    }


    liberarMemoria();

    char linea[512];
    int maxId = 0;

    while (fgets(linea, sizeof(linea), f) != NULL) {
        Riesgo temp;
        int leidos = sscanf(linea, "%d,%49[^,],%149[^,],%39[^,],%d,%d,%d,%d,%d,%d,%d,%29[^,\n]",
                             &temp.id, temp.nombre, temp.descripcion, temp.tipo,
                             &temp.F, &temp.S, &temp.P, &temp.E, &temp.A, &temp.V,
                             &temp.resultado, temp.nivel);

        if (leidos == 12) {
            temp.calculado = 1;
            asegurarCapacidad();
            riesgos[cantidad] = temp;
            cantidad++;
            if (temp.id > maxId) {
                maxId = temp.id;
            }
        }
    }

    fclose(f);
    siguienteId = maxId + 1; /* para no repetir IDs al crear nuevos riesgos */
    printf("Se cargaron %d riesgos desde '%s'.\n", cantidad, archivoActual);
}


void liberarMemoria(void) {
    free(riesgos);
    riesgos = NULL;
    cantidad = 0;
    capacidad = 0;
}
