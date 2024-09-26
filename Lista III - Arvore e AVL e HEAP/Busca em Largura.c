#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    int aresta[MAX_VERTICES][MAX_VERTICES];
    int grau[MAX_VERTICES];
    int vertices;
    int arestas;
} Grafo;

typedef struct {
    int vertex;
    int predecessor;
    int distance;
} BFSInfo;

void inicializarGrafo(Grafo *g, int vertices) {
    g->vertices = vertices;
    g->arestas = 0;
    for (int i = 0; i < vertices; i++) {
        g->grau[i] = 0;
        for (int j = 0; j < vertices; j++) {
            g->aresta[i][j] = 0;
        }
    }
}

void adicionarAresta(Grafo *g, int origem, int destino) {
    g->aresta[origem][destino] = 1;
    g->aresta[destino][origem] = 1; 
    g->grau[origem]++;
    g->grau[destino]++;
}

void buscaEmLargura(Grafo *g, int origem, int destino, int casoTeste) {
    BFSInfo info[MAX_VERTICES];
    bool visitado[MAX_VERTICES] = {false};
    int fila[MAX_VERTICES];
    int frente = 0, tras = 0;

    for (int i = 0; i < g->vertices; i++) {
        info[i].distance = -1; 
        info[i].predecessor = -1;
    }

    info[origem].distance = 0;
    info[origem].predecessor = -1;
    fila[tras++] = origem;

    printf("Caso de Teste #%d - BFS(%d)\n", casoTeste, origem);

    while (frente < tras) {
        int v = fila[frente++];
        printf("Iniciando busca em largura a partir de %d\n", v);
        visitado[v] = true;

        for (int adj = 0; adj < g->vertices; adj++) {
            if (g->aresta[v][adj] == 1 && !visitado[adj]) {
                info[adj].distance = info[v].distance + 1;
                info[adj].predecessor = v;
                fila[tras++] = adj;
                visitado[adj] = true;
            }
        }
    }

    for (int i = 0; i < g->vertices; i++) {
        printf("%d | ", i);
        if (info[i].distance == -1) {
            printf("- | -\n");
        } else {
            printf("%d | %d\n", info[i].distance, info[i].predecessor);
        }
    }

    if (info[destino].distance == -1) {
        printf("Caminho entre %d e %d: Sem caminho entre %d e %d\n", origem, destino, origem, destino);
    } else {
        printf("Caminho entre %d e %d: ", origem, destino);
        int caminho[MAX_VERTICES];
        int index = 0;
        for (int v = destino; v != -1; v = info[v].predecessor) {
            caminho[index++] = v;
        }
        for (int i = index - 1; i >= 0; i--) {
            printf("%d", caminho[i]);
            if (i != 0) printf(" => ");
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    Grafo g;
    int V, A, T;
    scanf("%d %d %d", &V, &A, &T);
    inicializarGrafo(&g, V);

    for (int i = 0; i < A; i++) {
        int O, D;
        scanf("%d %d", &O, &D);
        adicionarAresta(&g, O, D);
    }

    for (int i = 0; i < T; i++) {
        int O, D;
        scanf("%d %d", &O, &D);
        buscaEmLargura(&g, O, D, i + 1);
    }

    return 0;
}
