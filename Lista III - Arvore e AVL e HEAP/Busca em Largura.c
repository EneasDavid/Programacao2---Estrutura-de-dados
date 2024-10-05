#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int valor;
    struct no *proximo;
} No;

typedef struct grafo {
    int *distancias;
    int *anteriores;
    int total_vertices;
    No **adjacencias;
} Grafo;

typedef struct fila {
    int *itens;
    int inicio;
    int fim;
    int tamanho;
    int capacidade;
} Fila;

Fila *criarFila(int capacidade) {
    Fila *nova_fila = (Fila*)malloc(sizeof(Fila));
    memset(nova_fila, 0, sizeof(Fila));
    nova_fila->itens = (int*)malloc(capacidade * sizeof(int));
    memset(nova_fila->itens, 0, capacidade * sizeof(int));
    nova_fila->capacidade = capacidade;
    return nova_fila;
}

No *criarNo(int valor) {
    No *novo_no = (No*)calloc(1, sizeof(No));
    novo_no->valor = valor;
    novo_no->proximo = NULL;
    return novo_no;
}

Grafo *criarGrafo(int tamanho) {
    Grafo *novo_grafo = (Grafo*)malloc(sizeof(Grafo));
    memset(novo_grafo, 0, sizeof(Grafo));
    novo_grafo->adjacencias = (No**)malloc(tamanho * sizeof(No*));
    novo_grafo->distancias = (int*)malloc(tamanho * sizeof(int));
    novo_grafo->anteriores = (int*)malloc(tamanho * sizeof(int));
    memset(novo_grafo->adjacencias, 0, tamanho * sizeof(No*));
    memset(novo_grafo->distancias, 0, tamanho * sizeof(int));
    memset(novo_grafo->anteriores, 0, tamanho * sizeof(int));
    novo_grafo->total_vertices = tamanho;
    return novo_grafo;
}

void enfileirar(Fila *fila, int valor) {
    fila->itens[fila->fim] = valor;
    fila->fim++;
    fila->tamanho++;
}

int filaVazia(Fila *fila) {
    return fila->tamanho == 0;
}

int desenfileirar(Fila *fila) {
    int valor = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;
    return valor;
}

void adicionarAresta(Grafo *grafo, int origem, int destino) {
    No *novo_no = criarNo(destino);
    if (grafo->adjacencias[origem] == NULL || destino <= grafo->adjacencias[origem]->valor) {
        novo_no->proximo = grafo->adjacencias[origem];
        grafo->adjacencias[origem] = novo_no;
        return;
    }
    No *anterior = NULL;
    No *atual = grafo->adjacencias[origem];
    while (atual && destino > atual->valor) {
        anterior = atual;
        atual = atual->proximo;
    }
    novo_no->proximo = atual;
    anterior->proximo = novo_no;
}

void buscaLargura(Grafo *grafo, int origem, int destino) {
    int total_vertices = grafo->total_vertices;
    Fila *fila = criarFila(total_vertices);
    for (int i = 0; i < total_vertices; i++) {
        grafo->distancias[i] = -1;
        grafo->anteriores[i] = -1;
    }
    grafo->distancias[origem] = 0;
    enfileirar(fila, origem);

    while (!filaVazia(fila)) {
        int vertice_atual = desenfileirar(fila);
        printf("Iniciando busca em largura a partir de %d\n", vertice_atual);
        No *auxiliar = grafo->adjacencias[vertice_atual];
        while (auxiliar != NULL) {
            int adjacente = auxiliar->valor;
            if (grafo->distancias[adjacente] == -1) {
                grafo->distancias[adjacente] = grafo->distancias[vertice_atual] + 1;
                grafo->anteriores[adjacente] = vertice_atual;
                enfileirar(fila, adjacente);
            }
            auxiliar = auxiliar->proximo;
        }
    }
    printf("\n");
    free(fila->itens);
    free(fila);
}

void imprimirCaminho(int anteriores[], int origem, int destino) {
    if (origem == destino) {
        printf("%d", origem);
    } else {
        imprimirCaminho(anteriores, origem, anteriores[destino]);
        printf(" => %d", destino);
    }
}

int main() {
    int vertices, arestas, casos_teste;
    scanf("%d %d %d", &vertices, &arestas, &casos_teste);

    Grafo *grafo = criarGrafo(vertices);

    for (int i = 0; i < arestas; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        adicionarAresta(grafo, v1, v2);
    }

    for (int i = 1; i <= casos_teste; i++) {
        int origem, destino;
        scanf("%d %d", &origem, &destino);
        printf("\n--------\n\n");
        printf("Caso de Teste #%d - BFS(%d)\n\n", i, origem);

        buscaLargura(grafo, origem, destino);

        for (int j = 0; j < vertices; j++) {
            if (grafo->distancias[j] == -1)
                printf("%d | - | -\n", j);
            else if (grafo->distancias[j] == 0)
                printf("%d | %d | -\n", j, grafo->distancias[j]);
            else
                printf("%d | %d | %d\n", j, grafo->distancias[j], grafo->anteriores[j]);
        }

        if (grafo->distancias[destino] == -1)
            printf("\nSem caminho entre %d e %d\n", origem, destino);
        else {
            printf("\nCaminho entre %d e %d: ", origem, destino);
            imprimirCaminho(grafo->anteriores, origem, destino);
            printf("\n");
        }
    }
    printf("\n--------\n");
    return 0;
}