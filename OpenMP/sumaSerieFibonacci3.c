#include <stdio.h>

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

// Función para calcular la suma de los números de Fibonacci en índices pares hasta n
int calculateEvenSum(int n)
{
    // La suma de los primeros n números de Fibonacci en índices pares es igual al (2n + 1)-ésimo número de Fibonacci menos 1
    return (fibo(2 * n + 1) - 1);
}

// Programa principal
int main()
{
    long n;
    // Solicitar al usuario que introduzca un número
    printf("Ingresar un número: ");
    scanf("%ld", &n);

    // Calcular la suma de los números de Fibonacci en índices pares hasta n
    int sum = calculateEvenSum(n);

    // Imprimir el resultado
    printf("La suma de los números de Fibonacci con índices pares hasta %zu términos es %d\n", n, sum);
    
    return 0;
}
