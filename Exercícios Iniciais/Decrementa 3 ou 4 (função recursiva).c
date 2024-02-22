#include <stdio.h>
int resultado(int entrada, int verificarEsquerda){
    if(verificarEsquerda/10==0){
        return verificarEsquerda%2==0?entrada-4:entrada-3;
    }
    resultado(entrada, verificarEsquerda/10);
}

int main(){
    int entrada;
    scanf("%d", &entrada);
    printf("%d",resultado(entrada, entrada));
    return 0;
}