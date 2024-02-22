#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 50

typedef struct pilha{
    int item[max];
    int topo;
}TPilha;

void create(TPilha *pilha){
    pilha->topo=-1;
}

void push(TPilha *pilha, int item){
    pilha->topo++;
    pilha->item[pilha->topo]=item;
}

int pop(TPilha *pilha){
    int valorRemovido=pilha->item[pilha->topo];
    pilha->topo--;
    return valorRemovido;
}
void imprimir(TPilha *pilha){
    int i=pilha->topo;
    while(i>0){
        printf("%d ", pilha->item[i]);
        i--;
    }
    printf("%d\n", pilha->item[i]);
}

int main(){
    char entrada[12];
    TPilha pilha;
    create(&pilha);

    while(strcmp(entrada,"Finalizar")!=0){
        scanf(" %s", entrada);
        if(strcmp(entrada,"Empilhar")==0){
            int valor;
            scanf("%d", &valor);
            push(&pilha, valor);
        }else if(strcmp(entrada,"Desempilhar")==0){
            pop(&pilha);
        }else if(strcmp(entrada,"Imprimir")==0){
            imprimir(&pilha);
        }
    }
    return 0;
}