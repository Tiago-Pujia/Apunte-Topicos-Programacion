# Introducción

## Indice

> - [Clase 1 - Buenas Practicas, Crear Libreria, Tipo de Datos y Punteros](#clase-1)
> - [Clase 2 - ](#clase-2)
> - [Clase 3 - ](#clase-3)
> - [Clase 4 - ](#clase-4)
> - [Clase 5 - ](#clase-5)

## Profesores

- Pablo Soligo
- Dario Hirschfeldt

## Parciales

- 1 Parcial
- 1 TP Grupal. Defensa oral (20 minutos) y 3-5 personas
- 1 Recuperatorio

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

## Clase 2