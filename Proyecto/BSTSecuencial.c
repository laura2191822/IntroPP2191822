#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void inOrder(struct Node* root, FILE* output_file) {
    // Realiza un recorrido inOrden del árbol BST y escribe los datos en un archivo de salida
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

    // Medir el tiempo de construcción del BST secuencial
    clock_t start_time = clock();

    // Construir el BST secuencialmente
    for (int i = 0; i < num_elements; i++) {
        root = insert(root, data[i]);
    }

    clock_t end_time = clock();

    // Imprimir el tiempo de construcción
    printf("Tiempo de construcción del BST: %f segundos\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    // Almacenar los resultados en un nuevo archivo de texto
    FILE* output_file = fopen("salidaSecuencial.txt", "w");
    inOrder(root, output_file);
    fclose(output_file);

    // Liberar memoria
    free(data);

    return 0;
}
