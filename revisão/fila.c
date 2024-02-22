#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int valor;
    struct _node *proximo;
} Node;

void enqueue_at_start(Node **listaEncadeada, int value) {
    Node *novaLista = malloc(sizeof(Node));
    novaLista->valor = value;
    novaLista->proximo = *listaEncadeada;
    *listaEncadeada = novaLista;
}

void enqueue_at_end(Node **listaEncadeada, int value) {
    Node *novaLista = malloc(sizeof(Node));
    novaLista->valor = value;
    novaLista->proximo = NULL;
    if (*listaEncadeada == NULL) {
        *listaEncadeada = novaLista;
    } else {
        Node *temp = *listaEncadeada;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novaLista;
    }
}

void enqueue_at_middle(Node **listaEncadeada, int valor, int valorAnterior) {
    Node *novaLista = malloc(sizeof(Node));
    novaLista->valor = valor;

    if (*listaEncadeada == NULL) {
        novaLista->proximo = NULL;
        *listaEncadeada = novaLista;
    } else {
        Node *temp = *listaEncadeada;
        while (temp->proximo != NULL && temp->valor != valorAnterior) {
            temp = temp->proximo;
        }
        novaLista->proximo = temp->proximo;
        temp->proximo = novaLista;
    }
}

void dequeue(Node *listaEncadeada) {
    if (listaEncadeada) {
        Node *temp = listaEncadeada->proximo;
        listaEncadeada->proximo = temp->proximo;
        free(temp);
    }
}

void dequeue_in_search(Node *no, int valorBusca){
    Node *atual=no;
    Node *anterior=NULL;
    while(atual && atual->valor!=valorBusca){
        anterior=atual;
        atual=atual->proximo;
    }
    if(!atual){
        return no;
    }
    if(!anterior){
        no=atual->proximo;
    }else{
        anterior->proximo=atual->proximo;
    }
    free(atual);
}

void imprimir(Node *listaEncadeada) {
    if(listaEncadeada){
        printf("%d ", listaEncadeada->valor);
        imprimir(listaEncadeada->proximo);
    }
    printf("\n");
}

int main() {
    Node *listaEncadeada = NULL;

    for (int i = 1; i < 6; i++) {
        enqueue_at_end(&listaEncadeada, i);
    }

    imprimir(listaEncadeada);

    enqueue_at_start(&listaEncadeada, 7);
    imprimir(listaEncadeada);

    enqueue_at_middle(&listaEncadeada, 9, 3);
    imprimir(listaEncadeada);

    dequeue(listaEncadeada);
    imprimir(listaEncadeada);

    free(listaEncadeada);

    return 0;
}
