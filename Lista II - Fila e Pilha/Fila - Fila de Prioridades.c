#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct fila {
    ITEM vet[TAM];
    int front, rear;
} TFila;

typedef struct filaprio {
    TFila f1, f2, f3;
} TFilaPrio;

void create(TFila *f) {
	f->front = f->rear = 0;
}

void destroy(TFila *f) {
	f->front = f->rear;
}

int next(int n) {
    return (n + 1) % TAM;
}

int isfull(TFila *f) {
	return next(f->rear + 1) == f->front;
}

int isempty(TFila *f) {
	return f->front == f->rear;
}

void store(TFila *f, ITEM x) {
    if( isfull(f) ) {
        puts("overflow");
        abort();
    }
    f->vet[f->rear] = x;
    f->rear = next(f->rear);
}

ITEM retrieve(TFila *f) {
    if( isempty(f) ) {
        puts("underflow");
        abort();
    }
    ITEM aux = f->vet[f->front];
    f->front = next(f->front);
    return aux;
}

void createfp(TFilaPrio *fp) {
	//Insira o código aqui
}

void destroyfp(TFilaPrio *fp) {
	//Insira o código aqui
}

int isemptyfp(TFilaPrio *fp, int prio) {
	//Insira o código aqui
}

void storefp(TFilaPrio *fp, int prio, ITEM x) {
	//Insira o código aqui
}

ITEM retrievefp(TFilaPrio *fp, int prio) {
	//Insira o código aqui
}

void preenche(TFilaPrio *fp) {
    ITEM x;
    int prio, qtd, i;

    scanf("%d%*c", &qtd);

    for( i=0; i<qtd; i++ ) {
        scanf("%c %d%*c", &x, &prio);
        storefp(fp, prio, x);
    }
}

void exibe(TFilaPrio *fp) {
    int i;
    for( i=1; i<=3; i++ ) {
        printf("PRIORIDADE %d =", i);
        while( !isemptyfp(fp, i) )
            printf(" %c", retrievefp(fp, i));
        putchar('\n');
    }
}

int main(void) {
    TFilaPrio fp;

    createfp(&fp);
    preenche(&fp);
    exibe(&fp);
    destroyfp(&fp);

    return 0;
}
