unsigned long long int factorial(signed char valor)
{
    signed char i;
    unsigned long long int acumulador = 1;

    for (i = valor; i > 0; i--)
        acumulador *= i;

    return acumulador;
}