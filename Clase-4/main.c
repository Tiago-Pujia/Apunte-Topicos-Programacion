#include <stdio.h>
#include <stdlib.h>

#define TAM 50

void strcpy(char *destino, char *origen)
{
    while(*origen)
    {
        *destino = *origen;

        destino++;
        origen++;
    }
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

signed char strcmp(const char *str1,const char *str2)
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

int main()
{
    char string1[] = "Hola",
         string2[] = "Hola MunDo";

    system("cls");
    //strcpy(string1,string2);
    printf("%d",strchr(string2,'D'));

    return 0;
}