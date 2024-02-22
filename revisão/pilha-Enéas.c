#include <stdio.h>
#include <stdlib.h>
//Pila usa a logica de LIFO (Lest-In, First-Out)

//Codigos bases
typedef struct _no{
    int valor;
    struct _no *proximo;
}No;

void push (int entrada, No **topo){
    No *novoTopo=malloc(sizeof(No));
    novoTopo->valor=entrada;
    novoTopo->proximo=*topo;
    *topo=novoTopo;
}

void pop(No **topo){
    No *remover=*topo;
    *topo=remover->proximo;
    free(remover);
}

void imprimir(No *topo){
    while(topo){
        printf("Valor: %d| Proximo: %p\n", topo->valor, topo->proximo);
        topo=topo->proximo;
    }
}
//Codigos bases

int main(){
    No *topo = NULL;
    /*
    printf("Primeiro topo: %p\n", topo);
    push(&topo,5);
    printf("Segundo topo: %p\n", topo);
    imprimirPila(topo);
    pop(&topo);
    printf("Desempilhando topo: %p\n", topo);
    */
    //Com base no codigo acima, vamos tentar fazer um loop e receber valores para a pilha
    int tamanhoPilha;
    printf("Quantos elementos terá nossa lista? ");
    scanf("%d", &tamanhoPilha);
    for(int i=0;i<tamanhoPilha;i++){
        int entrada;
        printf("Digite o valor para a posição %d: ",i+1);
        scanf("%d", &entrada);
        push(entrada,&topo);
    }
    imprimir(topo);
    printf("removendo um elemento\n");
    pop(&topo);
    imprimir(topo);
    return 0;
}