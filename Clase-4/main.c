#include <stdio.h>
#include <stdlib.h>

#define TAM 50

char strcpy(char *destino, char *origen)
{
    char *ini = destino; // Debemos retornar la direccion inicial de destino

    // Copia cada carácter de 'origen' a 'destino' mientras no sea el caracter nulo
    while(*origen)
    {
        *destino = *origen; // Asigna el caracter actual de 'origen' a 'destino'
        destino++;          // Avanza el puntero 'destino'
        origen++;           // Avanza el puntero 'origen'
    }
    *destino = '\0'; // Añade el carácter nulo al final de la cadena copiada

    return ini;
}

char strncpy(char *destino, char *origen, size_t bytes)
{
    char *ini = destino; // Debemos retornar la direccion inicial de destino

    // Copia cada carácter de 'origen' a 'destino' mientras no sea el caracter nulo
    while(*origen && bytes)
    {
        *destino = *origen; // Asigna el caracter actual de 'origen' a 'destino'
        destino++;          // Avanza el puntero 'destino'
        origen++;           // Avanza el puntero 'origen'
        bytes--;            // Decrementa  el contador de bytes a copiar
    }
    *destino = '\0'; // Añade el carácter nulo al final de la cadena copiada

    return ini;
}

char* strcat(char *destino, char *origen)
{
    char *ini = destino;
    while(*destino)
        destino++;
    
    while(*origen)
    {
        *destino = *origen;
        destino++;
        origen++;
    }

    *destino = '\0';
    return ini;
}

char strcmp(const char *str1,const char *str2)
{
    while(*str1 == *str2 && *str1 && *str2)
    {
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

int strlen(char* str)
{
    const char* ini = str;
    while(*str)
        str++;
    return str-ini;
}

int strchr(char *str, const char buscar)
{
    const char *ini = str;
    while (*str) {
        if (*str == buscar)
            return str-ini;
        str++;
    }
    return -1;
}

#define STRINGIFY(x) #x

int main()
{
    printf("%s",STRINGIFY(123.2));

    return 0;
}