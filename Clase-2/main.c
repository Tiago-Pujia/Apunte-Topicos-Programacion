#include <stdio.h>
#include <stdlib.h>

#define TAM 100

void mostrarVector(int *vec, unsigned short int tamanio)
{
    unsigned int i;

    printf("[");
    for (i = 0; i < tamanio; i++)
    {
        i < tamanio - 1
            ? printf("%d, ", *(vec + i))
            : printf("%d", *(vec + i));
    }
    printf("]\n");
}

void insertarOrdenadoVector(int *vec, unsigned short int tamanio, int *ce, int ingreso)
{
    unsigned short int i = *ce;

    if (*ce >= tamanio)
        return 0;

    while (i > 0 && *(vec + i - 1) > ingreso)
    {
        *(vec + i) = *(vec + i - 1);
        i--;
    }

    *(vec + i) = ingreso;
    (*ce)++;
}

int main()
{
    int vec1[TAM] = {8, 9, 1, 5, 6, 7}, vec2[] = {}, i, ce1 = 6, ce2 = 0;

    for (i = 0; i < ce1; i++)
        insertarOrdenadoVector(vec2, TAM, &ce2, *(vec1 + i));

    mostrarVector(vec2, ce2);

    return 0;
}