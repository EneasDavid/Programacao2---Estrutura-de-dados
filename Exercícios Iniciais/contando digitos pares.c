#include <stdio.h>
int ContaDigitosPares(int entrada){
    if (entrada == 0) {
        return 0;
    }
    int ultimoDigito=entrada%10;
    return ultimoDigito%2==0?1+ContaDigitosPares(entrada/10):ContaDigitosPares(entrada/10);
}
int main() {
    int digito;
    scanf("%d", &digito);
    printf("%d",ContaDigitosPares(digito));
	return 0;
}