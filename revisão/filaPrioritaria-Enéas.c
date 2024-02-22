#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int valor;
    int prioridade;
    struct node *proximo;
} Node;

typedef struct prioridadeFila {
    Node *inicio;
} PrioridadeFila;

// Função para verificar se a fila de prioridade está vazia
int is_empty(PrioridadeFila *pF) {
    return pF->inicio == NULL;
}

// Função para enfileirar um elemento com uma determinada prioridade
void enqueue(PrioridadeFila *pF, int entrada, int prioridade) {
    Node *node = malloc(sizeof(Node));
    node->valor = entrada;
    node->prioridade = prioridade;

    // Se a fila está vazia ou a prioridade do novo nó é maior que a do primeiro nó
    if (is_empty(pF) || (prioridade > pF->inicio->prioridade)) {
        node->proximo = pF->inicio;
        pF->inicio = node;
    } else {
        // Percorre a fila para encontrar a posição correta para o novo nó
        Node *atual = pF->inicio;
        while ((atual->proximo != NULL) && (atual->proximo->prioridade > prioridade)) {
            atual = atual->proximo;
        }
        node->proximo = atual->proximo;
        atual->proximo = node;
    }
}

// Função para desenfileirar o elemento com a maior prioridade
Node* dequeue(PrioridadeFila *pF) {
    if (!is_empty(pF)) {
        Node *node = pF->inicio;
        pF->inicio = pF->inicio->proximo;
        node->proximo = NULL;
        return node;
    }
    return NULL;
}

// Função para obter o valor do elemento com a maior prioridade sem desenfileirar
int maximum(PrioridadeFila *pF) {
    if (!is_empty(pF)) {
        // Imprime a prioridade máxima antes de retornar o valor
        printf("Prioridade Máxima: %d|", pF->inicio->prioridade);
        return pF->inicio->valor;
    }
    return -1;
}

int main() {
    PrioridadeFila *filaPrioritaria = malloc(sizeof(PrioridadeFila));

    // Teste 1: Enfileirar elementos com diferentes prioridades
    enqueue(filaPrioritaria, 5, 3);
    enqueue(filaPrioritaria, 10, 1);
    enqueue(filaPrioritaria, 7, 2);

    // Teste 2: Imprimir os elementos na fila de prioridade
    Node *current = filaPrioritaria->inicio;
    while (current != NULL) {
        printf("Valor: %d, Prioridade: %d\n", current->valor, current->prioridade);
        current = current->proximo;
    }

    // Teste 3: Desenfileirar o elemento com a maior prioridade
    Node *dequeuedNode = dequeue(filaPrioritaria);
    printf("Desenfileirado: Valor: %d, Prioridade: %d\n", dequeuedNode->valor, dequeuedNode->prioridade);

    // Teste 4: Imprimir os elementos restantes na fila de prioridade
    current = filaPrioritaria->inicio;
    while (current != NULL) {
        printf("Valor: %d, Prioridade: %d\n", current->valor, current->prioridade);
        current = current->proximo;
    }

    // Teste 5: Obter o valor do elemento com a maior prioridade sem desenfileirar
    int max = maximum(filaPrioritaria);
    printf("| Valor da vez: %d\n", max);

    free(filaPrioritaria);
    return 0;
}
