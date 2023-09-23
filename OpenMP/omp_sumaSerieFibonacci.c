// Solución paralela 

#include <stdio.h>
#include "omp.h"

// Función para calcular el n-ésimo número de Fibonacci
long fibo(long n)
{
    // Los primeros dos números de Fibonacci son 1
    if (n == 1 || n == 2)
    {
        return 1;
    }
    // Para n > 2, el n-ésimo número de Fibonacci es la suma de los dos números anteriores
    else
    {
        return fibo(n - 1) + fibo(n - 2);
    }
}

// Programa principal
int main()
{
    // Establecer el número de hilos que OpenMP debe usar
    int nHilos = 5;
    omp_set_num_threads(nHilos);

    long respuesta = 0, n;

    // Solicitar al usuario que introduzca un número
    printf("Ingresar un número: ");
    scanf("%ld", &n);

    // Bloque de código paralelo en OpenMP
#pragma omp parallel sections
    {
        // Sección que se ejecutará en un hilo separado
    #pragma omp section
        {
            // Calcular el (2n + 1 - 2)-ésimo número de Fibonacci y sumarlo a la respuesta
            long subrespuesta = fibo((2 * n + 1) - 2);
            printf("El hilo %d descubrio que Fibonacci(%ld) = %ld\n", omp_get_thread_num(), n - 2, subrespuesta);
    #pragma omp atomic
            respuesta += subrespuesta;
        }
        // Otra sección que se ejecutará en un hilo separado
    #pragma omp section
        {
            // Calcular el (2n + 1 - 1)-ésimo número de Fibonacci y sumarlo a la respuesta
            long subrespuesta = fibo((2 * n + 1) - 1);
            printf("El hilo %d descubrio que Fibonacci(%ld) = %ld\n", omp_get_thread_num(), n - 1, subrespuesta);
    #pragma omp atomic
            respuesta += subrespuesta;
        }
    }

    // Restar 1 a la respuesta para obtener la suma de los números de Fibonacci en índices pares hasta n
    respuesta = respuesta - 1; 

    // Imprimir el resultado
    printf("La suma de los números de Fibonacci con índices pares hasta %zu términos es %ld\n", n, respuesta);

    return 0;
}
