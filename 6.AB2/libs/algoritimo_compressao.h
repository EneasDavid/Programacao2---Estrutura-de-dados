#ifndef ALGORITMOS_COMPRESSAO_H
#define ALGORITMOS_COMPRESSAO_H

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fila_prioridade_vazia(NoHuffman *fila);

NoHuffman *inserir_na_fila_prioridade(NoHuffman **fila, int frequencia, char caracter, int *tamanho_atual_lista);

NoHuffman *obter_frequencia_caracter(FILE *arquivo, int arr_frequencia[TAMANHO_ASCII], int *tamanho_atual_lista);

NoHuffman *remover_da_fila_prioridade(NoHuffman **fila, int *tamanho_atual_lista);

NoHuffman *construir_arvore_huffman(NoHuffman **fila, int tamanho_atual_lista);

int calcular_tamanho_lixo(int frequencia[], dado_objeto dados[]);

int calcular_tamanho_arvore(NoHuffman *raiz);

void escrever_cabecalho_inicial(FILE *arquivo_comprimido, int tamanho_lixo, int tamanho_arvore);

void escrever_arvore_pre_ordem(FILE *arquivo_comprimido, NoHuffman *preorder);

void gerar_Nova_Tabela_ASCII_Hufmman(NoHuffman *raiz, dado_objeto table[], dado_objeto codigo_parafolha);

void gravarCodigos(FILE *arquivoComprimido, FILE *arquivoPraComprimir, dado_objeto tabela[], int tamanho_lixo);

#endif
