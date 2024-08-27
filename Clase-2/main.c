#include <stdio.h>
#include <stdlib.h>

#define TAM 5

void mostrarVectorEntero(int *vec, unsigned int tamanio)
{
    unsigned int i;

    for (i = 0; i < tamanio; i++)
    {
        // printf("%d\n",*vec);
        // vec++;

        printf("%d\n", *(vec + i));
    }
}

void insetarVectorOrdenado(int *vec, unsigned int tamanio, int ingreso)
{
    int *ini = vec;
    vec += tamanio;

    while ((vec > ini) && (*(vec - 1) > ingreso || *(vec - 1) == 0))
    {
        *vec = *(vec - 1);
        vec--;
    }
    *vec = ingreso;
}

int main()
{
    int vec[TAM] = {}, vecInse[] = {3, 9, 7, 1, 16, 5, 4, 8}, i, ce = 0;

    for (i = 0; i < sizeof(vecInse) / sizeof(*vecInse); i++)
        insetarVectorOrdenado(vec, TAM, vecInse[i]);

    mostrarVectorEntero(vec, TAM);

    return 0;
}