#include "../libs/algoritimo_descompressao.h"
#include "../libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Uso interno durante a descompressão
unsigned int bit_ta_ativo(unsigned char caracter, int i)
{
    // Cria uma máscara que tem um único bit definido em 1 na posição i
    unsigned char mascara = (1 << i);

    // Retorna o resultado da operação AND bit a bit entre o caracter e a máscara.
    // Se o bit na posição i do caracter estiver ativo (1), a operação resultará em um valor diferente de zero.
    // Caso contrário, retornará zero.
    return caracter & mascara;

    /**
     *  Exemplo:
     * caracter = 0b10101010
     * i = 3
     * mascara = 0b00001000
     * caracter & mascara = 0b00001000
     * Retorna 1
     * */
}
// Uso interno durante a descompressão

// 1º Função chamada
short int obter_lixo(FILE *arquivoCompactado)
{
    // Verifica se o arquivo foi aberto corretamente
    if (arquivoCompactado == NULL)
        return -1; // Retorna -1 para indicar erro ao abrir o arquivo

    unsigned char byte_lido;

    // Lê o primeiro byte do arquivo compactado
    fread(&byte_lido, sizeof(unsigned char), 1, arquivoCompactado);

    // Verifica se a leitura foi bem-sucedida
    if (!byte_lido)
    {
        printf("Erro ao ler o arquivo\n");
        return 0; // Retorna 0 em caso de erro na leitura
    }

    // Extrai os 3 bits mais significativos do byte lido, que representam o valor de "lixo"
    int lixo = byte_lido & 0b11100000; // Aplica a máscara para isolar os 3 bits mais à esquerda

    // Desloca esses bits para a direita, alinhando-os no início do número
    lixo = lixo >> 5;

    // Reposiciona o cursor no início do arquivo, caso outras leituras sejam necessárias
    fseek(arquivoCompactado, 0, SEEK_SET);

    return lixo; // Retorna o valor do "lixo", que indica a quantidade de bits extra no último byte

    /**
     * Exemplo:
     * byte_lido = 0b10101010
     * lixo = 0b10100000
     * lixo >> 5 = 0b00000101
     * Retorna 5
     * */
}
// 2º Função chamada
short int obter_tamanho_arvore(FILE *arquivoCompactado)
{
    // Verifica se o arquivo foi aberto corretamente
    if (arquivoCompactado == NULL)
        return -1; // Retorna -1 para indicar erro ao abrir o arquivo

    unsigned char primeiro_byte_lido, segundo_byte_lido;

    // Lê os dois primeiros bytes do arquivo compactado
    fread(&primeiro_byte_lido, sizeof(unsigned char), 1, arquivoCompactado);
    fread(&segundo_byte_lido, sizeof(unsigned char), 1, arquivoCompactado);

    // Limpa os 3 bits mais à esquerda do primeiro byte, que contêm o valor do "lixo"
    primeiro_byte_lido &= 0b00011111; // Aplica a máscara para manter apenas os 5 bits menos significativos

    // Combina os dois bytes para formar o tamanho da árvore
    short int tamanho_arvore = (primeiro_byte_lido << 8) | segundo_byte_lido;

    return tamanho_arvore; // Retorna o tamanho da árvore
}

// 3º Função chamada
unsigned long long int obterTamanhoCompressao(FILE *arquivo)
{
    // Armazena a posição atual do ponteiro do arquivo
    unsigned long long int posicaoAtual = ftell(arquivo);

    // Move o ponteiro do arquivo para o final para obter o tamanho total do arquivo
    fseek(arquivo, 0, SEEK_END);

    // Obtém a posição atual do ponteiro do arquivo, que agora indica o tamanho total em bytes
    unsigned long long int tamanho = ftell(arquivo);

    // Retorna o ponteiro do arquivo para a posição original para não afetar outras operações
    fseek(arquivo, posicaoAtual, SEEK_SET);
    // fseek
    //  Retorna o tamanho do arquivo em bytes
    return tamanho;
    /**
     * Exemplo:
     * Se o arquivo tem 100 bytes, a função retornará 100.
     * */
}
// Função para calcular o tamanho da extensão de um arquivo a partir do caminho do arquivo

int obter_tamanho_extensao(FILE *arquivoCompactado)
{
    // Verifica se o arquivo foi aberto corretamente
    if (arquivoCompactado == NULL)
        return -1; // Retorna -1 para indicar erro ao abrir o arquivo

    unsigned char byte_lido;

    // Lê o primeiro byte do arquivo compactado
    fread(&byte_lido, sizeof(unsigned char), 1, arquivoCompactado);

    // Os 3 primeiros bits representam o tamanho da extensão (no máximo 6)
    int tamanho_extensao = byte_lido >> 5; // Desloca os bits para a direita para alinhar o valor

    // Verifica se o valor extraído é válido
    if (tamanho_extensao > 6)
    {
        fprintf(stderr, "Erro: a extensão do arquivo não pode ter mais de 6 caracteres.\n");
        return 0;
    }

    return tamanho_extensao;
}
void obter_extensao(FILE *arquivoCompactado, int *tamanho_extensao, unsigned char *extensao)
{
    // Verifica se o arquivo foi aberto corretamente
    if (arquivoCompactado == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return;
    }

    // Verifica se o tamanho da extensão é válido
    if (*tamanho_extensao > 6 || *tamanho_extensao <= 0)
    {
        fprintf(stderr, "Erro: Tamanho da extensão inválido: %d\n", *tamanho_extensao);
        return;
    }

    unsigned char byte_lido = 0;

    // Lê os bytes da extensão do arquivo
    for (int i = 0; i < *tamanho_extensao; i++)
    {
        size_t bytes_lidos = fread(&byte_lido, sizeof(unsigned char), 1, arquivoCompactado);
        if (bytes_lidos != 1)
        {
            fprintf(stderr, "Erro ao ler o byte %d da extensão\n", i);
            return;
        }
        extensao[i] = byte_lido;
    }

    extensao[*tamanho_extensao] = '\0'; // Garante que a string tenha o terminador nulo
}

