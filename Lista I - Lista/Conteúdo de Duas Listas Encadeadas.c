#include <stdio.h>
#include <stdlib.h>

typedef struct lista_encadeada{
    int valor;
    struct lista_encadeada *proximo;
}listaEncadeada;

void enqueue(listaEncadeada *lE, int valor){
    listaEncadeada *novaLista=malloc(sizeof(listaEncadeada));
    novaLista->valor=valor;
    novaLista->proximo=NULL;
    if(lE->proximo==NULL) {
        lE->proximo=novaLista;
    }else{
        listaEncadeada *ultimo=lE->proximo;
        while(ultimo->proximo!=NULL) {
            ultimo=ultimo->proximo;
        }
        ultimo->proximo=novaLista;
    }
}

int dequeue(listaEncadeada *lE){
    if(lE->proximo==NULL){
        return -1;
    }
    listaEncadeada *remover=lE->proximo;
    int valorRemovido=remover->valor;
    lE->proximo=remover->proximo;
    free(remover);
    return valorRemovido;
}

int proximoValor(listaEncadeada *lE, int valorComparacao){
    if(lE==NULL) return 0;
    if(lE->valor==valorComparacao) return 1;
    return proximoValor(lE->proximo, valorComparacao);
}
/*
void imprimir(listaEncadeada *lE) {
    while (lE) {
        printf("%d ", lE->valor);
        lE = lE->proximo;
    }
}
*/

int main() {
    int n, m, entrada;
    
    scanf("%d", &n);
    listaEncadeada *primeiraLista=malloc(sizeof(listaEncadeada));
    primeiraLista->proximo=NULL;
    for (int i=0; i<n; i++){
        scanf("%d", &entrada);
        enqueue(primeiraLista, entrada);
    }

    scanf("%d", &m);
    listaEncadeada *segundaLista=malloc(sizeof(listaEncadeada));
    segundaLista->proximo=NULL;
    for (int i=0; i<m; i++){
        scanf("%d", &entrada);
        enqueue(segundaLista, entrada);
    }  
    for(int i=0;i<n;i++){
        if(proximoValor(primeiraLista,dequeue(segundaLista))){
            m--;
        }
    }
    printf("%d",!m);
    /*
    imprimir(primeiraLista->proximo);
    printf("\n");
    imprimir(segundaLista->proximo);
    */
    //Limpar memoria
    free(primeiraLista);
    free(segundaLista);

    return 0;
}
