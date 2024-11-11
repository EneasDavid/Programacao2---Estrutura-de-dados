#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int item;
    struct Node *next;
}node;

typedef struct Stack{
    node *top;
}stack;

stack* createStack(){
    stack* new_stack=(stack*)malloc(sizeof(stack));
    new_stack->top=NULL;
    return new_stack;
}

void push(stack *stack,int item){
    node *newNS=(node*)malloc(sizeof(node));
    newNS->item=item;
    newNS->next=stack->top;
    stack->top=newNS;
}

void freeList(stack *stack){
    node *aux=stack->top;
    while(aux!=NULL){
        node *aux2=aux->next;
        free(aux);
        aux=aux2;
    }
    stack->top=NULL;
}

int sum(stack *stack){
    int cont=0;
    node *aux=stack->top;
    while(aux!=NULL){
        cont+=aux->item;
        aux=aux->next;
    }
    return cont;
}

int main(){
    stack *stackF=createStack();
    stack *stackB=createStack();
    char comando[14];
    while(scanf(" %s", comando)!=EOF){
        if(strcmp(comando,"ENTER")==0){
            push(stackF,1);
            freeList(stackB);
        }else if(strcmp(comando,"BACK")==0 && stackB!=NULL){
            push(stackF,-1);
            push(stackB,1);
        }else if(strcmp(comando,"FORWARD")==0 && sum(stackB)>0){
            push(stackF,1);
            push(stackB,-1);
        }
    }

    int contF=sum(stackB);
    int contB=sum(stackF)-1;
    printf("BACK: %d\nFORWARD: %d",contB,contF);

    freeList(stackF);
    freeList(stackB);
    free(stackF);
    free(stackB);
	return 0;
}