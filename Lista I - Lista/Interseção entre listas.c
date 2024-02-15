#include <stdio.h>
#include <stdlib.h>

void preenncherArray(int entrada[]){
    for(int i=0;i<20;i++){
        scanf("%d", &entrada[i]);
    }
}
int semelhancaEntreArray(int valor, int arrayDois[], int tamanhoLista){
    for(int i=0;i<tamanhoLista;i++){
        if(valor==arrayDois[i]) return 1;
    }
    return 0;
}
void ordenaArray(int array[], int tamanho){
        for(int d=0;d<tamanho-1;d++){
        if(array[d]>array[d+1]){
            int valorTemp=array[d+1];
            array[d+1]=array[d];
            array[d]=array;
        }
    }
}
int main(){
    int primeiraLista[20], segundaLista[20], *listaMesclada, tamanhoLista=0;;
    preenncherArray(primeiraLista);
    preenncherArray(segundaLista);
    for(int i=0; i<20;i++){
        for(int d=0; d<20;d++){
            if(primeiraLista[i]==segundaLista[d]){
                if(!semelhancaEntreArray(primeiraLista[i], listaMesclada, tamanhoLista)){
                    tamanhoLista++;
                    listaMesclada=(int *)realloc(listaMesclada, tamanhoLista * sizeof(int));
                    listaMesclada[tamanhoLista-1]=primeiraLista[i];
                }
            }
        }
    }
    if(tamanhoLista==0) printf("VAZIO");
    else{
        ordenaArray(listaMesclada, tamanhoLista);
        for (int i = 0; i < tamanhoLista; i++) {
            printf("%d\n", listaMesclada[i]);
        }
    }
    free(listaMesclada);
    return 0;
}