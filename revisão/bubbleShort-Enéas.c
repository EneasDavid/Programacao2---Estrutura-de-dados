#include <stdio.h>
#include <stdlib.h>

// Função para trocar dois elementos de posição em um array
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função principal que implementa o algoritmo de ordenação Bubble Sort
void bubble_sort(int array[], int tamanho) {
    // Itera através de todos os elementos do array
    for (int i = 0; i < tamanho - 1; i++) {
        // Últimos 'i' elementos já estão no lugar correto
        for (int j = 0; j < tamanho - i - 1; j++) {
            // Compara elementos adjacentes e troca se estiverem na ordem errada
            if (array[j] > array[j + 1]) {
                trocar(&array[j], &array[j + 1]);
            }
        }
    }
}

int main() {
    // Exemplo de uso do Bubble Sort
    int array[] = {64, 25, 12, 22, 11};
    int tamanho = sizeof(array) / sizeof(array[0]);

    printf("Array original: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }

    // Chama a função bubble_sort para ordenar o array
    bubble_sort(array, tamanho);

    printf("\nArray ordenado: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
