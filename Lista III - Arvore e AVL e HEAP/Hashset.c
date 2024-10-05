#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct no {
    int valor;
    struct no *proximo;
} No;

typedef struct tabela_dispersao {
    int tamanho;
    int total_elementos;
    int maior_lista;
    No **listas;
} TabelaDispersao;

TabelaDispersao *criarTabelaDispersao(int tamanho) {
    TabelaDispersao *novaTabela = (TabelaDispersao *)malloc(sizeof(TabelaDispersao));
    novaTabela->tamanho = tamanho;
    novaTabela->total_elementos = 0;
    novaTabela->maior_lista = 0;
    novaTabela->listas = (No **)malloc(tamanho * sizeof(No *));
    for (int i = 0; i < tamanho; i++) {
        novaTabela->listas[i] = NULL;
    }
    return novaTabela;
}

int funcaoDispersao(int valor, int tamanho) {
    return valor % tamanho;
}

bool buscarElemento(TabelaDispersao *tabela, int valor, int *comparacoes) {
    int indice = funcaoDispersao(valor, tabela->tamanho);
    No *atual = tabela->listas[indice];
    int contador = 0;
    while (atual != NULL) {
        contador++;
        if (atual->valor == valor) {
            *comparacoes = contador;
            return true;
        }
        atual = atual->proximo;
    }
    *comparacoes = contador;
    return false;
}

int inserirElemento(TabelaDispersao *tabela, int valor, int *comparacoes) {
    if (buscarElemento(tabela, valor, comparacoes)) {
        return false;
    }

    int indice = funcaoDispersao(valor, tabela->tamanho);
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->proximo = tabela->listas[indice];
    tabela->listas[indice] = novoNo;

    tabela->total_elementos++;
    if (tabela->total_elementos >= tabela->tamanho * 0.75) {
        int tamanho_antigo = tabela->tamanho;
        tabela->tamanho = 2 * tabela->tamanho - 1;
        No **antigas_listas = tabela->listas;
        tabela->listas = (No **)malloc(tabela->tamanho * sizeof(No *));
        for (int i = 0; i < tabela->tamanho; i++) {
            tabela->listas[i] = NULL;
        }

        for (int i = 0; i < tamanho_antigo; i++) {
            No *atual = antigas_listas[i];
            while (atual != NULL) {
                No *proximo = atual->proximo;
                int novo_indice = funcaoDispersao(atual->valor, tabela->tamanho);
                atual->proximo = tabela->listas[novo_indice];
                tabela->listas[novo_indice] = atual;
                atual = proximo;
            }
        }

        free(antigas_listas);
    }
    return true;
}

bool removerElemento(TabelaDispersao *tabela, int valor, int *comparacoes) {
    int indice = funcaoDispersao(valor, tabela->tamanho);
    No *atual = tabela->listas[indice];
    No *anterior = NULL;
    int contador = 0;
    while (atual != NULL) {
        contador++;
        if (atual->valor == valor) {
            if (anterior == NULL) {
                tabela->listas[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            tabela->total_elementos--;
            *comparacoes = contador;
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    *comparacoes = contador;
    return false;
}

int calcularMaiorLista(TabelaDispersao *tabela) {
    int max = 0;
    for (int i = 0; i < tabela->tamanho; i++) {
        int contador = 0;
        No *atual = tabela->listas[i];
        while (atual != NULL) {
            contador++;
            atual = atual->proximo;
        }
        if (contador > max) {
            max = contador;
        }
    }
    return max;
}

int main(void) {
    TabelaDispersao *tabela = criarTabelaDispersao(7);

    int i = 0, comparacoes = 0;
    char comando[4];
    while (scanf("%s", comando) == 1) {
        int entradaValor;

        if (strcmp(comando, "ADD") == 0) {
            scanf("%d", &entradaValor);
            int resultado = inserirElemento(tabela, entradaValor, &comparacoes);
            printf("%d %d %d\n", i, resultado, comparacoes);
            comparacoes = 0;
        } else if (strcmp(comando, "DEL") == 0) {
            scanf("%d", &entradaValor);
            int resultado = removerElemento(tabela, entradaValor, &comparacoes);
            printf("%d %d %d\n", i, resultado, comparacoes);
            comparacoes = 0;
        } else if (strcmp(comando, "HAS") == 0) {
            scanf("%d", &entradaValor);
            int resultado = buscarElemento(tabela, entradaValor, &comparacoes);
            printf("%d %d %d\n", i, resultado, comparacoes);
            comparacoes = 0;
        } else if (strcmp(comando, "PRT") == 0) {
            printf("%d %d %d %d\n", i, tabela->tamanho, tabela->total_elementos, calcularMaiorLista(tabela));
        }
        i += 1;
    }
    free(tabela);
    return 0;
}