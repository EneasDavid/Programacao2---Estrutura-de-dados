#include <stdio.h>
#include <stdlib.h>
// Fila é do tipo First-In-First-Out (FIFO)
typedef struct _fila{
    int valor;
    struct _fila *fila;
}Fila;

void enqueue(Fila **fila, int entrada){
    Fila *aux, *proximaPosicao=malloc(sizeof(Fila));
    proximaPosicao->valor=entrada;
    proximaPosicao->fila=NULL;
    //Indicando o proximo valor da lista
    aux= *fila;
    if(*fila){
        while(aux->fila!=NULL){
            aux=aux->fila;
        }
        aux->fila=proximaPosicao;
    }else{
        *fila=proximaPosicao;
    }
}

void dequeue(Fila **fila){
    Fila *remover = NULL;
    remover=*fila;
    *fila=remover->fila;
    free(remover);
}

void imprimir(Fila *comeco){
     while (comeco) {
        printf("%d\n", comeco->valor);
        comeco = comeco->fila;
    }
}

int main(){
    Fila *comeco = NULL;
    for(int i=1;i<6;i++){
        enqueue(&comeco, i);
    }
    imprimir(comeco);
    printf("Usando o dequeue\n");
    dequeue(&comeco);
    imprimir(comeco);
    return 0;
}