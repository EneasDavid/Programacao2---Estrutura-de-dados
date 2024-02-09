#include <stdio.h>
int raizDigital(int valor){
    return valor>10?valor%10+raizDigital(valor/10):valor;
}
int saidaRaizDigital(int qtn, int valor){
    if(qtn==1) return valor;
    int contador=1, numeroDaRaiz=10, valorVerifica;
    while(contador<qtn){
        do{
            valorVerifica=raizDigital(numeroDaRaiz);
        }while(valorVerifica>10);
    if(valorVerifica==valor){
          contador++;
          printf("%d\n", numeroDaRaiz);
        } 
        numeroDaRaiz++;
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