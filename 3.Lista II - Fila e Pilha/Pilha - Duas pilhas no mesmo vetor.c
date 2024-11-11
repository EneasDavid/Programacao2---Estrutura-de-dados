#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct pilha_dupla {
    ITEM vet[TAM];
    int topo1, topo2;
} TPilhaDupla;

void create(TPilhaDupla *pd) {
    pd->topo1 = -1;      // Topo da pilha 1 come�a antes da posi��o 0
    pd->topo2 = TAM;     // Topo da pilha 2 come�a depois da �ltima posi��o
}

void destroy(TPilhaDupla *pd) {
    pd->topo1 = -1;
	pd->topo2 = TAM;
}

int isfull(TPilhaDupla *pd) {
    return pd->topo1 + 1 == pd->topo2;  // As pilhas se encontraram
}

int isempty(TPilhaDupla *pd, int topo) {
    if (topo == 1) return pd->topo1 == -1;
	else return pd->topo2 == TAM;
}

void push(TPilhaDupla *pd, ITEM x, int topo) {
    if (isfull(pd)) {
        printf("Pilha cheia!\n");
        return;
    }
    if (topo == 1) pd->vet[++(pd->topo1)] = x;
    else if (topo == 2) pd->vet[--(pd->topo2)] = x;
}

ITEM pop(TPilhaDupla *pd, int topo) {
    if (isempty(pd, topo)) {
        printf("Pilha %d vazia!\n", topo);
        return '\0';
    }

    if (topo == 1) return pd->vet[(pd->topo1)--];
    else return pd->vet[(pd->topo2)++];
}

ITEM top(TPilhaDupla *pd, int topo) {
    if (isempty(pd, topo)) {
        printf("Pilha %d vazia!\n", topo);
        return '\0';
    }
    if (topo == 1) return pd->vet[pd->topo1];
    else return pd->vet[pd->topo2];
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
