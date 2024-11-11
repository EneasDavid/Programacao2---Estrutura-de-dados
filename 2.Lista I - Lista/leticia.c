#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista_seq {
    int ddtp;
    struct lista_seq* proximo;
} lista_seq;

void ordfim(lista_seq **inc, int vlr) {
    lista_seq* novapos = (lista_seq*)malloc(sizeof(lista_seq));
    novapos->ddtp = vlr;
    novapos->proximo = NULL;
    if (*inc == NULL) { 
        *inc = novapos;
        return;
    }
    lista_seq* k = *inc;
    while (k->proximo != NULL) {
        k = k->proximo;
    }
    k->proximo = novapos;
}

void maiorseq(lista_seq* inc) {
    int comeco=-1, fim=-1; // fim-comeco
    int comeco_n=-1, fim_n=-1; // fim_n-comeco_n
    int posicao=0;

    lista_seq* atual=inc;

    while (atual!=NULL){
        if(!atual->ddtp){
            if(comeco_n==-1){
                comeco_n=posicao;
            }
            fim_n=posicao;
        }else{
            if(comeco_n!=-1 && (fim-comeco<fim_n-comeco_n)){
                comeco=comeco_n;
                fim=fim_n;
            }
            comeco_n=-1;
        }

        if (atual->proximo!=NULL) posicao++;
        atual=atual->proximo;
    }

    if(comeco!=-1) printf("%d %d\n", comeco, fim);
    else printf("%d %d\n", posicao, posicao);
}

void liberarFila(lista_seq **lista){
    while(*lista!=NULL) {
        lista_seq *temporaria=*lista;
        *lista=temporaria->proximo;
        free(temporaria);
    }
}

int main() {
    lista_seq* inc = NULL;
    char sequencia[100];

    //a condição de parada é quando entrar um 0 sozinho
    while(scanf(" %s", sequencia) && strcmp(sequencia,"0")!=0){
        for (int i = 0; sequencia[i] != '\0'; i++) {
            ordfim(&inc, sequencia[i] - '0');
        }
        maiorseq(inc);
        liberarFila(&inc);
    }
    
    return 0;
}
