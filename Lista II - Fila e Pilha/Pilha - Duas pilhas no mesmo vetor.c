#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct pilha_dupla {
    ITEM vet[TAM];
    int topo1, topo2;
} TPilhaDupla;

void create(TPilhaDupla *pd) {
    pd->topo1=-1;
}

void destroy(TPilhaDupla *pd) {
	//Insira o código aqui
}

int isfull(TPilhaDupla *pd) {
	//Insira o código aqui
}

int isempty(TPilhaDupla *pd, int topo) {
	//Insira o código aqui
}

void push(TPilhaDupla *pd, ITEM x, int topo) {
	//Insira o código aqui
}

ITEM pop(TPilhaDupla *pd, int topo) {
	//Insira o código aqui
}

ITEM top(TPilhaDupla *pd, int topo) {
	//Insira o código aqui
}

void preenche(TPilhaDupla *pd) {
    ITEM x;
    int topo, qtd, i;

    scanf("%d%*c", &qtd);

    for( i=0; i<qtd; i++ ) {
        scanf("%c %d%*c", &x, &topo);
        push(pd, x, topo);
    }
}

void exibe(TPilhaDupla *pd) {
    int topo;

    while( scanf("%d", &topo) != EOF )
        printf("TOPO %d = %c\n", topo, pop(pd, topo));
}

int main(void) {
    TPilhaDupla pd;

    create(&pd);
    preenche(&pd);
    exibe(&pd);
    destroy(&pd);

    return 0;
}
