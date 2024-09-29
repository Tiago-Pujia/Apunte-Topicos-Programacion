#include <stdio.h>
#include <stdlib.h>

void mostrarEntero(void *elemento)
{
    int *elementoTransformado = (int*)(elemento);
    printf("%d",*elementoTransformado);
}

void mostrarChar(void *elemento)
{
    char *elementoTransformado = (char*)(elemento);
    printf("%c",*elementoTransformado);
}

void* mostrarVector(void *vec, unsigned int longitud, unsigned int tamanio, void mostrar(void*))
{
    void *fin = vec + longitud * tamanio;

    while(vec < fin)
    {
        mostrar(vec);
        printf(" ");
        vec += tamanio;
    }

    puts("");
}

unsigned short int longitudCadena(char *cadena)
{
    char *ini = cadena;
    while(*cadena) cadena++;
    return (unsigned short int)(cadena - ini);
}

int main1()
{
    int vec[] = {0,1,2,3};
    size_t  tamanio = sizeof(*vec),
            longitud = sizeof(vec) / tamanio;

    mostrarVector(vec,longitud,tamanio,mostrarEntero);

    return 0;
}

int main()
{
    char origen[20] = "Hola, Mundo!";
    char destino[20];
    unsigned int tamanio = sizeof(char), longitud = longitudCadena(origen) + 1;

    memcpy(destino, origen, longitud);  

    system("cls");
    printf("%s\n",origen);
    printf("%s",destino);
}