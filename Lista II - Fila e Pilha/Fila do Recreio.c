#include <stdio.h>
#include <stdlib.h>

typedef struct fila{
    int valor;
    struct fila *proximo;
}Fila;

void create(Fila *fila){
    fila=(Fila*)malloc(sizeof(Fila));
    
}
int main(){
    int qtnListas;

    scanf("%d", &qtnListas);
    while(qtnListas--){
        create()
    }
    return 0;
}