# Introducción

## Indice

> - [Clase 1 - Buenas Practicas, Crear Libreria, Tipo de Datos y Punteros](#clase-1)
> - [Clase 2 - Array Unidimencionales](#clase-2)
> - [Clase 3 - Matrices](#clase-3)

## Parciales

- 1 Parcial (laboratorio con CodeBlocks)
- 1 TP Grupal. Defensa oral (20 minutos) y 3-5 personas
- 1 Recuperatorio

## Información Extra

- **Profesores:** Pablo Soligo
- **Alumno:** Tiago Pujia
- **Comisión:** 2600 (martes tarde)
- **Fecha Inicio:** 13/08/2024
- **[Clases Grabadas](https://youtube.com/playlist?list=PLENvh_JZMnA6n-wdPgmxpLHa4OBW7Qxxo&si=8chccEFcD95x4y22)**
- **[Apunte(este mismo)](https://github.com/Tiago-Pujia/Apunte-Topicos-Programacion)**

---

# Clase 1

_Realizar Ejercicios hasta el 6_

## Buenas Practicas
- Separar todo por Funciones
- Hacer las funciones lo mas flexible posible para que sea utilizado por otros
- Separar por librerias
- Usar debugger
- Comentar Codigo

## Crear Librerias
Vamos a tener 2 archivos que son recomendados tenerlos en una carpeta llamada "libs":
- `nombre.c` - Incluimos las funciones que vamos agregar al proyecto
- `nombre.h` - Incluimos los prototipado y el include del archivo.c

Luego para incluirlo dentro del main hacemos uso de: `#include "libs/nombre.h"`

## Tipos de Datos
El tipo de archivo numero (int) se le puede hacer ciertas modificaciones para modificar la longitud de bits o si esta con signo. Las clausulas se colocan detras del int.


- **Numeros Signados**

El 1° bit indica el signo

|Tipo de Dato|Formato|Tamaño(bits)|Rango|
|---|---|---|---|
|signed char|%hhd|8|[-128 ; 127]|
|short int|%hd|16|[-32,768 ; 32,767]|
|int|%d|32|[-2,147,483,648 ; 2,147,483,647]|
|long long int|%lld|64|[-9,223,372,036,854,775,808 ; 9,223,372,036,854,775,807]|

- **Numeros sin Signar**

|Tipo de Dato|Formato|Tamaño(bits)|Rango|
|---|---|---|---|
|unsigned char|%hhu|8|[0 ; 255]|
|unsigned short int|%hu|16|[0 ; 65,536]|
|unsigned int|%u|32|[0 ; 4,294,967,295]|
|unsigned long long int|%llu|64|[0 ; 18,446,744,073,709,551,615]|

- **Numeros Flotantes**

|Tipo de Dato|Formato|Tamaño(bits)|Rango|
|---|---|---|---|
|float|%f o %e o %g|32|[±3.4×10^38 ; ±1.2×10^-38]|
|double|%f o %e o %g|64|[±1.7×10^308 ; ±2.2×10^-308]|
|long double|%Lf o %Le o %Lg|96 - 152||

Mientras mejor categoria, mas precision de valor flotante

## Punteros

### Definición

Un puntero es una variable que almacena una dirección de memoria de otra variable dentro de la computadora. Se utiliza para la manipulación de variables desde diferentes funciones.

La variable que almacenará la dirección debe ser de tipo int e incluir el signo "\*". Para obtener la dirección de una variable, utilizamos el operador "&". Además, podemos utilizar el operador "\*" delante de una variable que contiene una dirección para acceder al valor almacenado en esa dirección, cualquier operación implica el valor original. Ejemplo:
~~~
char nombre = 'T';
int *direccionNombre = &nombre;

printf("Direccion de Memoria: %u\n",direccionNombre);
printf("Valor de la dirección: %c\n", *direccionNombre)
~~~


### Ejemplo de Uso

El siguiente programa no permite modificar el contenido de la variable "valor" dentro de la función, realiza una copia:

~~~
void miFuncion(char valor)
{
    valor = 'U';
    printf("Valor: %c\n",valor);
}

int main()
{
    char valor = 'R';

    miFuncion(valor);
    printf("Valor: %c\n",valor);

    return 0;
}
~~~

~~~
Resultado:
Valor: U
Valor: R
~~~

Para poder realizar eso querido debemos:
~~~
void miFuncion(int *valor)
{
    *valor = 'U'; // Modificamos el valor original
    printf("Valor: %c\n",*valor);
}

int main()
{
    char valor = 'R';

    miFuncion(&valor); // Pasamos la dirección como argumento
    printf("Valor: %c\n",valor);

    return 0;
}
~~~
~~~
Resultado:
Valor: U
Valor: U
~~~

---

# Clase 2

## Array Unidimencionales

- **Administración del Espacio**

Al momento de crear un array de N elementos, se reservan en memoria N cantidad de espacios multiplicado por el tamaño del tipo de dato; N*sizeof(tipo dato). Ejemplo:
~~~
int vector[5];
~~~
El tipo int ocupa 4 bytes. Por lo tanto reservamos 5*4(bytes)=20 bytes.

- **Buenas Practicas**

Es buena practica definir el tamaño del array mediante constantes define. Ejemplo:
~~~
#define TAM 5

int vector[TAM];
~~~

- **Retornar Tamaño**

Podemos saber la cantidad de elementos que tiene un array que tiene con la siguiente formula:
~~~
sizeof(vector)/sizeof(int);
~~~
sizeof retorna tamaño, en este caso el tamaño del vector (5*4=20) y del tipo int(4 bytes). Por lo que ya no es necesario pasar a una función el tamaño del array.

-  **Aritmetica de Punteros**

Debemos hacer el uso aritemtica de punteros en cadenas y arrays, y evitar utilizar subindices Ejemplo:
~~~
void mostrarVectorEntero(int *vec, unsigned int tamanio)
{
    unsigned int i;

    for (i = 0; i < tamanio; i++)
    {
        // printf("%d\n",*vec);
        // vec++;
        // Es lo mismo utilizar el de arriba

        printf("%d\n", *(vec + i));
    }
}
~~~

---

# Clase 3

## Compresión del Proceso Interno de una Matriz

Para una mejor comprensión de cómo funcionan las matrices NxN utilizando punteros, es importante entender que cada matriz se almacena en memoria de manera continua. Los elementos de cada fila se colocan uno tras otro, formando una secuencia lineal.

![imagen](imgs/matrizFormaReal.png)

Esto quiere decir que para acceder a un elemento de un array de debe utilizar un doble puntero al estilo `*(*(matriz+F)+C)`, donde con F indicamos la fila y C la columna. Ejemplo:
~~~
int matriz[3][3] = {
    {00,01,02},
    {10,11,12},
    {20,21,22}
};
    
printf("%d",*(*(matriz+1)+2));
// Resultado: 12
~~~

Aunque no es obligatorio el uso de punteros para matrices, pero si para arrays y cadenas.

## Recorrido de Matrices

La optimización de la manera de recorrer las matrices es muy importante.

- **Recorrer Triangulo de Matriz**

![imagen](imgs/matrizTriangular.png)

~~~
int i, j;

// Recorrido de Matriz Triangular
for(i = 1 ; i < f ; i++)
    for(j = 0 ; j < i ; j++)
        printf("%d ",*(*(matriz+i)+j));

// Recorrido de Matriz Triangular + Diagonal Principal
for(i = 0 ; i < tamanio ; i++)
        for(j = 0 ; j <= i ; j++)
            printf("%d ",*(*(matriz+i)+j));
~~~

También podemos utilizar una técnica llamada _Matriz Espejada_, en la que podemos acceder a la casilla espejo de la posición en la que nos encontramos para diferentes usos. Solo necesitamos intercambiar "i" y "j" al recorrer la matriz de manera triangular.

![imagen](imgs/matrizEspejada.png)

~~~
for(i = 1 ; i < f ; i++)
    for(j = 0 ; j < i ; j++){
        printf("Valor: %d" , *(*(matriz+i)+j) );
        printf("Espejado: %d" , *(*(matriz+j)+i) );
    }
~~~

- **Saber si es Matriz Identidad**

La matriz identidad es aquella donde solo tiene 0 en todas las casillas y 1 en la diagonal principal.

![imagen](imgs/matrizIdentidad.png)

~~~
int i, j;
// Chequear Diagonal
for(i = 0 ; i < f ; i++)
    if(1 != *(*(matriz+i)+i))
        return 0;

// Chequear Triangulos con espejado
for(i = 1 ; i < f ; i++)
    for(j = 0 ; j < i ; j++)
        if(0 != *(*(matriz+i)+j) || 0 != *(*(matriz+j)+i))
            return 0;

return 1;
~~~

- **Transponer Matriz**

Transponer una matriz es el proceso de intercambiar filas por columnas. Esto significa que el elemento que está en la posición (i, j) pasa a la posición (j, i). Ejemplo:

![imagen](imgs/matrizTranspuesta.png)

La optimización para transponer una matriz cuadrada consiste en aprovechar el recorrido triangular, es decir, solo intercambiar los elementos que estan por fuera de la diagonal principal (ya que la diagonal principal permanece intacta). Hacemos uso del espejado de matriz junto una variable auxiliar al momento de realizar el intercambio.

~~~
void transponerMatriz(char matriz[][COL_MAX], int tamanio) {
    int i, j;
    char aux;

    // Recorre la matriz de manera triangular
    for(i = 1 ; i < tamanio ; i++)
    {
        for(j = 0 ; j < i ; j++)
        {
            // Intercambia los elementos de forma espejada con una variable auxiliar
            aux = *(*(matriz+i)+j);
            *(*(matriz+i)+j) = *(*(matriz+j)+i);
            *(*(matriz+j)+i) = aux;
        }
    }
}
~~~

- **Recorrido en Espiral** (desde afuera hacia adentro)

- **Recorrido en Espiral** (desde dentro hacia afuera)
 
Hacer uso de topes donde decidimos los limites dentro de la matriz (limite superior, inferior, izquierdo y derecho)

## Eliminar Constantes

Podemos eliminar la predefinicion de tamaños de matrices con constantes para hacerlo de uso en bibliotecas, globales para cualquier matriz. Ejemplo de error:

~~~
#define TAM_COL 4
#define TAM_FIL 4

void mostrarMatriz(int matriz[][TAM_COL],int f, c);
~~~

Una opción posible es poner una constante de tamaño maximo con un numero muy grande. Teniendo la desventaja que reservamos memoria que no se va a utilizar, pero es lo que se utiliza (por ahora).

~~~
#define MAX_COL 50
#define MAX_FIL 50

// Como una matriz identidad es siempre cuadrada, tan solo le pasamos un parametro
void es_identidad(int matriz[][MAX_COL],int tamanio);

int main()
{
    int resultado;
    int matriz[MAX_FIL][MAX_COL] = {
        {1,0,0},
        {0,1,0},
        {0,0,1}
    }

    resultado = es_identidad(matriz,3);
    printf("Identidad: %d",resultado);
}
~~~