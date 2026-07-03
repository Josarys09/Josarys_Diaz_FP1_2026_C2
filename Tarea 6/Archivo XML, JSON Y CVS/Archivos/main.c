#include <stdio.h>
#include <string.h>

struct Alumno
{
    char matricula[20];
    char nombre[50];
    int edad;
    char carrera[50];
};

 void mostrarTabla(struct Alumno alumnos[], int cantidad)
{
    int i;

    printf("\n--------------------------------------------------------------\n");
    printf("%-12s %-20s %-5s %-20s\n", "Matricula", "Nombre", "Edad", "Carrera");
    printf("--------------------------------------------------------------\n");

    for(i=0; i<cantidad; i++)
    {
        printf("%-12s %-20s %-5d %-20s\n",
               alumnos[i].matricula,
               alumnos[i].nombre,
               alumnos[i].edad,
               alumnos[i].carrera);
    }

    printf("--------------------------------------------------------------\n");
}

void leerCSV()
{
    FILE *archivo;
    struct Alumno alumnos[10];
    int i = 0;
    char linea[200];

    archivo = fopen("alumnos.csv", "r");

    if(archivo == NULL)
    {
        printf("No se pudo abrir alumnos.csv\n");
        return;
    }

    fgets(linea, sizeof(linea), archivo);

    while(fgets(linea, sizeof(linea), archivo))
    {
        sscanf(linea,"%[^,],%[^,],%d,%[^\n]",
               alumnos[i].matricula,
               alumnos[i].nombre,
               &alumnos[i].edad,
               alumnos[i].carrera);
        i++;
    }

    fclose(archivo);

    printf("\n=========== ARCHIVO CSV ===========\n");
    mostrarTabla(alumnos, i);
}

void leerXML()
{
    FILE *archivo;
    struct Alumno alumnos[10];
    char linea[200];
    int i = -1;

    archivo = fopen("alumnos.xml", "r");

    if(archivo == NULL)
    {
        printf("No se pudo abrir alumnos.xml\n");
        return;
    }

    while(fgets(linea, sizeof(linea), archivo))
    {
        if(strstr(linea, "<alumno>"))
            i++;

        if(strstr(linea, "<matricula>"))
            sscanf(linea, " <%*[^>]>%[^<]", alumnos[i].matricula);

        if(strstr(linea, "<nombre>"))
            sscanf(linea, " <%*[^>]>%[^<]", alumnos[i].nombre);

        if(strstr(linea, "<edad>"))
            sscanf(linea, " <%*[^>]>%d", &alumnos[i].edad);

        if(strstr(linea, "<carrera>"))
            sscanf(linea, " <%*[^>]>%[^<]", alumnos[i].carrera);
    }

    fclose(archivo);

    printf("\n=========== ARCHIVO XML ===========\n");
    mostrarTabla(alumnos, i + 1);
}

void leerJSON()
{
    FILE *archivo;
    struct Alumno alumnos[10];
    char linea[200];
    int i = -1;

    archivo = fopen("alumnos.json", "r");

    if(archivo == NULL)
    {
        printf("No se pudo abrir alumnos.json\n");
        return;
    }

    while(fgets(linea, sizeof(linea), archivo))
    {
        if(strchr(linea, '{'))
            i++;

        if(strstr(linea, "\"matricula\""))
            sscanf(linea, " \"matricula\":\"%[^\"]\"", alumnos[i].matricula);

        if(strstr(linea, "\"nombre\""))
            sscanf(linea, " \"nombre\":\"%[^\"]\"", alumnos[i].nombre);

        if(strstr(linea, "\"edad\""))
            sscanf(linea, " \"edad\":%d", &alumnos[i].edad);

        if(strstr(linea, "\"carrera\""))
            sscanf(linea, " \"carrera\":\"%[^\"]\"", alumnos[i].carrera);
    }

    fclose(archivo);

    printf("\n=========== ARCHIVO JSON ===========\n");
    mostrarTabla(alumnos, i + 1);
}

int main()
{
    leerCSV();
    leerXML();
    leerJSON();

    return 0;
}
