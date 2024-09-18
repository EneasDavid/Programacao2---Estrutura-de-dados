#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct{
    int notas[MAX_SIZE];
    int frente;
    int tras;
} Fila;

void inicializarFila(Fila *fila){
    fila->frente=0;
    fila->tras=0;
}

void enfileirar(Fila *fila, int nota){
    if(fila->tras<MAX_SIZE) fila->notas[fila->tras++]=nota;
}

int desenfileirar(Fila *fila){
    if(fila->frente<fila->tras) return fila->notas[fila->frente++];
    return -1;
}

int contarAlunosNaMesmaPosicao(Fila *filaOriginal, Fila *filaOrdenada, int M){
    int contador=0;
    for(int i=0; i<M; i++){
        int notaOriginal=desenfileirar(filaOriginal);
        int notaOrdenada=desenfileirar(filaOrdenada);
        if(notaOriginal==notaOrdenada){
            contador++;
        }
    }
    return contador;
}

void ordenarFila(Fila *fila){
    for(int i=fila->frente; i<fila->tras-1; i++){
        for(int j=fila->frente; j<fila->tras-1 -(i-fila->frente); j++){
            if(fila->notas[j]<fila->notas[j+1]){
                fila->notas[j]^= fila->notas[j+1];
                fila->notas[j+1] ^=fila->notas[j];
                fila->notas[j]^=fila->notas[j+1];
            }
        }
    }
}

void processarCasoTeste(){
    int M;
    scanf("%d", &M);

    Fila filaOriginal;
    Fila filaOrdenada;
    inicializarFila(&filaOriginal);
    inicializarFila(&filaOrdenada);

    for(int j=0; j<M; j++){
        int nota;
        scanf("%d", &nota);
        enfileirar(&filaOriginal, nota);
        enfileirar(&filaOrdenada, nota);
    }

    ordenarFila(&filaOrdenada);
    
    int resultado=contarAlunosNaMesmaPosicao(&filaOriginal, &filaOrdenada, M);
    printf("%d\n", resultado);
}

int main(){
    int N;
    scanf("%d", &N); 

    for(int i=0; i<N; i++){
        processarCasoTeste();
    }

    return 0;
}
