#include <stdio.h>
#include <stdlib.h>

typedef struct letra{
    char letra;
    int frequencia;
    struct letra *proximo;
}Letra;
//Usando enqueue_at_middle da revisão
void enqueue(Letra **letra, char valor){
    Letra *novoCaracter=malloc(sizeof(Letra));
    novoCaracter->letra=valor;
    novoCaracter->frequencia=1;
    novoCaracter->proximo=NULL;
    if(*letra==NULL){
        *letra=novoCaracter;
    }else{
        Letra *temporario=*letra;
        while (temporario->proximo != NULL && temporario->letra != valor) {
            temporario = temporario->proximo;
        }
        if(temporario->letra==valor){
            temporario->frequencia+=1;
        }else{
            temporario->proximo=novoCaracter;
        }
    }
}
void imprimir(Letra *letra){
    if(letra==NULL) return ;
    printf("%c %d\n", letra->letra, letra->frequencia);
    imprimir(letra->proximo);
}
int main(){
    Letra *letra=NULL;
    char entrada;
    while ((entrada = getchar()) != '\n') {
        enqueue(&letra, entrada);
    }
    imprimir(letra);
    free(letra);
    return 0;
}