// 4º Função chamada
NoHuffman *reconstruir_arvore_huffman(FILE *arquivoCompactado, short int *tamanho_arvore)
{
    // Declaração de uma variável para armazenar cada byte lido e um ponteiro para o novo nó
    unsigned char byte_lido;
    NoHuffman *no = NULL;

    // Continua reconstruindo a árvore enquanto ainda houver partes para ler
    while (*tamanho_arvore)
    {
        // Lê um byte do arquivo compactado
        fread(&byte_lido, sizeof(unsigned char), 1, arquivoCompactado);

        // Verifica se o byte lido é o caractere de escape '\\'
        if (byte_lido == '\\')
        {
            // Decrementa o tamanho da árvore para contabilizar o caractere de escape
            (*tamanho_arvore)--;

            // Lê o próximo byte, que representa um caractere literal da árvore original
            fread(&byte_lido, sizeof(unsigned char), 1, arquivoCompactado);

            // Cria um nó com o caractere lido e frequência zero (a frequência não é necessária na reconstrução)
            no = criar_no_huffman(byte_lido, 0);

            // Decrementa novamente o tamanho da árvore para contabilizar o caractere armazenado no nó
            (*tamanho_arvore)--;

            // Retorna o nó com o caractere literal armazenado
            return no;
        }

        // Cria um nó com o byte lido e frequência zero
        no = criar_no_huffman(byte_lido, 0);

        // Decrementa o tamanho da árvore, pois mais um caractere foi lido
        (*tamanho_arvore)--;

        // Verifica se o byte representa um nó interno (indicado por '*')
        if (byte_lido == '*')
        {
            // Chama recursivamente para construir o nó esquerdo e o nó direito
            no->esquerda = reconstruir_arvore_huffman(arquivoCompactado, tamanho_arvore);
            no->direita = reconstruir_arvore_huffman(arquivoCompactado, tamanho_arvore);
        }

        // Retorna o nó criado, que pode ser um nó folha ou um nó interno com filhos
        return no;
    }
    // Retorna NULL se não houver mais partes para processar
    return NULL;
    /**
     * Exemplo:
     * Se o arquivo compactado contém a árvore "a*(b*c)", os bytes seriam:
     * 0x61 (a), 0x2A (*), 0x28 (abertura de parênteses), 0x62 (b), 0x2A (*), 0x63 (c), 0x29 (fechamento de parênteses)
     * O caractere '*' é usado para representar um nó interno e '\\' é usado como caractere de escape.
     * A árvore é reconstruída recursivamente, lendo cada byte e criando nós folha ou internos conforme necessário.
     *
     */
}
// 5º Função chamada
void descomprimir_arquivo_usando_huffman(FILE *arquivo_comprimido, int tamanho_lixo, int tamanho_arq_comprimido_sem_arvore_sem_lixo, NoHuffman *arvore_huffman, FILE *arquivo_descomprimido)
{
    unsigned char byte_lido;                                                                     // Armazena o byte atual lido do arquivo comprimido
    NoHuffman *atual = arvore_huffman;                                                           // Ponteiro que percorre a árvore, começando pela raiz
    int bits_para_processamento = tamanho_arq_comprimido_sem_arvore_sem_lixo * 8 - tamanho_lixo; // Total de bits úteis para processamento, excluindo os bits de lixo
    int bits_lidos = 0;                                                                          // Controla a posição atual no byte
    // Loop para percorrer cada bit dos dados comprimidos até o limite de bits úteis
    for (int bitIndexGeral = 0; bitIndexGeral < bits_para_processamento; bitIndexGeral++)
    {
        // Lê um novo byte do arquivo se estiver no início de um novo grupo de 8 bits
        if (bitIndexGeral % 8 == 0)
            fread(&byte_lido, sizeof(unsigned char), 1, arquivo_comprimido);

        // Calcula a posição do bit atual dentro do byte
        bits_lidos = 7 - (bitIndexGeral % 8);

        // Verifica o bit específico de acordo com a função `bit_ta_ativo`
        if (bit_ta_ativo(byte_lido, bits_lidos))
            atual = atual->direita; // Bit 1: percorre o nó direito da árvore
        else
            atual = atual->esquerda; // Bit 0: percorre o nó esquerdo da árvore

        // Quando atinge um nó folha, escreve o caractere no arquivo descomprimido
        if (e_folha(atual))
        {
            fwrite(&atual->caractere, sizeof(unsigned char), 1, arquivo_descomprimido);
            atual = arvore_huffman; // Volta para a raiz para o próximo caractere
        }
    }
    /**
     * Exemplo:
     * Se o arquivo comprimido contém 10 bytes de dados, o tamanho do lixo é 3 e o tamanho da árvore é 2 bytes.
     * O total de bits úteis para processamento é (10 * 8) - 3 = 77 bits.
     * O loop processará cada um dos 77 bits, lendo um novo byte do arquivo a cada 8 bits.
     */
}