#include <stdio.h>
#include <stdlib.h>

#define max_size 10000

void inverterLinhas() {
    char linha[max_size];
    if(fgets(linha, sizeof(linha), stdin)!=NULL){
        inverterLinhas();
    }; 
    printf("%s\n", linha);
}

int main() {
    inverterLinhas();
    return 0;
}
