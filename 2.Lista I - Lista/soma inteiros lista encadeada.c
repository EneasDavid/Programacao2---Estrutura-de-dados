#include <stdio.h>
#include <stdlib.h>

typedef struct lista_encadeada {
    int valor;
    struct lista_encadeada *proximo;
} listaEncadeada;

void enqueue(listaEncadeada **lE, int valor) {
    listaEncadeada *novaLista=malloc(sizeof(listaEncadeada));
    novaLista->valor=valor;
    novaLista->proximo=*lE;
    *lE = novaLista;
}

listaEncadeada* somaLista(listaEncadeada *um, listaEncadeada *dois) {
    listaEncadeada *somaLista=NULL;
    int dezenaNaSoma=0;
    //Primeiro array pode ser maior que o segundo e vice versa, e também a dezena tem que ser adicionada
    while (um!=NULL || dois!=NULL || dezenaNaSoma) {
        int soma=dezenaNaSoma;
        if(um!=NULL){
            soma+=um->valor;
            um=um->proximo;
        }
        if(dois!=NULL){
            soma+=dois->valor;
            dois=dois->proximo;
        }
        dezenaNaSoma=soma/10; // pega o que ultrapassa de 9
        enqueue(&somaLista, soma % 10);
    }
    return somaLista;
}

void imprimir(listaEncadeada *lE) {
    if (!lE) {
        printf("Lista vazia!\n");
        return;
    }
    // Encontrar o primeiro dígito não nulo
    while (lE!=NULL && lE->valor==0){
        lE=lE->proximo;
    }
    while (lE!=NULL){
        printf("%d ", lE->valor);
        lE=lE->proximo;
    }
}

int main() {
    listaEncadeada *listaUm=NULL;
    listaEncadeada *listaDois=NULL;
    char entrada;
    while((entrada=getchar())!='+') {
        if (entrada!=' ' && entrada!='\n') {
            enqueue(&listaUm, entrada-'0');
        }
    }

    // Limpa o buffer de entrada antes de pedir mais input
    while(getchar()!='\n');

    while((entrada=getchar())!='='){
        if(entrada!=' ' && entrada!='\n') {
            enqueue(&listaDois, entrada-'0');
        }
    }
    listaEncadeada *resultado=somaLista(listaUm, listaDois);
    imprimir(resultado);
    free(listaUm);
    free(listaDois);
    free(resultado);
    return 0;
}