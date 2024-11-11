#include <stdio.h>
#include <stdlib.h>

#define max_length 1000

void inverterLinhas(char **pagina, int inicio, int fim) {
    if (inicio <= fim) {
        char *temp = pagina[inicio];
        pagina[inicio] = pagina[fim];
        pagina[fim] = temp;
        inverterLinhas(pagina, inicio+1, fim-1);
    }
}

int main() {
    char *pagina[max_length];
    char linha[max_length];
    int num_linhas = 0;

    while (fgets(linha, max_length, stdin) != NULL) {
        pagina[num_linhas] = malloc((strlen(linha) + 1) * sizeof(char));
        strcpy(pagina[num_linhas], linha);
        num_linhas++;
    }

    inverterLinhas(pagina, 0, num_linhas - 1);

    for (int i = 0; i < num_linhas; i++) {
        printf("%s", pagina[i]);
        if(i==0) printf("\n");
        free(pagina[i]);
    }

    return 0;
}
