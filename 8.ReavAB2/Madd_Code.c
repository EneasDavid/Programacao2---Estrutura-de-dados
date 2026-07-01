#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char valor;
    struct no *esq;
    struct no *dir;
} No;

No *criar_no(char valor) {
    No *novo = malloc(sizeof(No));

    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

No *inserir(No *raiz, char valor) {
    if (raiz == NULL) {
        return criar_no(valor);
    }

    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    } else {
        raiz->dir = inserir(raiz->dir, valor);
    }

    return raiz;
}

int main() {
    char geradora[] = "MGTCKQWAEILORUY BDFHJNPSVXZ";
    char entrada[100000];

    No *raiz = NULL;
    No *atual;

    int i;

    for (i = 0; geradora[i] != '\0'; i++) {
        raiz = inserir(raiz, geradora[i]);
    }

    scanf("%s", entrada);

    atual = raiz;

    for (i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] == '-') {
            atual = atual->esq;
        } else if (entrada[i] == '|') {
            atual = atual->dir;
        } else if (entrada[i] == '@') {
            atual = raiz;
        } else if (entrada[i] == '*') {
            printf("%c", atual->valor);
            atual = raiz;
        }
    }

    printf("\n");

    return 0;
}
