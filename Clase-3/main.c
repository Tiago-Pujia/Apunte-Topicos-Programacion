#include <stdio.h>
#include <stdlib.h>

#define TAM 5

void mostrarMatriz(char matriz[][TAM], int tamanio) {
    int i, j;
    for (i = 0; i < tamanio; i++) {
        printf("\n");
        for (j = 0; j < tamanio; j++) {
            printf("%c ", *(*(matriz+i)+j));
        }
    }
}

void recorridoEspiralAdentro(char matriz[][TAM], int filas, int columnas) {
    int centroFila = filas / 2;
    int centroColumna = columnas / 2;
    
    // Coordenadas actuales
    int x = centroFila;
    int y = centroColumna;
    
    // Movimientos en espiral
    int movimientos[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; // Derecha, Abajo, Izquierda, Arriba
    int pasos = 1; // Número de pasos a tomar en cada dirección
    int direccion = 0; // Índice para movimientos
    
    printf("\n%c ", matriz[x][y]); // Imprime el centro
    
    while (pasos <= filas || pasos <= columnas) {
        // Dos veces (cada vez que se aumenta pasos)
        for (int i = 0; i < 2; i++) {
            // Recorre en la dirección actual
            for (int j = 0; j < pasos; j++) {
                x += movimientos[direccion][0];
                y += movimientos[direccion][1];
                
                // Verifica si aún está dentro de los límites de la matriz
                if (x >= 0 && x < filas && y >= 0 && y < columnas) {
                    printf("%c ", matriz[x][y]);
                }
            }
            // Cambia de dirección (derecha -> abajo -> izquierda -> arriba)
            direccion = (direccion + 1) % 4;
        }
        pasos++; // Incrementa el número de pasos a tomar en la siguiente vuelta
    }
}

void recorridoEspiralAfuera(char matriz[][TAM], int filas, int columnas) {
    int izquierda = 0, derecha = columnas - 1;
    int arriba = 0, abajo = filas - 1;
    putchar('\n');
    while (izquierda <= derecha && arriba <= abajo) {
        // Recorrer de izquierda a derecha en la fila superior
        for (int i = izquierda; i <= derecha; i++) {
            printf("%c ", matriz[arriba][i]);
        }
        arriba++;

        // Recorrer de arriba a abajo en la columna derecha
        for (int i = arriba; i <= abajo; i++) {
            printf("%c ", matriz[i][derecha]);
        }
        derecha--;

        // Verificar que todavía estamos dentro de los límites
        if (arriba <= abajo) {
            // Recorrer de derecha a izquierda en la fila inferior
            for (int i = derecha; i >= izquierda; i--) {
                printf("%c ", matriz[abajo][i]);
            }
            abajo--;
        }

        // Verificar que todavía estamos dentro de los límites
        if (izquierda <= derecha) {
            // Recorrer de abajo hacia arriba en la columna izquierda
            for (int i = abajo; i >= arriba; i--) {
                printf("%c ", matriz[i][izquierda]);
            }
            izquierda++;
        }
    }
}

int main()
{
    char matriz[TAM][TAM];
    int k = 65;

    for(int i = 0; i < TAM; i++)
        for(int j= 0; j < TAM; j++)
            *(*(matriz+i)+j) = k++;
    
    system("cls");
    mostrarMatriz(matriz,TAM);

    recorridoEspiralAdentro(matriz,5, 5);
    //recorridoEspiralAfuera(matriz,5, 5);
    //transponerMatriz(matriz,3);
    //mostrarMatriz(matriz,3);
    return 0;
}