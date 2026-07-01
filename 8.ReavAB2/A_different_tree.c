#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char letra;
    int freq;
    struct no *esq;
    struct no *dir;
} No;

No *criar_no(char letra, int freq) {
    No *novo = malloc(sizeof(No));

    novo->letra = letra;
    novo->freq = freq;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

int tem_maior_prioridade(No *a, No *b) {
    if (a->freq < b->freq) {
        return 1;
    }

    if (a->freq == b->freq && a->letra < b->letra) {
        return 1;
    }

    return 0;
}

void inserir_fila(No *fila[], int *tam, No *novo) {
    int i = *tam;

    while (i > 0 && tem_maior_prioridade(novo, fila[i - 1])) {
        fila[i] = fila[i - 1];
        i--;
    }

    fila[i] = novo;
    (*tam)++;
}

No *remover_fila(No *fila[], int *tam) {
    No *removido = fila[0];
    int i;

    for (i = 0; i < *tam - 1; i++) {
        fila[i] = fila[i + 1];
    }

    (*tam)--;

    return removido;
}

void imprimir_arvore(No *raiz) {
    if (raiz == NULL) {
        return;
    }

    imprimir_arvore(raiz->esq);
    printf("%c", raiz->letra);
    imprimir_arvore(raiz->dir);
}

void imprimir_codigo(No *raiz, char letra, char codigo[], int pos) {
    if (raiz == NULL) {
        return;
    }

    if (raiz->esq == NULL && raiz->dir == NULL) {
        if (raiz->letra == letra) {
            codigo[pos] = '\0';
            printf("%c\t-\t%s\n", letra, codigo);
        }
        return;
    }

    codigo[pos] = '0';
    imprimir_codigo(raiz->esq, letra, codigo, pos + 1);

    codigo[pos] = '1';
    imprimir_codigo(raiz->dir, letra, codigo, pos + 1);
}

int main() {
    char entrada[300];
    int freq[256] = {0};
    No *fila[300];
    No *esq;
    No *dir;
    No *novo;
    No *raiz;
    char codigo[300];

    int tam = 0;
    int i;

    fgets(entrada, 300, stdin);

    entrada[strcspn(entrada, "\n")] = '\0';

    for (i = 0; entrada[i] != '\0'; i++) {
        freq[(unsigned char) entrada[i]]++;
    }

    for (i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            novo = criar_no((char) i, freq[i]);
            inserir_fila(fila, &tam, novo);
        }
    }

    while (tam > 1) {
        esq = remover_fila(fila, &tam);
        dir = remover_fila(fila, &tam);

        novo = criar_no('*', esq->freq + dir->freq);
        novo->esq = esq;
        novo->dir = dir;

        inserir_fila(fila, &tam, novo);
    }

    raiz = fila[0];

    printf("Tree\t-\t");
    imprimir_arvore(raiz);
    printf("\n");

    for (i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            imprimir_codigo(raiz, (char) i, codigo, 0);
        }
    }

    return 0;
}
