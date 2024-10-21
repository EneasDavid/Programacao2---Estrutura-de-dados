#include <stdio.h>
#include <stdlib.h>

#define N 5
#define DIRECOES { \
    {0, -1},   /* Esquerda */ \
    {0, 1},    /* Direita */  \
    {1, 0},    /* Baixo */    \
    {-1, 0}    /* Cima */     \
}

// Estrutura para representar um nó do caminho
typedef struct No {
    // Posição do nó seguindo um plano carteziano (x,y)
    int posX, posY;
    // Custo do caminho da origem até o nó
    int custoCaminho;  
    // Heurística (menor distancia da posição atual até o objetivo subtraindo o custo do caminho)
    int heuristica;    
    // Custo total (caminho + heurística)
    int custoTotal;    
    // Nó pai
    struct No* pai;    
} No;

typedef struct {
    // Lista de nós (aberta ou fechada)
    No* nos[N * N];
    // Tamanho da lista
    int tamanho;
} Lista;

// Matriz de 5x5 onde 0 é caminho navegável e 1 é barreira
int matriz[N][N] = {
    {0, 0, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0}
};

// Função para criar um nó
No* criar_no(int x, int y, int custoCaminho, No* pai) {
    No* no = (No*)malloc(sizeof(No));
    no->posX = x;
    no->posY = y;
    no->custoCaminho = custoCaminho;
    no->pai = pai;
    return no;
}

// Função para calcular a heurística (distância de Manhattan)
int calcular_heuristica(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Função para verificar se é uma barreira
int eh_barreira(int x, int y) {
    if (x < 0 || y < 0 || x >= N || y >= N) return 1;
    return matriz[x][y] == 1;
}

// Funções para manipulação de listas
void adicionar_na_lista(Lista *lista, No *no) {
    lista->nos[lista->tamanho++] = no;
}

int esta_na_lista(Lista *lista, int x, int y) {
    for (int i = 0; i < lista->tamanho; i++) {
        if (lista->nos[i]->posX == x && lista->nos[i]->posY == y) return 1;
    }
    return 0;
}

No* remover_da_lista(Lista *lista, int x, int y) {
    for (int i = 0; i < lista->tamanho; i++) {
        if (lista->nos[i]->posX == x && lista->nos[i]->posY == y) {
            No *no = lista->nos[i];
            lista->tamanho--;
            for (int j = i; j < lista->tamanho; j++) {
                lista->nos[j] = lista->nos[j + 1];
            }
            return no;
        }
    }
    return NULL;
}

// Função para processar chegada ao objetivo
void processar_chegada(No *atual) {
    printf("\nCaminho encontrado: ");
    No* no = atual;
    while (no) {
        printf("(%d, %d) -> ", no->posX, no->posY);
        no = no->pai;
    }
    printf("Objetivo\n");
}

// Função para obter o nó com menor custo na lista aberta
No* obter_no_com_menor_custo(Lista *lista) {
    // Inicializar com o primeiro nó
    No *menor = lista->nos[0];
    // Índice do menor nó
    int indice = 0;
    // Procurar o nó com menor custo
    for (int i = 1; i < lista->tamanho; i++) {
        // Se o custo do nó atual for menor que o menor custo
        if (lista->nos[i]->custoTotal < menor->custoTotal) {
            // Atualizar o menor custo e índice
            menor = lista->nos[i];
            // Atualizar o menor
            indice = i;
        }
    }
    // Remover o nó da lista aberta
    remover_da_lista(lista, menor->posX, menor->posY);
    // Retornar o nó com menor custo
    return menor;
}

// Função para expandir os vizinhos
void expandir_vizinhos(No *atual, Lista *lista_aberta, Lista *lista_fechada, int objetivoX, int objetivoY) {
    // Matriz de direções para mover: cima, direita, baixo, esquerda
    int direcoes[4][2] = DIRECOES;

    for (int i = 0; i < 4; i++) {
        // Calcular a nova posição usando o previsto na matriz de direções
        int novoX = atual->posX + direcoes[i][0];
        // Calcular a nova posição usando o previsto na matriz de direções
        int novoY = atual->posY + direcoes[i][1];

        if (!eh_barreira(novoX, novoY) && !esta_na_lista(lista_fechada, novoX, novoY)) {
            int g_tentativo = atual->custoCaminho + 1;
            No* vizinho = criar_no(novoX, novoY, g_tentativo, atual);
            vizinho->heuristica = calcular_heuristica(novoX, novoY, objetivoX, objetivoY);
            vizinho->custoTotal = vizinho->custoCaminho + vizinho->heuristica;

            if (!esta_na_lista(lista_aberta, novoX, novoY)) {
                adicionar_na_lista(lista_aberta, vizinho);
            }
        }
    }
}

// Função principal do algoritmo A*
void a_estrela(int inicioX, int inicioY, int objetivoX, int objetivoY) {
    if (eh_barreira(inicioX, inicioY) || eh_barreira(objetivoX, objetivoY)) {
        printf("Início ou objetivo é uma barreira!\n");
        return;
    }

    Lista lista_aberta = { .tamanho = 0 };
    Lista lista_fechada = { .tamanho = 0 };

    No *inicio = criar_no(inicioX, inicioY, 0, NULL);
    inicio->heuristica = calcular_heuristica(inicioX, inicioY, objetivoX, objetivoY);
    inicio->custoTotal = inicio->custoCaminho + inicio->heuristica;

    adicionar_na_lista(&lista_aberta, inicio);

    while (lista_aberta.tamanho > 0) {
        No *atual = obter_no_com_menor_custo(&lista_aberta);
        adicionar_na_lista(&lista_fechada, atual);

        if (atual->posX == objetivoX && atual->posY == objetivoY) {
            processar_chegada(atual);
            return;
        }

        expandir_vizinhos(atual, &lista_aberta, &lista_fechada, objetivoX, objetivoY);
    }

    printf("Caminho não encontrado.\n");
}

int main() {
    int inicioX = 0, inicioY = 4;
    int objetivoX = 4, objetivoY = 2;

    a_estrela(inicioX, inicioY, objetivoX, objetivoY);

    return 0;
}