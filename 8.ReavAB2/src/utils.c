#include <stdio.h>
#include <stdlib.h>
#include "../libs/utils.h"

// Função que exibe a mensagem inicial e obtém a escolha do usuário
int mensagem_inicial()
{
    // Exibe as opções para o usuário
    puts("0 - Encerrar\n");
    puts("1 - Comprimir\n");
    puts("2 - Descomprimir\n");

    int escolha;           // Variável para armazenar a escolha do usuário
    scanf("%d", &escolha); // Lê a escolha do usuário
    return escolha;        // Retorna a escolha
}

// Função que aloca memória para um byte e retorna um ponteiro genérico (void)
void *ponteiro_void(unsigned char byte)
{
    // Aloca memória para um ponteiro de byte
    unsigned char *ponteiro = malloc(sizeof(unsigned char));
    *ponteiro = byte;        // Atribui o byte à memória alocada
    return (void *)ponteiro; // Retorna o ponteiro como void
}

// Função que recupera um caractere a partir de um ponteiro genérico
unsigned char recuperar_caracter_ponteiro_void(void *caracter)
{
    // Converte o ponteiro void para um ponteiro para NoHuffman e recupera o caractere
    return ((NoHuffman *)caracter)->caractere;
}

// Função que verifica se um nó é uma folha
int e_folha(NoHuffman *no)
{
    // Retorna 1 (verdadeiro) se o nó não tem filhos, caso contrário retorna 0 (falso)
    return no->esquerda == NULL && no->direita == NULL;
}

// Função que cria um novo nó de Huffman
NoHuffman *criar_no_huffman(char caracter, int frequencia)
{
    NoHuffman *novo_no = (NoHuffman *)malloc(sizeof(NoHuffman));

    novo_no->frequencia = frequencia;

    // Atribui o caractere ao nó usando a função ponteiro_void
    novo_no->caractere = *((char *)ponteiro_void(caracter));
    /*
     * pela instancia ser inicialmente uma fila de prioridade
     * os dados abaixo são nulos, automaticamente, que depois
     * podem vir a serem preenchidos
     */
    novo_no->proximo = NULL;  // Inicializa o ponteiro para o próximo nó como NULL
    novo_no->esquerda = NULL; // Inicializa o ponteiro para o filho esquerdo como NULL
    novo_no->direita = NULL;  // Inicializa o ponteiro para o filho direito como NULL

    return novo_no; // Retorna o novo nó de Huffman criado
}

// Função para liberar memória de NoHuffman depois dos testes unitários
void liberar_no_huffman(NoHuffman *no)
{
    if (no)
    {
        liberar_no_huffman(no->esquerda);
        liberar_no_huffman(no->direita);
        free(no);
    }
}

// Função para liberar memória da árvore depois dos testes unitários
void liberar_arvore_huffman(NoHuffman *raiz)
{
    if (raiz != NULL)
    {
        liberar_arvore_huffman(raiz->esquerda); // Libera a subárvore esquerda
        liberar_arvore_huffman(raiz->direita);  // Libera a subárvore direita
        free(raiz);                             // Libera o nó atual
    }
}


void imprimir_binario(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);  // Imprime cada bit do byte
    }
}