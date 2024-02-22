#include <stdio.h>

// Função para ordenar um array usando o algoritmo de ordenação por inserção
void insertion_sort(int v[], int size) {
    int i, j, key;

    // Itera através do array a partir do segundo elemento
    for (i = 1; i < size; i++) {
        key = v[i]; // Armazena o valor atual a ser comparado
        j = i - 1;

        // Move os elementos maiores que o valor atual para a direita
        // até encontrar a posição correta para inserir o valor atual
        while ((j >= 0) && (v[j] > key)) {
            v[j + 1] = v[j]; // Desloca o elemento para a direita
            j--;
        }

        v[j + 1] = key; // Insere o valor atual na posição correta
    }
}

int main() {
    // Exemplo de uso do insertion_sort
    int array[] = {12, 11, 13, 5, 6};
    int tamanho = sizeof(array) / sizeof(array[0]);

    printf("Array original: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }

    // Chama a função insertion_sort para ordenar o array
    insertion_sort(array, tamanho);

    printf("\nArray ordenado: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
