#include <stdio.h>

void calculo(int posicao, int entrada, int resultado){
    if(entrada==0){
       printf("%d\n",resultado);
       return;
    }
    int digitoVez=entrada%10;
    int multiplicador=digitoVez%2==0?2:3;
    resultado+=digitoVez*multiplicador*posicao;
    calculo(posicao+1, entrada/10,resultado);
}

int main(){
    int entrada;
    do{
        scanf("%d", &entrada);
        if(entrada>0) calculo(1, entrada, 0);
    }while(entrada!=0);
    return 0;
}
/*
Digito par - multiplica por 2
Digito impar - multiplica por 3

deve-se também multiplicá-lo pela posição do dígito, onde o dígito da 
unidade corresponde ao valor 1, a dezena ao valor 2, centena 3, e assim por diante.

Formato de entrada

Cada caso de teste consiste de um número inteiro.

A entrada termina quando o número dado for igual a 0.

Formato de saída

Para cada caso de teste, imprima em uma única linha o valor da função.
*/