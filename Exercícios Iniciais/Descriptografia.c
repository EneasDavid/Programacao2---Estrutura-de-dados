#include <stdio.h>
#include <string.h>

#define max_size 100

void descriptografia(char texto[max_size], int tamanho, int posicao) {
    if (posicao>=tamanho) return;
    switch(texto[posicao]){
        case '*':
            printf("(%d", posicao + 1);
            descriptografia(texto, tamanho, posicao + 1);
            printf(")");
            break;
        case '-':
            printf("%d", posicao + 1);
            descriptografia(texto, tamanho, posicao + 1);
            break;
    }
}

int main() {
    char entrada[max_size]; 
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0'; // Remover o caractere de nova linha, se presente
    descriptografia(entrada, strlen(entrada), 0);
    return 0;
}
