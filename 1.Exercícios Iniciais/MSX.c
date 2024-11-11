#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void converteMaiuscula(char *linha){
    while(*linha){
        printf("%c", toupper(*linha));
        linha++;
    }
}

int main(){
    char *linhas = NULL;
    size_t tamanhoLinha = 0;
    while (1) {
        ssize_t entrada = getline(&linhas, &tamanhoLinha, stdin);
        if (strcmp(linhas, "the end!\n")==0) break;
        linhas[strcspn(linhas, "\n")] = '\0';
        converteMaiuscula(linhas);
        printf("\n"); 
    }
    free(linhas);
    return 0;
}
