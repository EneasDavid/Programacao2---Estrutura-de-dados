#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int valor;
    struct No *esquerdo;
    struct No *direito;
} No;

No* criarNo(int valor){
    No* novoNo=(No*)malloc(sizeof(No));
    novoNo->valor=valor;
    novoNo->esquerdo=NULL;
    novoNo->direito=NULL;
    return novoNo;
}

No* construirArvore(const char** str){
    if(**str=='\0' || **str==')') return NULL;
    (*str)++;
    int valor=0;
    while(**str>='0' && **str<='9'){
        valor=valor*10+(**str-'0');
        (*str)++;
    }

    No* raiz=criarNo(valor);
    raiz->esquerdo=construirArvore(str);
    raiz->direito=construirArvore(str);
    (*str)++;
    return raiz;
}

int buscarValor(No* raiz, int N, int profundidade){
    if(raiz==NULL) return -1;
    if(raiz->valor==N) return profundidade;
    int profundidadeEsquerda=buscarValor(raiz->esquerdo, N, profundidade+1);
    if(profundidadeEsquerda!=-1) return profundidadeEsquerda;
    return buscarValor(raiz->direito, N, profundidade+1);
}

void liberarArvore(No* raiz){
    if(raiz==NULL) return;
    liberarArvore(raiz->esquerdo);
    liberarArvore(raiz->direito);
    free(raiz);
}

int main(){
    char entrada[1000];
    scanf("%[^\n]", entrada);
    int N;
    scanf("%d", &N);
    const char* str=entrada;
    No* raiz=construirArvore(&str);
    int profundidade=buscarValor(raiz, N, 0);
    if(profundidade!=-1){
        printf("ESTA NA ARVORE\n");
        printf("%d\n", profundidade);
    } else{
        printf("NAO ESTA NA ARVORE\n");
        printf("-1\n");
    }

    liberarArvore(raiz);
    return 0;
}