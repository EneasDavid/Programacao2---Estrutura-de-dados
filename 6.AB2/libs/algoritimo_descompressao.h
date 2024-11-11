#ifndef ALGORITMOS_DESCOMPRESAO_H
#define ALGORITMOS_DESCOMPRESAO_H

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int bit_ta_ativo(unsigned char caracter, int i);

short int obter_lixo(FILE *arquivoCompactado);

short int obter_tamanho_arvore(FILE *arquivoCompactado);

unsigned long long int obterTamanhoCompressao(FILE *arquivo);

NoHuffman *reconstruir_arvore_huffman(FILE *arquivoCompactado, short int *tamanho_arvore);

void descomprimir_arquivo_usando_huffman(FILE *arquivo_comprimido, int tamanho_lixo, int tamanho_arq_comprimido_sem_arvore_sem_lixo, NoHuffman *arvore_huffman, FILE *arquivo_descomprimido);

#endif