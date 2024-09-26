#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No* novoNo(int valor) {
    No *no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->esq = no->dir = NULL;
    return no;
}

No* construirArvore(const char **str) {
    if (**str == '(') (*str)++;  

    if (**str == ')') {
        (*str)++;  
        return NULL;
    }

    int valor = 0;
    while (**str >= '0' && **str <= '9') {  
        valor = valor * 10 + (**str - '0');
        (*str)++;
    }

    No *raiz = novoNo(valor);
    raiz->esq = construirArvore(str);
    raiz->dir = construirArvore(str);

    if (**str == ')') (*str)++;  

    return raiz;
}

int contarNos(No *raiz) {
    if (!raiz) return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

int verificarCompleta(No *raiz, int nivel, int altura) {
    if (!raiz) return 1;

    if (!raiz->esq && !raiz->dir) return (nivel == altura); 

    if (!raiz->esq || !raiz->dir) return 0;  

    return verificarCompleta(raiz->esq, nivel + 1, altura) && verificarCompleta(raiz->dir, nivel + 1, altura);
}

int encontrarAltura(No *raiz) {
    if (!raiz) return -1;
    int esqAltura = encontrarAltura(raiz->esq);
    int dirAltura = encontrarAltura(raiz->dir);
    return 1 + (esqAltura > dirAltura ? esqAltura : dirAltura);
}

void encontrarNosUmFilho(No *raiz, int *nos, int *indice) {
    if (!raiz) return;

    encontrarNosUmFilho(raiz->esq, nos, indice);

    if ((raiz->esq && !raiz->dir) || (!raiz->esq && raiz->dir)) {
        nos[(*indice)++] = raiz->valor;
    }

    encontrarNosUmFilho(raiz->dir, nos, indice);
}

int main() {
    char entrada[1000];
    scanf("%s", entrada);

    const char *str = entrada;
    No *raiz = construirArvore(&str);

    int altura = encontrarAltura(raiz);
    if (verificarCompleta(raiz, 0, altura)) {
        printf("completa\n");
        printf("total de nos: %d\n", contarNos(raiz));
    } else {
        printf("nao completa\n");

        int nos[1000], indice = 0;
        encontrarNosUmFilho(raiz, nos, &indice);

        printf("nos com um filho: ");
        for (int i = 0; i < indice; i++) {
            printf("%d", nos[i]);
            if (i < indice - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
