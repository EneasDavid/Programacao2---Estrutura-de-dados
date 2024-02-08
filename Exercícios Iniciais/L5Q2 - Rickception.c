#include <stdio.h>

int encontro(int ondeT, int vezesR, int laco){
    if(laco<=vezesR){
        if(laco%2>0){
            return encontro(ondeT+3,vezesR,laco+1);
        }else{
            return encontro(ondeT+(ondeT%5),vezesR,laco+1);
        }
    }
    return ondeT;
}

int main() {
    int camada, tempo;
    scanf("%d%d", &camada,&tempo);
    printf("%d", encontro(camada,tempo,1));
	return 0;
}
/*
L� um n�emro
soma mais tr�s a ele, na proxima, soma o resto a divis�o por cinco

camada, tempo

while (tempo--){
    if(tempo%2==0){
        camada+3
    }else{
        camada+(camada%5)
    }
}
printf("%d", camada);
*/