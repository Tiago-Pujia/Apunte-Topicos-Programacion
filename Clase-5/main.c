#include <stdio.h>
#include <stdlib.h>

int main(){
    int *pi; // Creamos nuestra variable tipo puntero
    pi = malloc(sizeof(int)); // Apuntamos hacia una dirección de memoria dinamica

    if(pi) // Chequear que retorno una dirección de memoria
    {
        *pi = 7;
        // ... Hacemos lo que queramos con ella
        printf("Valor asignado %d en la direccion %p",*pi,pi);
    } 
    
    free(pi); // Liberamos la memoria

    return 0;
}