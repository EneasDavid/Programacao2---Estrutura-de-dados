#include "../libs/huffman.h"
#include "../libs/algoritimo_descompressao.h"
#include "../libs/algoritimo_compressao.h"
#include "../libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void comprimir(char *caminho_arquivo)
{
    FILE *arquivo_para_comprimir = fopen(caminho_arquivo, "rb");
    strcat(caminho_arquivo, ".huff");
    FILE *arquivo_comprimido = fopen(caminho_arquivo, "wb");

    NoHuffman *fila_prioridade = NULL;

    if (arquivo_para_comprimir == NULL)
    {
        perror("Erro ao abrir o arquivo");
        abort();
    }

    if (arquivo_comprimido == NULL)
    {
        perror("Erro ao criar o arquivo");
        abort();
    }

    int arr_frequencia[TAMANHO_ASCII] = {0}, tamanho_atual = 0;

    fila_prioridade = obter_frequencia_caracter(arquivo_para_comprimir, arr_frequencia, &tamanho_atual);

    construir_arvore_huffman(&fila_prioridade, tamanho_atual);

    dado_objeto dados_binarios, tabela[TAMANHO_ASCII];

    dados_binarios.conteudo = 0;
    dados_binarios.tamanho = 0;

    memset(tabela, 0, sizeof(dado_objeto) * TAMANHO_ASCII);

    gerar_Nova_Tabela_ASCII_Hufmman(fila_prioridade, tabela, dados_binarios);

    int tamanho_lixo = calcular_tamanho_lixo(arr_frequencia, tabela);
    int tamanho_arvore = calcular_tamanho_arvore(fila_prioridade);
    escrever_cabecalho_inicial(arquivo_comprimido, tamanho_lixo, tamanho_arvore);

    escrever_arvore_pre_ordem(arquivo_comprimido, fila_prioridade);

    fseek(arquivo_para_comprimir, 0, SEEK_SET);

    gravarCodigos(arquivo_comprimido, arquivo_para_comprimir, tabela, tamanho_lixo);

    fclose(arquivo_para_comprimir);
    fclose(arquivo_comprimido);
}

void descomprimir(char *caminho_arquivo_comprimido)
{
    // Declara um array de caracteres para o nome do arquivo descomprimido
    char caminho_arquivo_descomprimido[TAMANHO_ASCII];
    
    // Copia o caminho do arquivo comprimido para caminho_arquivo_descomprimido
    strncpy(caminho_arquivo_descomprimido, caminho_arquivo_comprimido, sizeof(caminho_arquivo_descomprimido) - 1);
    caminho_arquivo_descomprimido[sizeof(caminho_arquivo_descomprimido) - 1] = '\0'; // Garante terminação correta

    // Remove ".huff" do final, se presente
    char *extensao = strstr(caminho_arquivo_descomprimido, ".huff");
    if (extensao && extensao == caminho_arquivo_descomprimido + strlen(caminho_arquivo_descomprimido) - strlen(".huff")) {
        *extensao = '\0';  // Corta a string antes de ".huff"
    }

    // Abre o arquivo comprimido para leitura binária
    FILE *arquivo_comprimido = fopen(caminho_arquivo_comprimido, "rb");
    if (!arquivo_comprimido) {
        printf("Problema ao abrir o arquivo comprimido\n");
        return;
    }

    // Abre o arquivo descomprimido para escrita binária
    FILE *arquivo_descomprimido = fopen(caminho_arquivo_descomprimido, "wb");
    if (!arquivo_descomprimido) {
        printf("Problema ao abrir o arquivo descomprimido\n");
        fclose(arquivo_comprimido);
        return;
    }
    short int lixo = obter_lixo(arquivo_comprimido);
    short int tamanho_arvore = obter_tamanho_arvore(arquivo_comprimido);
    unsigned long long int tamanho_arq_comprimido_sem_arvore_sem_lixo = obterTamanhoCompressao(arquivo_comprimido) - (2 + tamanho_arvore);

    NoHuffman *arvore_huffman = reconstruir_arvore_huffman(arquivo_comprimido, &tamanho_arvore);
    descomprimir_arquivo_usando_huffman(arquivo_comprimido, lixo, tamanho_arq_comprimido_sem_arvore_sem_lixo, arvore_huffman, arquivo_descomprimido);

    fclose(arquivo_comprimido);
    fclose(arquivo_descomprimido);
}
