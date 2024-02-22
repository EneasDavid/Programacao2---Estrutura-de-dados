#include <stdio.h>
#include <stdlib.h>
#define max_size 10
//Lista circular

typedef struct fila{
    int tamanhoAtual;
    int inicio;
    int final;
    int items[max_size];
}Fila;

void enqueue(Fila *fila, int item){
    if(fila->tamanhoAtual<max_size){
        fila->final=(fila->final+1)%max_size;
        fila->items[fila->final]=item;
        fila->tamanhoAtual++;
    }
}

int is_empty(Fila *fila) {
    return fila->tamanhoAtual == 0;
}

int dequeue(Fila *fila){
    if(!is_empty(fila)){
        int dequeued=fila->items[fila->inicio];
        fila->inicio=(fila->inicio+1)%max_size;
        fila->tamanhoAtual--;
        return dequeued;
    }
}

void imprimir(Fila *fila){
    int contador=0;
    for(int i=fila->inicio;contador<fila->tamanhoAtual;i=(i+1)%max_size){
        printf("Valor: %d | Posicao %d\n", fila->items[i], i);
        contador++;
    }
}


Fila* criarFila(){
    Fila *queue=malloc(sizeof(Fila));
    queue->tamanhoAtual=0;
    queue->inicio=0;
    queue->final=max_size-1;
    return queue;
}

int main(){
    Fila *fila=criarFila();
    for(int i=1;i<11;i++){
        enqueue(fila,i);
    }
    imprimir(fila);
    dequeue(fila);
    imprimir(fila);
    enqueue(fila,11);
    imprimir(fila);
    return 0;
}