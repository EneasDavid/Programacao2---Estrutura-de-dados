#include <stdio.h>
#include <stdlib.h>

typedef struct lista_encadeada{
    int valor;
    struct lista_encadeada *proximo;
}lista;
//usando a logica de enqueue at middle
void enqueue(lista **lE, int valor){
    lista *novaLista=malloc(sizeof(lista));
    novaLista->valor=valor;
    novaLista->proximo=NULL;
    if(*lE==NULL || valor<(*lE)->valor){
        novaLista->proximo=*lE;
        *lE=novaLista;
    }else{
        lista *temporario=*lE;
        //lembre do && você passou meia hora nisso
        while(temporario->proximo!=NULL && temporario->proximo->valor<valor){
            temporario=temporario->proximo;
        }
        novaLista->proximo=temporario->proximo;
        temporario->proximo=novaLista;
    }
}

void imprimir(lista *lE){
    if (lE==NULL) return;
    printf("%d ", lE->valor);
    imprimir(lE->proximo);
}

int main(){
    lista *listaEncadeada=NULL;
    int entrada;
    while(scanf("%d", &entrada)!=EOF){
        enqueue(&listaEncadeada, entrada);
    }
    imprimir(listaEncadeada);
    return 0;
}