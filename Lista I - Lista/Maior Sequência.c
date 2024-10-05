#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_size 100

typedef struct lista_encadeada{
    int valor;
    struct lista_encadeada *proximo;
}listaEncadeada;

void enqueue(listaEncadeada **lE, int valor){
    listaEncadeada *listaNova=malloc(sizeof(listaEncadeada));
    listaNova->valor=valor;
    listaNova->proximo=NULL;

    if(*lE==NULL){
        *lE=listaNova;
    }else{
        listaEncadeada *temporaria=*lE;
        while(temporaria->proximo!=NULL) {
            temporaria=temporaria->proximo;
        }
        temporaria->proximo=listaNova;
    }
}

void imprimir(listaEncadeada *lE){
    while(lE!=NULL){
        printf("%d ", lE->valor);
        lE=lE->proximo;
    }
}

void liberar(listaEncadeada **lista){
    while(*lista!=NULL) {
        listaEncadeada *temporaria=*lista;
        *lista=temporaria->proximo;
        free(temporaria);
    }
}

void encontrarMaiorSequenciaDeZeros(listaEncadeada *lE) {
    int maiorInicio=-1, maiorFim=-1, inicioAtual=-1, fimAtual=-1, posicao = 0;
    while(lE!=NULL){
        //printf("%d\n",lE->valor);
        if(lE->valor==0){
            if(inicioAtual==-1){
                inicioAtual=posicao;
            }
            fimAtual=posicao;
        }else{
            if(inicioAtual!=-1 && (fimAtual-inicioAtual)>(maiorFim-maiorInicio)){
                maiorInicio= inicioAtual;
                maiorFim=fimAtual;
            }
            inicioAtual=-1;
        }
        if(lE->proximo!=NULL) posicao++;
        lE=lE->proximo;
    }
    // Verificar a última sequência
    if(inicioAtual!=-1 && (fimAtual-inicioAtual)>(maiorFim-maiorInicio)){
        maiorInicio=inicioAtual;
        maiorFim=fimAtual;
    }
    if(maiorInicio!=-1) printf("%d %d\n", maiorInicio, maiorFim);
    else printf("%d %d\n", posicao, posicao);
}

int main(){
    listaEncadeada *lista=NULL;
    char entrada[max_size];
    while(scanf("%s", entrada) && strcmp(entrada, "0")!=0){
        for(int i=0; i<strlen(entrada); i++){
            enqueue(&lista, entrada[i]-'0');
        }
        encontrarMaiorSequenciaDeZeros(lista);
        // Libere a memória no final
        liberar(&lista);
    }
    return 0;
}
