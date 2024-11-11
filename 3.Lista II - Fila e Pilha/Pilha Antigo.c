#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define max 100

typedef struct pilha{
    int valores[max];
    int topo;
}Pilha;

void create(Pilha *pilha){
    pilha->topo=-1;
}

void push(Pilha *pilha, int valor){
    pilha->topo++;
    pilha->valores[pilha->topo]=valor;
}

void pop(Pilha *pilha){
    pilha->topo--;
}

void imprimir(Pilha *pilha){
    int i;
    for(i=pilha->topo;i>0;i--){
        printf("%d ", pilha->valores[i]);
    }
    printf("%d\n",pilha->valores[i]);
}

int main() {
    char entrada[max];
    Pilha pilha;
    create(&pilha);
    while(strcmp(entrada,"Fim")!=0){
        scanf(" %s", entrada);
        if(strcmp(entrada,"Empilhar")==0){
            int valor;
            scanf("%d", &valor);
            push(&pilha, valor);
            imprimir(&pilha);
        }else if(strcmp(entrada,"Desempilhar")==0){
            pop(&pilha);
            imprimir(&pilha);
        }
    }
    return 0;
}