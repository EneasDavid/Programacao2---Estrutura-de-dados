#include "../libs/algoritimo_compressao.h"
#include "../libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Uso interno durante a compressão
int fila_prioridade_vazia(NoHuffman *fila)
{
    return fila == NULL;
}

NoHuffman *inserir_na_fila_prioridade(NoHuffman **fila, int frequencia, char caracter, int *tamanho_atual_lista)
{
    /**
     * O parâmetro tamanho_atual_lista é um ponteiro porque precisa
     * ser atualizado na função que chama essa função.
     */
    NoHuffman *novo_no = criar_no_huffman(caracter, frequencia);
    NoHuffman *atual = *fila; // Ponteiro que percorrerá a fila
    NoHuffman *anter = NULL;  // Ponteiro para o nó anterior

    // Se a fila estiver vazia, insere o novo nó como o primeiro.
    if (*fila == NULL)
    {
        *fila = novo_no;          // Atualiza a cabeça da fila
        novo_no->proximo = NULL;  // O novo nó não aponta para nenhum próximo nó
        (*tamanho_atual_lista)++; // Incrementa o tamanho da lista
        return novo_no;           // Retorna o novo nó
    }

    // Percorre a fila para encontrar a posição correta de inserção.
    while (atual != NULL)
    {
        // Se a frequência do nó atual for maior que a do novo nó, insere o novo nó antes.
        if (atual->frequencia > novo_no->frequencia)
        {
            novo_no->proximo = atual; // O novo nó aponta para o atual
            (*tamanho_atual_lista)++; // Incrementa o tamanho da lista

            // Se há um nó anterior, conecta-o ao novo nó
            if (anter != NULL)
            {
                anter->proximo = novo_no;
            }
            else
            {
                *fila = novo_no; // O novo nó se torna a cabeça da fila
            }
            return novo_no; // Retorna o novo nó inserido
        }
        anter = atual;          // Atualiza o nó anterior
        atual = atual->proximo; // Move para o próximo nó
    }

    // Se chegou até aqui, o novo nó deve ser inserido no final da fila.
    anter->proximo = novo_no; // O nó anterior agora aponta para o novo nó
    novo_no->proximo = NULL;  // O novo nó não aponta para mais nenhum nó
    (*tamanho_atual_lista)++; // Incrementa o tamanho da lista
    return novo_no;           // Retorna o novo nó inserido
}

NoHuffman *remover_da_fila_prioridade(NoHuffman **fila, int *tamanho_atual_lista)
{
    /**
     * O parâmetro tamanho_atual_lista é um ponteiro porque precisa
     * ser atualizado na função que chama essa função.
     */

    // Verifica se a fila de prioridade está vazia. Se estiver, retorna NULL.
    if (fila_prioridade_vazia(*fila))
    {
        return NULL;
    }
    // Armazena o nó que será removido (a cabeça da lista).
    NoHuffman *removido = *fila;

    // Atualiza a cabeça da fila para o próximo nó.
    *fila = (*fila)->proximo;

    // Desconecta o nó removido da lista, definindo seu próximo como NULL.
    removido->proximo = NULL;

    // Decrementa o tamanho da lista, pois um nó foi removido.
    (*tamanho_atual_lista)--;

    // Retorna o nó removido.
    return removido;
}
// Uso interno durante a compressão

