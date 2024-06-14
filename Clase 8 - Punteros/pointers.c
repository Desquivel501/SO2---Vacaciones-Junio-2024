#include <stdio.h>
#include <stdlib.h>

int size = 3;

void increment(int *p)
{
    (*p)++; // acceder o modificar el valor almacenado en esa ubicación eliminando la referencia al puntero
}

// Realojar la memoria de manera dinamica
void push(int *arr, int value)
{   
    // realloc cambia el tamaño de un bloque de almacenamiento reservado anteriormente. 
    // El argumento ptr apunta al principio del bloque a reasignar. 
    // El argumento tamaño proporciona el nuevo tamaño del bloque, en bytes. 
    // El contenido del bloque no se modifica, si hay espacio disponible lo incrementa donde esta, si no mueve todo el bloque a otra direccion
    // realloc regresara el puntero de donde se encuentra el bloque de memoria reasignado
    int *arr2 = (int *)realloc(arr, (size + 1) * sizeof(int));
    if (arr2 != NULL)
    {
        arr = arr2;
        *(arr + size) = value;
        size++;
    }
    else
    {
        printf("Error: No se pudo re-asignar memoria\n");
    }
}

int main()
{
    int x = 42;
    int *p = &x; // inicializa un puntero  que apunte a una variable o ubicación de memoria específica

    printf("%d\n", x);
    printf("%p\n", p);
    
    *p = 12;
    printf("%d\n", x);
    printf("%p\n", p);

    // ERROR
    // p = 12;
    // printf("%d\n", *p);
    // printf("%p\n", p);

    printf("x = %d\n", x); // prints x = 12
    increment(p);
    printf("x = %d\n", x); // prints x = 13

    printf("Address: %p\n", p);
    printf("\n");

    int *arr = (int *)malloc(3 * sizeof(int)); // void *
    // Definimos el puntero arr que apunta a un bloque de memoria de 3 enteros
    // malloc devuelve un puntero a la dirección de memoria asignada
    // (int *) es un casting que convierte el puntero genérico (void *) a un puntero de tipo entero

    // int *arr = (int *)calloc(size, sizeof(int)); // void *
    // calloc define n un bloques de memoria contiguos de tamaño size
    // y devuelve un puntero a la dirección de memoria asignada

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    int *q = arr;

    printf("arr[0] = %d\nq = %p\n\n", *q, q); // prints arr[0] = 1
    q++;
    printf("arr[1] = %d\nq = %p\n\n", *q, q); // prints arr[1] = 2
    q++;
    printf("arr[2] = %d\nq = %p\n\n", *q, q); // prints arr[2] = 3

    push(arr, 4);

    int *p = arr;
    for (int i = 0; i < size; i++)
    {
        printf("arr[%d] = %d - p = %p\n", i, *p, p);
        p++;
    }

    printf("arr[3] = %d\nq = %p\n\n", *q, q);

    //a[i] = ∗(a+i)
    //i[a] = *(i+a)
    printf("%d = %d = %d\n", arr[3], 3[arr], *(arr + 3));

    free(arr);

    return 0;
}