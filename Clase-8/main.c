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

int lecPalindromos(const char* nomArch)
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
int crearEstsVar(const char* nomArch)
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
int lecEstVar(ESTS* est, char *linea)
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

int lecEstsVar(const char* nomArch)
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
    while(fgets(linea,MAXLINE,arch) && lecEstVar(&est,linea))
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
int crearEstsFijo(const char* nomArch)
{
    ESTS est[] =
    {
        {10,"Tiago Pujia",28.2},
        {20,"Vladimir Francisco",22.5},
        {30,"Pablo Soligo",134.67} // Flotante al Limite
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

int lecEstFijo(ESTS* est, char *linea)
{
    char *dirCampo = linea + sizeof(ESTS);

    // Lectura Promedio
    dirCampo -= sizeof(est->prom);
    sscanf(dirCampo,"%f",&(est->prom));
    *dirCampo = '\0';

    // Lectura Nombre
    dirCampo -= sizeof(est->nombre);
    sscanf(dirCampo,"%[^\n]",est->nombre);
    *dirCampo = '\0';

    // Lectura Legajo
    sscanf(linea,"%d",&(est->leg));

    return 1;
}

int lecEstsFijo(const char* nomArch)
{
    FILE* arch = fopen(nomArch,"rt");
    ESTS est;
    char linea[MAXLINE];

    if(!arch)
        return 0;
    
    // Funcion fscanf
    printf("\nFuncion fscanf:\n");
    while(fscanf(arch, ESTRUC_EST_FIJO_LECTURA, &est.leg, est.nombre, &est.prom) != EOF)
        printf("%d %s %.2f\n",est.leg,est.nombre,est.prom);
    rewind(arch);

    // Manera Automatica
    printf("\nManera Automatica:\n");
    while(fgets(linea,MAXLINE,arch))
    {
        sscanf(linea, ESTRUC_EST_FIJO_LECTURA, &est.leg, est.nombre, &est.prom);
        printf("%d %s %.2f\n",est.leg,est.nombre,est.prom);
    }
    rewind(arch);

    // Manera Manual
    printf("\nManera Manual:\n");
    while(fgets(linea, MAXLINE,arch) && lecEstFijo(&est,linea))
        printf("%d %s %.2f\n",est.leg,est.nombre,est.prom);

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
    crearPalindromos(NOMARCH_POLINDROMO)
        ? lecPalindromos(NOMARCH_POLINDROMO)
        : printf("Error al escribir en %s",NOMARCH_POLINDROMO);
    system("pause");

    // Texto Estructurado Variable
    system("cls");
    crearEstsVar(NOMARCH_ESTUDIANTES_VARIABLE)
        ? lecEstsVar(NOMARCH_ESTUDIANTES_VARIABLE)
        : printf("Error al escribir en %s",NOMARCH_ESTUDIANTES_VARIABLE);
    system("pause");

    // Texto Estructurado Fijo
    system("cls");
    crearEstsFijo(NOMARCH_ESTUDIANTES_FIJO)
        ? lecEstsFijo(NOMARCH_ESTUDIANTES_FIJO)
        : printf("Error al escribir en %s",NOMARCH_ESTUDIANTES_FIJO);
    puts("fin");

    return 0;
}