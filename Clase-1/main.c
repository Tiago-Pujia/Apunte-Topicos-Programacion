#include <stdio.h>
#include <stdlib.h>
#include "libs/matematica.h"

int main()
{
    signed char valor = 5;
    printf("Factorial de %d = %llu\n", valor, factorial(valor));
    return 0;
}