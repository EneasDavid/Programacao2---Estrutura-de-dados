#ifndef UTILS_H
#define UTILS_H

#define TAMANHO_ASCII 256

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * Estrutura que representa um nó na árvore de
 * Huffman (que é usado na compressão de dados)
 * ou em uma lista encadeada (para gerenciar
 * nós em uma lista de nós disponíveis) ou em
 * uma fila de prioridade (para organizar nós
 * durante a construção da árvore de Huffman
 * com base na frequência).
 * */
typedef struct no_huffman
{
  char caractere;              // Caractere armazenado no nó
  int frequencia;              // Frequência do caractere
  struct no_huffman *proximo;  // Ponteiro para o próximo nó (usado em listas encadeadas)
  struct no_huffman *esquerda; // Ponteiro para o filho esquerdo na árvore
  struct no_huffman *direita;  // Ponteiro para o filho direito na árvore
} NoHuffman;

/**
 * permitindo que cada caractere tenha
 *  um código binário associado, representando-o
 * de forma eficiente.
 * exemplo:
 * A = dado_objeto{0b00000001, 1}
 * */
typedef struct dadoObjeto
{
  int conteudo; // Armazena os bits do arquivo
  int tamanho;  // Armazena o tamanho do código em bits
} dado_objeto;

int mensagem_inicial();

int e_folha(NoHuffman *no);

void *ponteiro_void(unsigned char byte);

unsigned char recuperar_caracter_ponteiro_void(void *byte);

NoHuffman *criar_no_huffman(char aracter, int frequencia);

void liberar_no_huffman(NoHuffman *no);

void liberar_arvore_huffman(NoHuffman *raiz);

#endif