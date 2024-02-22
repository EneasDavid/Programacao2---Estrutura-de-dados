#include <stdio.h>
int raizDigital(int valor){
    valor=valor<10?valor:valor%10+raizDigital(valor/10);
    if(valor>=10) return raizDigital(valor);
    else return valor;
}
int saidaRaizDigital(int qtn, int valor) {
    if(qtn==1) return valor;
    int valorVerifica, numeroDaRaiz=9, contador=1;
    while(contador<qtn){
        numeroDaRaiz++;
        if(raizDigital(numeroDaRaiz)==valor){
            contador++;
        }
    }
    return numeroDaRaiz;
}

int main(){
    int qtnRepeticao, qtnVez, entrada;
    scanf("%d", &qtnRepeticao);
    for(int i=0; i<qtnRepeticao;i++){
        scanf("%d%d", &qtnVez, &entrada);
        printf("%d\n",saidaRaizDigital(qtnVez,entrada));
    }
    return 0;
}