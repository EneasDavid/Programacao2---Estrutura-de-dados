#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct pilha {
    ITEM vet[TAM];
    int topo;
} TPilha;

void create(TPilha *p) {
    p->topo = -1;
}

void destroy(TPilha *p) {
    p->topo = -1;
}

int isfull(TPilha *p) {
    return p->topo == TAM;
}

int isempty(TPilha *p) {
    return p->topo == -1;
}

void push(TPilha *p, ITEM x) {
    if( isfull(p) ) {
        puts("overflow");
        abort();
    }
    p->topo++;
    p->vet[p->topo] = x;
}

ITEM pop(TPilha *p) {
    if( isempty(p) ) {
        puts("underflow");
        abort();
    }
    ITEM x = p->vet[p->topo];
    p->topo--;
    return x;
}

ITEM top(TPilha *p) {
    if( isempty(p) ) {
        puts("underflow");
        abort();
    }
    return p->vet[p->topo];
}

int palindromo(char s[]) {
    TPilha p;
    create(&p);
    //Verifica a posicao I é igual a uma quebra de linha
    for (int i=0; s[i]!='\0'; i++){
        //adiciona na lista
        push(&p, s[i]);
    }
    //verifica se I é menor ou igual ao topo da pilha
    for(int i=0;i<=p.topo;i++){
        //caso o topo da pilha (se liga que a função POP já remove o elemento, isso garante a ciclicidade da pilha) seja diferente da posicao de I na char, ele retorna false
        if(pop(&p)!=s[i]){
            return 0;
        }
    }
    //caso não, retorna true
    return 1;

}

int main(void) {
    char palavra[TAM];

    scanf("%s", palavra);
    printf(palindromo(palavra) ? "sim" : "nao");

    return 0;
}
