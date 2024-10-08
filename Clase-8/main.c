#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 128
#define MAXNOM 24
#define NOMARCH_POLINDROMO "prueba.txt"
#define NOMARCH_ESTUDIANTES "estudiantes.txt"

#define ESTRUC_EST_VARIABLE "%d|%s|%.2f\n"
#define ESTRUC_EST_FIJO "%4d %25s %5.2f\n"

typedef struct
{
    int leg;
    char nombre[MAXNOM];
    float prom;
} ESTS;

int crearEstudiantesVariable(const char* nomArch)
{
    ESTS est[] =
    {
        {10,"Maria",2.2},
        {20,"Juan",5.5},
        {30,"Mariana",1}
    };
    size_t i;

    FILE* arch = fopen(nomArch,"wt");

    if(!arch)
        return 0;

    for(i = 0 ; i < sizeof(est)/sizeof(*est); i++)
        fprintf(arch,ESTRUC_EST_VARIABLE, est[i].leg, est[i].nombre ,est[i].prom);

    fclose(arch);
    return 1;
}

int crearEstudiantesFijo(const char* nomArch)
{
    ESTS est[] =
    {
        {10,"Maria",2.2},
        {20,"Juan",5.5},
        {30,"Mariana",1}
    };
    size_t i;

    FILE* arch = fopen(nomArch,"wt");

    if(!arch)
        return 0;

    for(i = 0 ; i < sizeof(est)/sizeof(*est); i++)
        fprintf(arch,ESTRUC_EST_FIJO, est[i].leg, est[i].nombre ,est[i].prom);

    fclose(arch);
    return 1;
}

int crearPalindromos(const char* nomArch)
{
    char cad[][MAXLINE] = {
        {"menem"},
        {"oso"},
        {"Amad a la Dama"}
    };
    size_t i;

    FILE* arch = fopen(nomArch,"wt");

    if(!arch)
        return 0;

    for(i = 0 ; i < sizeof(cad)/MAXLINE; i++)
    {
        fprintf(arch,"%s\n", cad[i]);
    }

    fclose(arch);
    return 1;
}

int main(int argc,char* argv[])
{
    FILE *arch;
    ESTS est;
    char linea[MAXLINE];

    if(!crearPalindromos(NOMARCH_POLINDROMO))
        printf("No se pudo crear %s",NOMARCH_POLINDROMO);
    
    if(!crearEstudiantesFijo(NOMARCH_ESTUDIANTES))
        printf("No se pudo crear %s",NOMARCH_ESTUDIANTES);

    // LECTURA ARCH POLINDROMOS
    system("cls");
    arch = fopen(NOMARCH_POLINDROMO, "rt");
    
    if(!arch)
        return 1;
    
    // lee hasta nueva linea o fin de archivo
    while(fgets(linea, MAXLINE-1, arch))
    {
        printf("%s",linea);
    }
    fclose(arch);

    // LECTURA ARCH ESTUDIANTES
    system("cls");
    arch = fopen(NOMARCH_ESTUDIANTES, "rt");

    if(!arch)
        return 1;

    // Variable
    /*
    while(fgets(linea, 3, arch))
    {
        //sscanf(linea, "%d|%[^|]|%f", &(est.leg), est.nombre, &(est.prom));
        //printf("%d %s %.2f\n",est.leg, est.nombre, est.prom);
        printf("%s",linea);
    }
    */
   // FIJO
   int i = 0;
    while(fgets(linea, 3, arch))
    {
        i++;
        sscanf(linea, ESTRUC_EST_FIJO, &(est.leg), est.nombre, &(est.prom));
        printf(ESTRUC_EST_FIJO,est.leg, est.nombre, est.prom);
        //printf("%s",linea);
    }
    printf("%d",i);

    fclose(arch);
}
