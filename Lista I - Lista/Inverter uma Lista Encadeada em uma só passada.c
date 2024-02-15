#include <stdio.h>
#include <stdlib.h>

typedef struct _listaEncadeada{
    int valor;
    struct _listaEncadeada *proximo;
}listaEncadeada;

void enqueue(listaEncadeada **lE, int valor){
    listaEncadeada *novaLista=malloc(sizeof(listaEncadeada));
    novaLista->valor=valor;
    novaLista->proximo=NULL;
    if(*lE==NULL){
        *lE=novaLista;
    }else{
        listaEncadeada *ultimo=*lE;
        while(ultimo->proximo!=NULL){
            ultimo=ultimo->proximo;
        }
        ultimo->proximo=novaLista;
    }
}

listaEncadeada *inverter(listaEncadeada *lE) {
    listaEncadeada *anterior=NULL;
    listaEncadeada *atual=lE;
    listaEncadeada *proxima=NULL;
    while (atual!=NULL){
        proxima=atual->proximo;
        atual->proximo=anterior;
        anterior=atual;
        atual=proxima;
    }
    return anterior;
}


void imprimir(listaEncadeada *lE){
    while(lE){
        printf("%d ",lE->valor);
        lE=lE->proximo;
    }
}

int main(){
    int entrada;
    listaEncadeada *lista=NULL;
    while (scanf("%d", &entrada)!=EOF){
        enqueue(&lista,entrada);
    }
    lista=inverter(lista);
    imprimir(lista);
    free(lista);
    return 0;
}