// 1º primeira função chamada
NoHuffman *obter_frequencia_caracter(FILE *arquivo, int arr_frequencia[TAMANHO_ASCII], int *tamanho_atual_lista)
{
    /**
     * O parâmetro tamanho_atual_lista é um ponteiro porque precisa
     * ser atualizado na função que chama essa função.
     */

    unsigned char caracter; // Variável para armazenar cada caractere lido do arquivo

    // Lê o arquivo byte a byte até o final
    while (fread(&caracter, sizeof(unsigned char), 1, arquivo))
    {
        // Incrementa a frequência do caractere lido no array de frequências
        arr_frequencia[caracter]++;
    }

    // Inicializa a fila de prioridade que armazenará os nós de Huffman
    NoHuffman *fila_prioridade = NULL;

    // Itera sobre o array de frequências para construir a fila de prioridade
    for (int i = 0; i < TAMANHO_ASCII; i++)
    {
        // Se a frequência do caractere for maior que zero, insere na fila de prioridade
        if (arr_frequencia[i] > 0)
        {
            inserir_na_fila_prioridade(&fila_prioridade, arr_frequencia[i], i, tamanho_atual_lista);
        }
    }

    // Retorna a fila de prioridade com os caracteres e suas frequências
    return fila_prioridade;
}
// 2º segunda função chamada
NoHuffman *construir_arvore_huffman(NoHuffman **fila, int tamanho_atual_lista)
{
    /**
     * O parâmetro tamanho_atual_lista é um ponteiro porque precisa
     * ser atualizado na função que chama essa função.
     */
    NoHuffman *esquerda, *direita, *no_pai;

    // Enquanto houver mais de um nó na fila de prioridade
    while (tamanho_atual_lista > 1)
    {
        // Remove os dois nós com menor frequência da fila
        esquerda = remover_da_fila_prioridade(fila, &tamanho_atual_lista);
        direita = remover_da_fila_prioridade(fila, &tamanho_atual_lista);

        // Combina as frequências dos dois nós removidos
        int frequencia_combinada = esquerda->frequencia + direita->frequencia;

        // Cria um novo nó pai com a frequência combinada
        // O caractere é definido como '*' indicando que é um nó interno
        no_pai = inserir_na_fila_prioridade(fila, frequencia_combinada, '*', &tamanho_atual_lista);

        // Define os nós filho (esquerdo e direito) do nó pai
        no_pai->esquerda = esquerda;
        no_pai->direita = direita;
    }

    // Retorna o nó pai, que agora é a raiz da árvore de Huffman
    return no_pai;
}

// 3º terceira função chamada
void gerar_Nova_Tabela_ASCII_Hufmman(NoHuffman *raiz, dado_objeto table[], dado_objeto codigo_parafolha)
{
    // Verifica se o nó atual é uma folha da árvore
    if (e_folha(raiz))
    {
        // Armazena o código binário associado ao caractere da folha na tabela
        table[recuperar_caracter_ponteiro_void(raiz)] = codigo_parafolha;
        return; // Retorna após armazenar o código para a folha
    }

    // Incrementa o tamanho do código a cada nível da árvore
    codigo_parafolha.tamanho++;

    // Se existe um nó à esquerda, gera o código para o filho esquerdo
    if (raiz->esquerda != NULL)
    {
        dado_objeto esquerdaCode = codigo_parafolha;                          // Cria uma cópia do código atual
        esquerdaCode.conteudo <<= 1;                                          // Adiciona um 0 ao código (movendo para a esquerda)
        gerar_Nova_Tabela_ASCII_Hufmman(raiz->esquerda, table, esquerdaCode); // Chamada recursiva para o filho esquerdo
    }
    // Se existe um nó à direita, gera o código para o filho direito
    if (raiz->direita != NULL)
    {
        dado_objeto direitaCode = codigo_parafolha;                         // Cria uma cópia do código atual
        direitaCode.conteudo = (direitaCode.conteudo << 1) | 1;             // Adiciona um 1 ao código (movendo para a esquerda e adicionando 1)
        gerar_Nova_Tabela_ASCII_Hufmman(raiz->direita, table, direitaCode); // Chamada recursiva para o filho direito
    }
}
// 4º Função chamada
int calcular_tamanho_lixo(int frequencia[], dado_objeto dados[])
{
    long bit_antes = 0;  // Total de bits antes da compressão (considerando 8 bits por caractere)
    long bit_depois = 0; // Total de bits depois da compressão (considerando os tamanhos dos códigos de Huffman)

    // Itera sobre cada possível caractere ASCII
    for (int i = 0; i < TAMANHO_ASCII; i++)
    {
        // Calcula a quantidade total de bits antes da compressão
        // Multiplica a frequência do caractere pelo número de bits em um byte (8 bits)
        bit_antes += frequencia[i] * 8;

        // Calcula a quantidade total de bits após a compressão
        // Multiplica a frequência do caractere pelo tamanho do código Huffman associado a esse caractere
        bit_depois += frequencia[i] * dados[i].tamanho;
    }

    // Retorna a quantidade de "lixo" em bits, que é a diferença entre o total de bits antes e depois da compressão
    // O operador módulo 8 é usado para obter o número de bits que não são múltiplos de 8, ou seja, o lixo
    return (bit_antes - bit_depois) % 8;
}
// 5º Função chamada
int calcular_tamanho_arvore(NoHuffman *no)
{
    if (no == NULL)
    {
        return 0;
    }

    // Verifica se o nó é uma folha especial ('*' ou '\\')
    if (no->esquerda == NULL && no->direita == NULL && (no->caractere == '*' || no->caractere == '\\'))
    {
        return 2; // Retorna 2 para folhas especiais, indicando um tamanho específico
    }

    // Calcula o tamanho da árvore somando 1 para o nó atual e chamando recursivamente
    // a função para as subárvores esquerda e direita
    return 1 + calcular_tamanho_arvore(no->esquerda) + calcular_tamanho_arvore(no->direita);
}
// 6º Função chamada
void escrever_cabecalho_inicial(FILE *arquivo_comprimido, int tamanho_lixo, int tamanho_arvore)
{
    // Declaração de variáveis para armazenar os bits a serem escritos no arquivo
    unsigned char primeiro_bit = 0; // Armazena o primeiro byte a ser gravado
    unsigned char segundo_bit = 0;  // Armazena o segundo byte a ser gravado

    // O tamanho do lixo é deslocado para a esquerda em 5 bits e armazenado no primeiro_bit
    primeiro_bit = primeiro_bit | (tamanho_lixo << 5);

    // O tamanho da árvore é deslocado para a direita em 8 bits (pega os bits mais significativos)
    // e é adicionado ao primeiro_bit
    primeiro_bit = primeiro_bit | (tamanho_arvore >> 8);

    // O segundo byte armazena os 8 bits menos significativos do tamanho da árvore
    segundo_bit = segundo_bit | tamanho_arvore;

    // Escreve o primeiro byte no arquivo comprimido
    fwrite(&primeiro_bit, sizeof(unsigned char), 1, arquivo_comprimido);

    // Escreve o segundo byte no arquivo comprimido
    fwrite(&segundo_bit, sizeof(unsigned char), 1, arquivo_comprimido);
}


