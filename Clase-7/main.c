#include <stdio.h>
#include <stdlib.h>

// FUNCION GLOBAL
int comparacionInt(const void *el1, const void *el2)
{
    int *elInt1 = (int*)el1;
    int *elInt2 = (int*)el2;

    return *elInt1 - *elInt2;
}

// FUNCION BUSQUEDA BINARIA
void* busquedaBinaria(void* buscar, void* vec, size_t longitud, size_t tamanio, int comparacion(const void*, const void*)) {
    // Inicializa los punteros de inicio y fin que delimitan el rango de búsqueda
    void *mitad;                               // Puntero a la posición central actual
    void *inicio = vec;                        // Puntero al primer elemento del array
    void *fin = vec + (longitud - 1) * tamanio; // Puntero al último elemento del array
    
    int resultadoComparacion;  // Variable para almacenar el resultado de la comparación
    
    // El bucle continúa mientras el puntero de inicio no supere al puntero de fin
    while (inicio <= fin) {
        // Calcula la dirección de la mitad del rango actual utilizando aritmética de punteros
        mitad = inicio + ((fin - inicio) / (2 * tamanio)) * tamanio;
        
        // Compara el valor buscado con el valor en la posición de mitad
        resultadoComparacion = comparacion(buscar, mitad);
        
        // Si la comparación da cero, significa que hemos encontrado el valor
        if (resultadoComparacion == 0)
            return mitad;  // Devuelve el puntero al valor encontrado

        // Si el valor buscado es menor que el valor en la posición de mitad
        else if (resultadoComparacion < 0)
            fin = mitad - tamanio;  // Ajusta el puntero de fin para reducir la búsqueda a la mitad inferior

        // Si el valor buscado es mayor que el valor en la posición de mitad
        else
            inicio = mitad + tamanio;  // Ajusta el puntero de inicio para reducir la búsqueda a la mitad superior
    }
    
    // Si el bucle termina sin encontrar el valor, se retorna NULL
    return NULL;
}

// FUNCION ORDENAMIENTO POR SELECCION
void intercambiarElementos(void *elementoA, void *elementoB, size_t tamanio)
{
    char aux;
    size_t i;
    for (i = 0; i < tamanio; i++)
    {
        aux = *(char*)elementoB;
        *(char*)elementoB = *(char*)elementoA;
        *(char*)elementoA = aux;
        elementoA++;
        elementoB++;
    }
}

// Función que busca el menor elemento en el vector a partir de una posición dada
void* buscarElementoMenor(void *vec, size_t longitud, size_t tamanio, int comparacion(const void*, const void*))
{
    size_t i;
    void *elementoMenor = vec; // Puntero al menor elemento encontrado
    vec += tamanio; // Puntero al elemento actual

    // Itera por cada elemento del vector comparando cuál es menor
    for (i = 1; i < longitud; i++)
    {
        if (comparacion(vec, elementoMenor) < 0)
            elementoMenor = vec;
        vec += tamanio; // Avanza al siguiente elemento
    }

    return elementoMenor; // Retorna la dirección del menor elemento
}

// Función que ordena un vector usando el método de selección con lógica genérica
void ordenarSeleccion(void *vec, size_t longitud, size_t tamanio, int comparacion(const void*, const void*))
{
    size_t i;
    void *elementoMenor;

    // Itera por cada elemento del vector para buscar su posición correcta
    for (i = 0; i < longitud; i++)
    {
        // Busca el menor elemento a partir de la posición actual
        elementoMenor = buscarElementoMenor(vec, longitud - i, tamanio, comparacion);
        
        // Si el menor elemento no está en la posición actual, intercambia
        if (elementoMenor != vec)
            intercambiarElementos(elementoMenor, vec, tamanio);
        
        // Avanza al siguiente elemento
        vec += tamanio; 
    }
}


int main()
{
    int bus[] = {12,4,9,1,11,15,6,18,3};
    int vec[] = {3,5,9,12,15};

    ordenarSeleccion(vec,sizeof(vec)/sizeof(*vec),sizeof(*vec),comparacionInt);
    ordenarSeleccion(bus,sizeof(bus)/sizeof(*bus),sizeof(*bus),comparacionInt);

    printf("\nArray Vec:\n-----------------\n");
    for(int i = 0; i < sizeof(vec)/sizeof(*vec); i++)
        printf("%d. %d\n",i,*(vec+i));
    
    printf("\nArray Bus:\n-----------------\n");
    for(int i = 0; i < sizeof(bus)/sizeof(*bus); i++)
        printf("%d. %d\n",i,*(bus+i));

    printf("\nBusqueda Binaria:\n-----------------\n");
    for(int i = 0; i < sizeof(bus)/sizeof(*bus); i++)
        printf("~ Posicion en Memoria: %u\n",busquedaBinaria(bus+i,vec,sizeof(vec)/sizeof(*vec),sizeof(*vec),comparacionInt));
    
    return 0;
}
