// Método 1

// Incluye la biblioteca estándar de entrada y salida
#include <stdio.h>

// Función para calcular la suma de los números de Fibonacci en índices pares
int calculateEvenSum(int n)
{
    // Si n es menor o igual a cero, retorna 0
    if (n <= 0)
        return 0;

    // Crea un array para almacenar los números de Fibonacci
    int fibo[2 * n + 1];
    fibo[0] = 0, fibo[1] = 1;

    // Inicializa la suma en 0
    int sum = 0;

    // Calcula los números de Fibonacci y suma los que están en índices pares
    for (int i = 2; i <= 2 * n; i++) {
        fibo[i] = fibo[i - 1] + fibo[i - 2];

        // Si el índice es par, suma el número de Fibonacci a la suma total
        if (i % 2 == 0)
            sum += fibo[i];
    }

    // Retorna la suma total
    return sum;
}

// Función principal del programa
int main()
{
    // Declara la variable n
    int n;
    
    // Pide al usuario que ingrese el valor de n
    printf("Ingrese el valor de n: ");
    scanf("%d", &n);

    // Calcula e imprime la suma de los números de Fibonacci en índices pares hasta n
    printf("La suma de Fibonacci con índices pares hasta %d términos es: %d\n", n, calculateEvenSum(n));

    // Termina el programa
    return 0;
}
