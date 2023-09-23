// Solución secuencial: método 2

#include <stdio.h>
#define MAX 1000

// Crear un array para la memoización
int f[MAX] = {0};

// Retorna el n-ésimo número de Fibonacci usando la tabla f[]
int fib(int n)
{
    // Casos base
    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return (f[n] = 1);

    // Si fib(n) ya ha sido calculado
    if (f[n])
        return f[n];

    int k = (n & 1) ? (n + 1) / 2 : n / 2;

    // Aplicando la fórmula anterior [Nota: el valor de n&1 es 1 si n es impar, de lo contrario es 0].
    f[n] = (n & 1) ? (fib(k) * fib(k) + fib(k - 1) * fib(k - 1))
                   : (2 * fib(k - 1) + fib(k)) * fib(k);

    return f[n];
}

// Calcula el valor de la suma de los números de Fibonacci con índices pares
int calculateEvenSum(int n)
{
    return (fib(2 * n + 1) - 1);
}

// Programa principal para probar la función anterior
int main()
{
    // Obtener n del usuario
    int n;
    printf("Introduce un número: ");
    scanf("%d", &n);

    // La función calculateEvenSum(n) se calcula y retorna la suma de los números de Fibonacci con índices pares.
    int sum = calculateEvenSum(n);

    // Mostrar resultado
    printf("La suma de los números de Fibonacci con índices pares hasta %d términos es %d\n", n, sum);

    return 0;
}
