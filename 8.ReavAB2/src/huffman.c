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
    FILE *arquivo_comprimido = fopen("compress.huff", "wb");

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
    
    int tamanho_extensao = calcular_tamanho_extensao(caminho_arquivo);
    escrever_extensao(arquivo_comprimido, caminho_arquivo, tamanho_extensao);

    fseek(arquivo_para_comprimir, 0, SEEK_SET);

    gravarCodigos(arquivo_comprimido, arquivo_para_comprimir, tabela, tamanho_lixo);

    fclose(arquivo_para_comprimir);
    fclose(arquivo_comprimido);
}

// Função para descomprimir o arquivo
void descomprimir(char *caminho_arquivo_comprimido)
{
    // Abre o arquivo comprimido para leitura binária
    FILE *arquivo_comprimido = fopen(caminho_arquivo_comprimido, "rb");
    if (!arquivo_comprimido) {
        perror("Erro ao abrir o arquivo comprimido");
        return;
    }

    // Obtém as informações do cabeçalho do arquivo comprimido
    short int lixo = obter_lixo(arquivo_comprimido);
    short int tamanho_arvore = obter_tamanho_arvore(arquivo_comprimido);
    // Reconstrói a árvore de Huffman a partir do arquivo comprimido
    NoHuffman *arvore_huffman = reconstruir_arvore_huffman(arquivo_comprimido, &tamanho_arvore);

    // Obtém a extensão original do arquivo comprimido
    int tamanho_extensao = obter_tamanho_extensao(arquivo_comprimido);
    unsigned char extensao[7] = {0}; // Suporte para até 6 caracteres de extensão
    
    // Lê a extensão do arquivo
    obter_extensao(arquivo_comprimido, &tamanho_extensao, extensao);

    // Define o nome do arquivo descomprimido com base na extensão
    char caminho_arquivo_descomprimido[100] = "out";
    if (tamanho_extensao > 0) {
        strcat(caminho_arquivo_descomprimido, ".");
        strncat(caminho_arquivo_descomprimido, (char*)extensao, tamanho_extensao);
    }
    // Calcula o tamanho do arquivo comprimido excluindo a árvore e o lixo
    unsigned long long int tamanho_arq_comprimido_sem_arvore_sem_lixo_sem_extensao = obterTamanhoCompressao(arquivo_comprimido);

    tamanho_arq_comprimido_sem_arvore_sem_lixo_sem_extensao-= (2 + tamanho_arvore);
    tamanho_arq_comprimido_sem_arvore_sem_lixo_sem_extensao-= (tamanho_extensao + 1);
 
    // Abre o arquivo descomprimido para escrita binária
    FILE *arquivo_descomprimido = fopen(caminho_arquivo_descomprimido, "wb");
    if (!arquivo_descomprimido) {
        perror("Erro ao criar o arquivo descomprimido");
        fclose(arquivo_comprimido);
        return;
    }

    // Descomprime o arquivo usando a árvore de Huffman reconstruída
    descomprimir_arquivo_usando_huffman(
        arquivo_comprimido,
        lixo,
        tamanho_arq_comprimido_sem_arvore_sem_lixo_sem_extensao,
        arvore_huffman,
        arquivo_descomprimido
    );

    // Fecha os arquivos
    fclose(arquivo_comprimido);
    fclose(arquivo_descomprimido);
}