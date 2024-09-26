#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* prox;
} No;

No* criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->prox = NULL;
    return novoNo;
}

typedef struct {
    No** tabela;
    int tamanho;
} TabelaHash;

TabelaHash* criarTabelaHash(int tamanho) {
    TabelaHash* novaTabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    novaTabela->tabela = (No**)malloc(tamanho * sizeof(No*));
    novaTabela->tamanho = tamanho;
    
    for (int i = 0; i < tamanho; i++) {
        novaTabela->tabela[i] = NULL;
    }
    
    return novaTabela;
}

int hash(int chave, int tamanho) {
    return chave % tamanho;
}

void inserir(TabelaHash* tabela, int valor) {
    int indice = hash(valor, tabela->tamanho);
    No* novoNo = criarNo(valor);
    
    No* atual = tabela->tabela[indice];
    No* anterior = NULL;
    
    while (atual != NULL && atual->valor < valor) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (anterior == NULL) {
        novoNo->prox = tabela->tabela[indice];
        tabela->tabela[indice] = novoNo;
    } else {
        anterior->prox = novoNo;
        novoNo->prox = atual;
    }
}

void remover(TabelaHash* tabela, int valor) {
    int indice = hash(valor, tabela->tamanho);
    No* atual = tabela->tabela[indice];
    No* anterior = NULL;

    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return;
    }

    if (anterior == NULL) {
        tabela->tabela[indice] = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
}

void imprimir(TabelaHash* tabela) {
    for (int i = 0; i < tabela->tamanho; i++) {
        printf("[%d]:", i);
        No* atual = tabela->tabela[i];
        
        if (atual == NULL) {
            printf("Lista vazia!\n");
        } else {
            while (atual != NULL) {
                printf("%d=>", atual->valor);
                atual = atual->prox;
            }
            printf("\n");
        }
    }
}

void procurar(TabelaHash* tabela, int valor) {
    int indice = hash(valor, tabela->tamanho);
    No* atual = tabela->tabela[indice];
    int acessados = 0;
    int elementos = 0;
    
    for (int i = 0; i < tabela->tamanho; i++) {
        No* temp = tabela->tabela[i];
        while (temp != NULL) {
            elementos++;
            temp = temp->prox;
        }
    }
    
    while (atual != NULL) {
        acessados++;
        if (atual->valor == valor) {
            printf("BUSCA POR %d\n", valor);
            printf("numero de elementos da tabela hash: %d\n", elementos);
            printf("elemento %d encontrado!\n", valor);
            printf("numero de elementos acessados na tabela hash: %d\n", acessados);
            return;
        }
        atual = atual->prox;
    }
    
    printf("BUSCA POR %d\n", valor);
    printf("numero de elementos da tabela hash: %d\n", elementos);
    printf("elemento nao encontrado!\n");
    printf("numero de elementos acessados na tabela hash: %d\n", acessados);
}

int main() {
    int m, valor;
    char comando;
    scanf("%d", &m);
    TabelaHash* tabela = criarTabelaHash(m);
    while (scanf(" %c", &comando) && comando != 'f') {
        switch(comando){
            case 'a':
                scanf("%d", &valor);
                inserir(tabela, valor);
                break;
            case 'r':
                scanf("%d", &valor);
                remover(tabela, valor);
                break;
            case 'i':
                printf("imprimindo tabela hash:\n");
                imprimir(tabela);
                break;
            case 'p':
                scanf("%d", &valor);
                procurar(tabela, valor);
                break;
        }

    }
    
    return 0;
}