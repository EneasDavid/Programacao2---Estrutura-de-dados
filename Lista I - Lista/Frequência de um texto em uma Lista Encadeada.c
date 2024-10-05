#include <stdio.h>
#include <stdlib.h>

typedef struct letra{
    char letra;
    int frequencia;
    struct letra *proximo;
} Letra;

void enqueue(Letra **lista, char valor){
    Letra *novoCaracter=malloc(sizeof(Letra));
    novoCaracter->letra=valor;
    novoCaracter->frequencia=1;
    novoCaracter->proximo=NULL;

    if(*lista==NULL || valor>(*lista)->letra){
        novoCaracter->proximo=*lista;
        *lista=novoCaracter;
        return;
    }

    Letra *temporario=*lista;
    if(temporario->letra==valor){
        temporario->frequencia+=1;
        free(novoCaracter); 
    }else{
        while(temporario->proximo!=NULL && valor<temporario->proximo->letra){
            temporario=temporario->proximo;
        }
        if(temporario->proximo!=NULL && temporario->proximo->letra==valor){
            temporario->proximo->frequencia+=1;
            free(novoCaracter);
        }else{
            novoCaracter->proximo=temporario->proximo;
            temporario->proximo=novoCaracter;
        }
    }
}

void imprimir(const Letra *lista){
    while (lista!=NULL){
        printf("%c %d\n", lista->letra, lista->frequencia);
        lista=lista->proximo;
    }
}

// Função para liberar a memória da lista encadeada
void liberarMemoria(Letra *lista){
    while(lista!=NULL){
        Letra *proximo=lista->proximo;
        free(lista);
        lista=proximo;
    }
}

int main(){
    Letra *lista=NULL;
    char entrada;
    while((entrada=getchar())!=EOF){
        enqueue(&lista, entrada);
    }
    imprimir(lista);
    liberarMemoria(lista);
    return 0;
}
