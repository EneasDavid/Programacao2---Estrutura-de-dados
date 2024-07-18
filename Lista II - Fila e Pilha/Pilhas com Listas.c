#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura da pilha
typedef struct {
    int *array; // Array para armazenar os inteiros
    int tamanho; // Tamanho atual da pilha
    int capacidade; // Capacidade máxima da pilha
} PilhaVariavel;

// Função para inicializar a pilha
PilhaVariavel* inicializarPilha(int capacidade) {
    PilhaVariavel* pilha = (PilhaVariavel*)malloc(sizeof(PilhaVariavel));
    pilha->array = (int*)malloc(capacidade * sizeof(int));
    pilha->tamanho = 0;
    pilha->capacidade = capacidade;
    return pilha;
}

// Função para realizar a operação PUSH na pilha
void push(PilhaVariavel* pilha, int* valores, int numValores) {
    if (pilha->tamanho + numValores > pilha->capacidade) {
        pilha->capacidade<<=1;
        pilha->array = (int*)realloc(pilha->array, pilha->capacidade * sizeof(int));
    }
    for (int i = 0; i < numValores; i++) {
        pilha->array[pilha->tamanho++] = valores[i];
    }
}

// Função para realizar a operação POP na pilha
void pop(PilhaVariavel* pilha) {
    if(pilha->tamanho==0) printf("EMPTY STACK\n");
    else{
        for (int i = pilha->tamanho - 1; i >= 0; i--) {
            printf("%d ", pilha->array[i]);
        }
        printf("\n");
        pilha->tamanho = 0;
    }
}

// Função principal
int main() {
    char comando[4];
    PilhaVariavel* pilha = inicializarPilha(10);
    while (scanf("%s", comando) != EOF) {
        if (strcmp(comando,"PUSH")==0){ // PUSH
            int numValores;
            scanf("%d", &numValores);
            int* valores = (int*)malloc(numValores * sizeof(int));
            for (int i = 0; i < numValores; i++) scanf("%d", &valores[i]);
            push(pilha, valores, numValores);
            free(valores);
        } else if (strcmp(comando,"POP")==0) pop(pilha);
    }
    free(pilha->array);
    free(pilha);
    return 0;
}