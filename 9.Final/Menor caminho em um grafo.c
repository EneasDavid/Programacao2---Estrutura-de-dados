#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXIMO_VERTICES 1000
#define INF 999999

typedef struct Aresta {
    int destino;
    struct Aresta *next;
} Aresta;

typedef struct Grafo {
    Aresta *adjacencia_list[MAXIMO_VERTICES];
    int num_vertices;
} Grafo;

Aresta *create_aresta(int destino) {
    Aresta *new_aresta = (Aresta *)malloc(sizeof(Aresta));
    if (!new_aresta) {
        printf("Erro de aloca��o de mem�ria\n");
        exit(1);
    }
    new_aresta->destino = destino;
    new_aresta->next = NULL;
    return new_aresta;
}

void insert_grafo(Grafo *grafo, int src, int destino) {
    Aresta *new_aresta = create_aresta(destino);
    new_aresta->next = grafo->adjacencia_list[src];
    grafo->adjacencia_list[src] = new_aresta;
}

void inicializar_grafo(Grafo *grafo, int num_vertices) {
    grafo->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        grafo->adjacencia_list[i] = NULL;
    }
}

int busca_em_largura(Grafo *grafo, int start, int fim) {
    int distancia[MAXIMO_VERTICES];
    bool visitado[MAXIMO_VERTICES] = {0};

    for (int i = 0; i < grafo->num_vertices; i++) distancia[i] = INF;

    distancia[start] = 0;
    visitado[start] = 1;

    int queue[MAXIMO_VERTICES];
    int front = 0, rear = 0;
    queue[rear++] = start;

    while (front < rear) {
        int vertice_atual = queue[front++];
        Aresta *temp = grafo->adjacencia_list[vertice_atual];

        while (temp != NULL) {
            int vertice_adjacente = temp->destino;

            if (!visitado[vertice_adjacente]) {
                visitado[vertice_adjacente] = 1;
                distancia[vertice_adjacente] = distancia[vertice_atual] + 1;

                if (vertice_adjacente == fim) {
                    return distancia[vertice_adjacente];
                }

                queue[rear++] = vertice_adjacente;
            }
            temp = temp->next;
        }
    }

    return -1;
}

int main() {
    Grafo main_grafo;

    int A, V;
    scanf("%d %d", &V, &A);

    inicializar_grafo(&main_grafo, V);

    for (int i = 0; i < A; i++) { 
        int V1i, V2i;
        scanf("%d %d", &V1i, &V2i);
        insert_grafo(&main_grafo, V1i, V2i);
    }

    int S, E;
    scanf("%d %d", &S, &E);

    int resultado = busca_em_largura(&main_grafo, S, E);
    if (resultado != -1) {
        printf("Tamanho do menor caminho de G: %d\n", resultado);
    } else {
        printf("N�o h� caminho entre os v�rtices %d e %d.\n", S, E);
    }

    return 0;
}
