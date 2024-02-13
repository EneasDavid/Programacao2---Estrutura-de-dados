#include <stdio.h>
#include <stdlib.h>

// Função para mesclar duas sub-listas ordenadas em uma única lista ordenada
void merge(int array[], int inicio, int meio, int fim) {
    int tamanho1 = meio - inicio + 1;
    int tamanho2 = fim - meio;
    
    // Cria arrays temporários para armazenar as sub-listas
    int subArrayEsquerdo[tamanho1];
    int subArrayDireito[tamanho2];

    // Copia os dados para os arrays temporários subArrayEsquerdo[] e subArrayDireito[]
    for (int i = 0; i < tamanho1; i++)
        subArrayEsquerdo[i] = array[inicio + i];
    for (int j = 0; j < tamanho2; j++)
        subArrayDireito[j] = array[meio + 1 + j];
    
    // Mescla os arrays temporários de volta na lista original array[]
    int i = 0; // Índice inicial da primeira sub-lista
    int j = 0; // Índice inicial da segunda sub-lista
    int k = inicio; // Índice inicial da lista mesclada

    while (i < tamanho1 && j < tamanho2) {
        if (subArrayEsquerdo[i] <= subArrayDireito[j]) {
            array[k] = subArrayEsquerdo[i];
            i++;
        } else {
            array[k] = subArrayDireito[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de subArrayEsquerdo[], se houver
    while (i < tamanho1) {
        array[k] = subArrayEsquerdo[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de subArrayDireito[], se houver
    while (j < tamanho2) {
        array[k] = subArrayDireito[j];
        j++;
        k++;
    }
}

// Função principal que implementa o algoritmo de ordenação Merge Sort
void merge_sort(int array[], int inicio, int fim) {
    if (inicio < fim) {
        // Encontra o ponto médio do array
        int meio = inicio + (fim - inicio) / 2;

        // Recursivamente ordena as duas metades
        merge_sort(array, inicio, meio);
        merge_sort(array, meio + 1, fim);

        // Mescla as duas metades ordenadas
        merge(array, inicio, meio, fim);
    }
}

int main() {
    int array[] = {12, 11, 13, 5, 6, 7};
    int tamanho = sizeof(array) / sizeof(array[0]);

    printf("Array original: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }

    merge_sort(array, 0, tamanho - 1);

    printf("\nArray ordenado: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
