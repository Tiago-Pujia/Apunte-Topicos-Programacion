#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define MAXNOM 24

typedef struct
{
    int leg;
    char nombre[MAXNOM];
    float prom;
} ESTS;

char* strrchr(char *str, const char buscar)
{
    char *posicion = NULL;
    const char *ini = str;

    while (*str) {
        if (*str == buscar)
            posicion = str;
        str++;
    }

    return posicion; 
}

/*
====================================
Texto No Estructurado
====================================
*/

#define NOMARCH_POLINDROMO "polindromos.txt"

// Escritura
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
        fprintf(arch,"%s\n", cad[i]);

    fclose(arch);
    return 1;
}

int lecturaPalindromos(const char* nomArch)
{
    FILE *arch = fopen(nomArch,"rt");
    char linea[MAXNOM];

    if(!arch)
        return 1;
    
    while(fgets(linea,MAXLINE-1,arch))
        printf("%s",linea);
    
    fclose(arch);
    return 0;
}

/*
====================================
Texto Estructurado Variable
====================================
*/

#define NOMARCH_ESTUDIANTES_VARIABLE "estudiantes(formato variable).txt"
#define ESTRUC_EST_VARIABLE_ESCRITURA "%d|%s|%.2f\n"
#define ESTRUC_EST_VARIABLE_LECTURA "%d|%[^|]|%f\n"
#define SEPARADOR '|'

// Escritura
int crearEstudiantesVariable(const char* nomArch)
{
    size_t i;
    ESTS est[] =
    {
        {10,"Maria Pia",2.2},
        {20,"Juan Domingo",5.5},
        {30,"Mariana",1}
    };
    FILE* arch = fopen(nomArch,"wt");

    if(!arch)
        return 0;

    for(i = 0 ; i < sizeof(est)/sizeof(*est) ; i++)
        fprintf(arch,ESTRUC_EST_VARIABLE_ESCRITURA, est[i].leg, est[i].nombre ,est[i].prom);

    fclose(arch);
    return 1;
}

// Lectura
int lecturaEstudiante(ESTS* est, char *linea)
{
    char *dirSeparador;

    // Lectura Promedio
    dirSeparador = strrchr(linea,SEPARADOR);
    if (!dirSeparador)
        return 0;
    sscanf(dirSeparador + 1,"%f",&(est->prom));
    *dirSeparador = '\0';

    // Lectura Nombre
    dirSeparador = strrchr(linea,SEPARADOR);
    if (!dirSeparador)
        return 0;
    sscanf(dirSeparador + 1,"%[^|]",est->nombre);
    *dirSeparador = '\0';

    // Lectura Legajo
    sscanf(linea,"%d",&(est->leg));

    return 1;
}

int lecturaEstudiantesVariable(const char* nomArch)
{
    FILE* arch = fopen(nomArch,"rt");
    ESTS est;
    char linea[MAXLINE];

    if(!arch)
        return 0;

    // Utilización con función fscanf
    printf("Funcion fscanf:\n");
    while(fscanf(arch, ESTRUC_EST_VARIABLE_LECTURA, &est.leg, est.nombre, &est.prom) != EOF)
        printf("%d %s %.2f\n",est.leg,est.nombre,est.prom);
    rewind(arch);

    // Manera Automatica
    printf("\nManera Automatica:\n");
    while(fgets(linea,MAXLINE,arch))
    {
        sscanf(linea, ESTRUC_EST_VARIABLE_LECTURA, &est.leg, est.nombre, &est.prom);
        printf("%d %s %.2f\n",est.leg,est.nombre,est.prom);
    }
    rewind(arch);

    // Manera Manual
    printf("\nManera Manual:\n");
    while(fgets(linea,MAXLINE,arch) && lecturaEstudiante(&est,linea))
        printf("%d %s %.2f\n",est.leg,est.nombre,est.prom);

    fclose(arch);
    return 1;
}

/*
====================================
Texto Estructurado Fijo
====================================
*/

#define NOMARCH_ESTUDIANTES_FIJO "estudiantes(formato fijo).txt"
#define ESTRUC_EST_FIJO_ESCRITURA "%4d%23s%7.2f\n"
#define ESTRUC_EST_FIJO_LECTURA "%4d%23[^\n]%7f\n"

// Escritura
int crearEstudiantesFijo(const char* nomArch)
{
    ESTS est[] =
    {
        {10,"Eva Peron",28.2},
        {20,"Maria",22.5},
        {30,"Juan",134.67} // Flotante al Limite
    };
    size_t i;

    FILE* arch = fopen(nomArch,"wt");

    if(!arch)
        return 0;

    for(i = 0 ; i < sizeof(est)/sizeof(*est); i++)
        fprintf(arch, ESTRUC_EST_FIJO_ESCRITURA, est[i].leg, est[i].nombre ,est[i].prom);

    fclose(arch);
    return 1;
}

int lecturaEstudiantesFijo(const char* nomArch)
{
    FILE* arch = fopen(nomArch,"rt");
    ESTS est;
    char linea[MAXLINE];

    if(!arch)
        return 0;

    // Manera Automatica
    printf("Manera Automatica:\n");
    while(fgets(linea,MAXLINE,arch))
    {
        sscanf(linea, ESTRUC_EST_FIJO_LECTURA, &est.leg, est.nombre, &est.prom);
        printf("%d %s %.2f\n",est.leg,est.nombre,est.prom);
    }
    rewind(arch);

    printf("\nFuncion fscanf:\n");
    while(fscanf(arch, ESTRUC_EST_FIJO_LECTURA, &est.leg, est.nombre, &est.prom) != EOF)
        printf("%d %s %.2f\n",est.leg,est.nombre,est.prom);
    rewind(arch);

    fclose(arch);
    return 1;
}

/*
====================================
MAIN
====================================
*/
int main()
{
    // Texto No Estructurado
    system("cls");
    crearPalindromos(NOMARCH_POLINDROMO);
    lecturaPalindromos(NOMARCH_POLINDROMO);
    system("pause");

    // Texto Estructurado Variable
    system("cls");
    crearEstudiantesVariable(NOMARCH_ESTUDIANTES_VARIABLE);
    lecturaEstudiantesVariable(NOMARCH_ESTUDIANTES_VARIABLE);
    system("pause");

    // Texto Estructurado Fijo
    system("cls");
    crearEstudiantesFijo(NOMARCH_ESTUDIANTES_FIJO);
    lecturaEstudiantesFijo(NOMARCH_ESTUDIANTES_FIJO);

    puts("fin");
    return 0;
}