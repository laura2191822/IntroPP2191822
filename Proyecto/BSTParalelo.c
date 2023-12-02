#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* insert(struct Node* root, int data) {
    // Inserta un nuevo nodo en el árbol BST
    if (root == NULL) {
        struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = data;
        temp->left = temp->right = NULL;
        return temp;
    }

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

struct Node* insertBatch(struct Node* root, int* data, int start, int end) {
    // Inserta un lote de elementos en el árbol BST
    for (int i = start; i < end; i++) {
        root = insert(root, data[i]);
    }
    return root;
}

void inOrder(struct Node* root, FILE* output_file) {
    // Realiza un recorrido inorden del árbol BST y escribe los datos en un archivo de salida
    if (root != NULL) {
        inOrder(root->left, output_file);
        fprintf(output_file, "%d ", root->data);
        inOrder(root->right, output_file);
    }
}

int main() {
    struct Node* root = NULL;

    // Contar el número de elementos en el archivo
    FILE *file = fopen("numeros_aleatorios.txt", "r");
    int num_elements = 0;
    int temp;
    while (fscanf(file, "%d", &temp) != EOF) {
        num_elements++;
    }
    fclose(file);

    // Lectura de datos desde el archivo
    file = fopen("numeros_aleatorios.txt", "r");
    int* data = (int*)malloc(num_elements * sizeof(int));

    for (int i = 0; i < num_elements; i++) {
        fscanf(file, "%d", &data[i]);
    }

    fclose(file);

    // Medir el tiempo de construcción del BST en paralelo utilizando OpenMP
    double start_time = omp_get_wtime();

    // Construir el BST en paralelo utilizando OpenMP
    #pragma omp parallel
    {
        #pragma omp single
        root = insertBatch(root, data, 0, num_elements);
    }

    double end_time = omp_get_wtime();

    // Imprimir el tiempo de construcción
    printf("Tiempo de construcción del BST: %f segundos\n", end_time - start_time);

    // Almacenar los resultados en un nuevo archivo de texto
    FILE* output_file = fopen("salidaParalelo.txt", "w");
    inOrder(root, output_file);
    fclose(output_file);

    // Liberar memoria
    free(data);

    return 0;
}