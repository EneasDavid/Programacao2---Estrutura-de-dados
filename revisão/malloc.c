#include <stdio.h>
//O macllob está nessa bilbiote lib.h
#include <stdlib.h>

int main() {
    // Declarando um ponteiro para inteiros (que será nosso array) e uma variável para armazenar o tamanho do array
    int *lista, tamanho;

    // Solicitando ao usuário o tamanho desejado para o array
    printf("Digite o tamanho do array: ");
    scanf("%d", &tamanho);

    // Alocando dinamicamente memória para o array usando malloc
    //sizeof para obter quantos bites tem uma variavel da tipagem especifica e depois multiplica pelo tamanho pre informado
    lista = (int *)malloc(tamanho * sizeof(int));

    // Verificando se a alocação de memória foi bem-sucedida
    /*if (lista == NULL) {
        printf("Falha na alocação de memória.\n");
        return 1;  // Saindo do programa com código de erro
    }
    //em minha opininão isso é apenas para grandes porjetos
    */

    // Preenchendo o array com valores de 1 até o tamanho
    for (int i = 0; i < tamanho; i++) {
        lista[i] = i + 1;
    }

    // Imprimindo os elementos do array
    printf("Elementos do array: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", lista[i]);
    }

    // Liberando a memória alocada para o array
    free(lista);

    return 0;  // Saindo do programa com sucesso
}
