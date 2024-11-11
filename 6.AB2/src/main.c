#include "../libs/utils.h"
#include "../libs/huffman.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int escolha;
    char caminho[TAMANHO_ASCII];

    do
    {
        escolha = mensagem_inicial();
        if (escolha==0)
        {
            break;
        }
        else if (escolha != 1 && escolha != 2)
        {
            printf("Digite uma escolha válida!\n");
            continue;
        }
        printf("Digite o caminho do arquivo: ");
        scanf("%s", caminho);
        switch (escolha)
        {
        case 1:
            comprimir(caminho);
            break;

        case 2:
            descomprimir(caminho);
            break;

        default:
            printf("Digite uma escolha válida!\n");
            break;
        }
    } while (escolha != 0);

    return 0;
}