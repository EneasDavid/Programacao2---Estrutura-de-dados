#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 10000

typedef struct{
    int tamanho_atual;
    int dados[MAX_SIZE];
} Lista;

typedef struct{
    int tamanho_atual;
    Lista *dados[MAX_SIZE];
} PilhaListas;

Lista *criar_lista(){
    Lista *nova_lista = (Lista *)malloc(sizeof(Lista));
    nova_lista->tamanho_atual = 0;
    return nova_lista;
}

PilhaListas *criar_pilha_de_listas(){
    PilhaListas *nova_pilha = (PilhaListas *)malloc(sizeof(PilhaListas));
    nova_pilha->tamanho_atual = 0;
    return nova_pilha;
}

void inserir_lista(Lista *lista, int dado){
    if (lista->tamanho_atual == MAX_SIZE) printf("List overflow\n");
    else lista->dados[lista->tamanho_atual++] = dado;
}

void inserir_pilha(PilhaListas *pilha, Lista *lista){
    if (pilha->tamanho_atual == MAX_SIZE) printf("Stack overflow for pilha de listas\n");
    else pilha->dados[pilha->tamanho_atual++] = lista;
}

int remover_lista(Lista *lista){
    if (lista->tamanho_atual == 0){
        printf("List underflow\n");
        return -1;
    }
    else{
        return lista->dados[--lista->tamanho_atual];
    }
}

Lista *remover_pilha(PilhaListas *pilha){
    if (pilha->tamanho_atual == 0) return NULL;
    else return pilha->dados[--pilha->tamanho_atual];
}

int topo_lista(Lista *lista){
    if (lista->tamanho_atual == 0){
        printf("List underflow\n");
        return -1;
    }
    else{
        return lista->dados[lista->tamanho_atual - 1];
    }
}

void imprimir_lista(Lista *lista){
    if (lista == NULL){
        printf("EMPTY STACK\n");
        return;
    }
    for (int i = 0; i < lista->tamanho_atual; i++){
        printf("%d", lista->dados[i]);
        if (i + 1 != lista->tamanho_atual){
            printf(" ");
        }
    }
    printf("\n");
    return;
}

void entradas(PilhaListas *pilha){
    Lista *nova_lista = criar_lista();
    inserir_pilha(pilha, nova_lista);

    int entrada;
    while (scanf("%d", &entrada) == 1){
        inserir_lista(nova_lista, entrada);
    }
}

int main(){
    PilhaListas *pilha = criar_pilha_de_listas();
    char comando[7];
    while (scanf("%s", comando) != EOF){
        if (strcmp(comando, "PUSH") == 0){
            entradas(pilha);
        }
        else if (strcmp(comando, "POP") == 0){
            Lista *lista_para_imprimir = remover_pilha(pilha);
            imprimir_lista(lista_para_imprimir);
            free(lista_para_imprimir);
        }
    }
    for (int i = 0; i < pilha->tamanho_atual; i++){
        free(pilha->dados[i]);
    }
    free(pilha);
    return 0;
}
