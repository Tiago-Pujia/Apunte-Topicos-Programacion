#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define MAXNOM 24
#define IMPRIMIR "%d|%s|%.2f\n"

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
int trozarEstVar(ESTS* est, char *linea)
{
    char *dirSeparador;

    // Eliminar salto de linea
    dirSeparador = strrchr(linea,'\n');
    *dirSeparador = '\0';

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

    while(fgets(linea,MAXLINE,arch) && lecEstVar(&est,linea))
        printf(IMPRIMIR,est.leg,est.nombre,est.prom);

    fclose(arch);
    return 1;
}

/*
====================================
Texto Estructurado Fijo
====================================
*/
// NOMBRE ARCHIVO
#define NOMARCH_ESTUDIANTES_FIJO "estudiantes(formato fijo).txt"

// Longitudes
#define TAM_LEG 4
#define TAM_NOM 23
#define TAM_PRO 7
// total = 4 + 23 + 7 = 34

// FORMATO
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

int trozarEstFijo(ESTS* est, char *linea)
{
    char *dirCampo = linea + TAM_LEG + TAM_NOM + TAM_PRO;
    // char *dirCampo = linea + 34

    // Eliminamos salto de linea
    *dirCampo = '\0';

    // Lectura Promedio
    dirCampo -= TAM_PRO; // 7
    sscanf(dirCampo,"%f",&est->prom);
    *dirCampo = '\0';

    // Lectura Nombre
    dirCampo -= TAM_NOM; // 23
    sscanf(dirCampo,"%[^\n]",est->nombre);
    *dirCampo = '\0';

    // Lectura Legajo
    sscanf(linea,"%d",&est->leg);

    return 1;
}

int lecEstsFijo(const char* nomArch)
{
    FILE* arch = fopen(nomArch,"rt");
    ESTS est;
    char linea[MAXLINE];

    if(!arch)
        return 0;

    while(fgets(linea, MAXLINE, arch) && trozarEstFijo(&est, linea))
        printf("%d - %s - %.2f",est.leg,est.nombre,est.prom);

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
   system("cls");
   puts(ESTRUC_EST_FIJO_ESCRITURA);

    return 0;
}