int calcular_tamanho_extensao(char *caminho_arquivo) {
    // Localiza o último ponto no caminho do arquivo, que marca o início da extensão
    char *extensao = strrchr(caminho_arquivo, '.');
    long tamanho = 0;
    if (extensao == NULL) {
        fprintf(stderr, "Erro: o arquivo não possui uma extensão.\n");
        return 0;
    }

    // Calcula o tamanho da extensão (sem o ponto)
    int tamanho_extensao = strlen(extensao) - 1;    

    // Verifica se a extensão excede o limite de 6 caracteres
    if (tamanho_extensao > 6) {
        fprintf(stderr, "Erro: a extensão do arquivo não pode ter mais de 6 caracteres.\n");
        return 0;
    }
    tamanho = tamanho | (tamanho_extensao << 5);

    return tamanho;
}


void escrever_extensao(FILE *arquivo_comprimido, char *caminho_arquivo, int tamanho_extensao) {
    // Valida o tamanho da extensão, garantindo que não seja zero ou maior que 6
    if (tamanho_extensao == 0) {
        fprintf(stderr, "Erro: Tamanho da extensão inválido (deve ser entre 1 e 6).\n");
        abort(); // Encerra o programa em caso de erro
    }

    // Obtém a extensão sem o ponto, '+1' move o ponteiro para o início da extensão
    char *extensao = strrchr(caminho_arquivo, '.') + 1;
    
    // Escreve o byte que contém o tamanho da extensão no arquivo
    if (fwrite(&tamanho_extensao, sizeof(unsigned char), 1, arquivo_comprimido) != 1) {
        fprintf(stderr, "Erro ao escrever o byte de extensão no arquivo comprimido.\n");
        abort();
    }

    // Escreve os caracteres da extensão (máximo 6)
    int tamanho_extensao_convertido = tamanho_extensao >> 5; // Desloca o tamanho da extensão para a esquerda para limpar os bits de tamanho
    if(tamanho_extensao_convertido<7){
        for(int i = 0; i < tamanho_extensao_convertido; i++) {
            if (fwrite(&extensao[i], sizeof(unsigned char), 1, arquivo_comprimido) != 1) {
                fprintf(stderr, "Erro ao escrever os caracteres da extensão no arquivo comprimido.\n");
                abort();
            }
        }
    }
}

