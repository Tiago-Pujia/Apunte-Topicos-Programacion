#include <stdio.h>
#include <stdlib.h>

// FUNCION GLOBAL
int comparacionInt(void *el1, void *el2)
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
void intercambioElementos(void *el1, void *el2, size_t bytes)
{
    // Definimos los punteros char para recorrer byte por byte los elementos
    char *elChar1 = (char*)el1, *elChar2 = (char*)el2;
    char aux;  // Variable auxiliar para almacenar temporalmente el valor de un byte

    // Mientras queden bytes por intercambiar
    while (bytes)
    {
        
        aux = *elChar1;      // Guardamos el valor del byte actual de elChar1 en aux
        *elChar1 = *elChar2; // Copiamos el valor de elChar2 a elChar1
        *elChar2 = aux;      // Colocamos el valor guardado en aux en elChar2

        elChar1++; // Avanzamos ambos punteros al siguiente byte
        elChar2++; 
        bytes--;   // Reducimos la cantidad de bytes restantes
    }
}

// Función que busca el menor elemento en el vector a partir de una posición dada
void* buscarMenor(void *vec, size_t longitud, size_t tamanio, int cmp(void*, void*))
{
    void *fin = vec + (longitud - 1) * tamanio, // Calcular la dirección final del vec
         *pos = vec; // Apunta al elemento actual o primero, donde se guarda el menor

    while(vec < fin) // Itera cada elemento del vector comparando cuál es menor
    {
        vec += tamanio; // Avanza al siguiente elemento del vector (razon por la resta 1)
        if(cmp(vec, pos) < 0) // Si el elemento actual es menor, actaliza pos
            pos = vec;
    }

    return pos; // Retorna la dirección del menor elemento
}

// Función que ordena un vector usando el método de selección con lógica genérica
void ordenarSeleccion(void *vec, size_t longitud, size_t tamanio, int cmp(void*, void*))
{
    void *vecFin = vec + tamanio * (longitud - 1), *posMenor;

    while (vec < vecFin)
    {
        posMenor = buscarMenor(vec, longitud, tamanio, cmp);

        if (posMenor != vec)
            intercambio(vec, posMenor, tamanio);

        vec += tamanio;
        longitud--;
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
