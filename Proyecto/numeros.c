#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Configurar la semilla para los números aleatorios
    srand((unsigned int)time(NULL));

    // Definir la cantidad de números aleatorios a generar
    long long int num_elements = 20000000;

    // Abrir el archivo para escribir
    FILE *file = fopen("numeros_aleatorios.txt", "w");
    
    // Verificar si el archivo se abrió correctamente
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Generar y escribir los números aleatorios en el archivo
    for (long long int i = 0; i < num_elements; i++) {
        fprintf(file, "%d\n", rand());
    }

    // Cerrar el archivo
    fclose(file);

    printf("Se generaron y guardaron %lld números aleatorios en 'numeros_aleatorios.txt'.\n", num_elements);

    return 0;
}