// 7º quarta função chamada
void escrever_arvore_pre_ordem(FILE *arquivo_comprimido, NoHuffman *preorder)
{
    // Verifica se o nó atual é NULL, se sim, simplesmente retorna (condição de parada)
    if (preorder == NULL)
    {
        return;
    }

    // Verifica se o nó atual é uma folha especial (caracteres especiais)
    if (e_folha(preorder) && (preorder->caractere == '\\' || preorder->caractere == '*'))
    {
        // Se for uma folha especial, escreve o caractere de escape '\\' no arquivo
        unsigned char pica_a_mula = (unsigned char)'\\';
        fwrite(&pica_a_mula, sizeof(unsigned char), 1, arquivo_comprimido);
    }

    // Escreve o caractere do nó atual no arquivo
    unsigned char caractere = (unsigned char)preorder->caractere;
    fwrite(&caractere, sizeof(unsigned char), 1, arquivo_comprimido);

    // Chama recursivamente para o filho à esquerda
    escrever_arvore_pre_ordem(arquivo_comprimido, preorder->esquerda);

    // Chama recursivamente para o filho à direita
    escrever_arvore_pre_ordem(arquivo_comprimido, preorder->direita);
}
// 8º Função chamada
void gravarCodigos(FILE *arquivoComprimido, FILE *arquivoPraComprimir, dado_objeto tabela[], int tamanho_lixo)
{
    /*
     * Função para gravar os códigos Huffman de cada caractere em um arquivo comprimido.
     *
     * Parâmetros:
     * - arquivoComprimido: ponteiro para o arquivo onde os dados comprimidos serão armazenados.
     * - arquivoPraComprimir: ponteiro para o arquivo de entrada a ser comprimido.
     * - tabela: vetor contendo os códigos Huffman para cada caractere.
     * - tamanho_lixo: quantidade de bits adicionais para completar o último byte.
     *
     * A função lê o arquivo de entrada caractere por caractere, busca o código Huffman
     * correspondente na tabela e escreve esse código bit a bit em um acumulador.
     * Quando o acumulador atinge 8 bits (1 byte), ele é escrito no arquivo comprimido.
     * No final do arquivo, caso existam bits restantes, eles são preenchidos com zeros
     * à direita para completar o último byte antes da gravação.
     */

    // Inicializa variáveis para acumular os bits e controlar o tamanho do acumulador
    unsigned char acumulador_bits = 0; // Acumulador para armazenar os bits a serem escritos
    int tamanho_acumulador = 0;        // Contador para rastrear quantos bits estão no acumulador
    int caractere;                     // Variável para armazenar o caractere lido do arquivo de entrada

    // Lê cada caractere do arquivo a ser comprimido até o final do arquivo (EOF)
    while ((caractere = getc(arquivoPraComprimir)) != EOF)
    {
        // Obtém a entrada da tabela de Huffman correspondente ao caractere lido
        dado_objeto index_tabela = tabela[caractere];

        // Percorre os bits do código Huffman do caractere da direita para a esquerda
        for (int i = index_tabela.tamanho - 1; i >= 0; --i)
        {
            // Adiciona o bit atual ao acumulador, deslocando os bits para a esquerda
            // e utilizando uma operação bit a bit para definir o bit mais à direita
            acumulador_bits = (acumulador_bits << 1) | ((index_tabela.conteudo >> i) & 1);
            // >> adciona na cauda
            // << adciona na cabeça
            tamanho_acumulador++; // Incrementa o contador de bits no acumulador

            // Verifica se o acumulador está cheio (8 bits)
            if (tamanho_acumulador == 8)
            {
                // Escreve o byte acumulado no arquivo comprimido
                fwrite(&acumulador_bits, sizeof(unsigned char), 1, arquivoComprimido);
                acumulador_bits = 0;    // Reseta o acumulador para novos bits
                tamanho_acumulador = 0; // Reseta o contador de bits
            }
        }
    }

    // Após a leitura, se ainda houver bits no acumulador, os escreve no arquivo comprimido
    if (tamanho_acumulador > 0)
    {
        // Desloca os bits restantes para a esquerda para completar o byte
        acumulador_bits <<= tamanho_lixo;                                      // Preenche os bits restantes com zeros
        fwrite(&acumulador_bits, sizeof(unsigned char), 1, arquivoComprimido); // Escreve o último byte no arquivo
    }
}