#include <stdio.h>

int acharMatriz(int tamanho, int linha, int coluna, int quadrante) {
    if(tamanho==1) {
        return 0;
    }
    if(linha<tamanho/2){
        if(coluna>=tamanho/2){
            quadrante=1;
        }else{
            quadrante=2;
        }
    }else if(coluna>tamanho/2){
        quadrante=4;
    }else{
        quadrante=4;
    }

    if(quadrante==1){
        tamanho/=2;
    }else if(quadrante==2){
        tamanho/=2;
        coluna-=tamanho;
    }else if(quadrante==3){
        tamanho/=2;
        linha-=tamanho;
    }else if(quadrante==4){
        tamanho/=2;
        linha-=tamanho;
        coluna-=tamanho;
    }
    printf("%d", quadrante);
    return acharMatriz(tamanho, linha, coluna, quadrante);
}
int main() {
    int tamanho, quadrante, linha=0, coluna=0;
    scanf("%d", &tamanho);
    char entrada[tamanho][tamanho];
    for (int i=0;i<tamanho;i++) {
        for (int d=0;d<tamanho;d++) {
            scanf(" %c", &entrada[i][d]);
        }
    }
   for (int i=0;i<tamanho;i++) {
        for (int d=0;d<tamanho;d++) {
            if (entrada[i][d] == '*') {
                linha = i;
                coluna = d;
                break;
            }
        }
    }
    printf("%d",acharMatriz(tamanho, linha,  coluna, quadrante));
    return 0;
}