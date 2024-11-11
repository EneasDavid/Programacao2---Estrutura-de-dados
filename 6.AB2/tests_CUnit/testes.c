// testes.c
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../libs/utils.h"
#include "../libs/huffman.h"
#include "../libs/algoritimo_descompressao.h"
#include "../libs/algoritimo_compressao.h"

// TESTES LIBS

//*UTILS.H
// Teste da função criar_no_huffman
void test_criar_no_huffman()
{
    NoHuffman *no = criar_no_huffman('A', 5);

    CU_ASSERT(no != NULL);           // Verifica se o nó foi alocado
    CU_ASSERT(no->caractere == 'A'); // Verifica o caractere
    CU_ASSERT(no->frequencia == 5);  // Verifica a frequência
    CU_ASSERT(no->proximo == NULL);  // Verifica se o próximo nó é NULL
    CU_ASSERT(no->esquerda == NULL); // Verifica se o filho esquerdo é NULL
    CU_ASSERT(no->direita == NULL);  // Verifica se o filho direito é NULL

    liberar_no_huffman(no); // Libera a memória alocada
}

// Teste da função criar_dado_objeto
void test_criar_dado_objeto()
{
    dado_objeto obj; // Declarando um objeto

    obj.conteudo = 255; // Atribuindo um valor ao conteúdo
    obj.tamanho = 8;    // Atribuindo um tamanho

    CU_ASSERT(obj.conteudo == 255); // Verifica se o conteúdo está correto
    CU_ASSERT(obj.tamanho == 8);    // Verifica se o tamanho está correto
}

// Teste da função ponteiro_void
void test_ponteiro_void()
{
    unsigned char byte = 42; // Um valor de teste
    unsigned char *ponteiro = (unsigned char *)ponteiro_void(byte);

    CU_ASSERT(ponteiro != NULL);  // Verifica se o ponteiro não é NULL
    CU_ASSERT(*ponteiro == byte); // Verifica se o byte foi armazenado corretamente

    free(ponteiro); // Libera a memória alocada
}

// Teste da função recuperar_caracter_ponteiro_void
void test_recuperar_caracter_ponteiro_void()
{
    NoHuffman *no = criar_no_huffman('B', 3); // Cria um nó com o caractere 'B'

    unsigned char caracter = recuperar_caracter_ponteiro_void(no);

    CU_ASSERT(caracter == 'B'); // Verifica se o caractere recuperado é 'B'

    liberar_no_huffman(no); // Libera a memória do nó
}

// Teste da função e_folha
void test_e_folha()
{
    NoHuffman *no_folha = criar_no_huffman('C', 2);     // Nó folha
    NoHuffman *no_nao_folha = criar_no_huffman('D', 4); // Nó não folha
    no_nao_folha->esquerda = criar_no_huffman('E', 1);  // Adiciona filho para torná-lo não folha

    CU_ASSERT(e_folha(no_folha) == 1);     // Deve retornar 1 (verdadeiro)
    CU_ASSERT(e_folha(no_nao_folha) == 0); // Deve retornar 0 (falso)

    liberar_no_huffman(no_folha);               // Libera a memória do nó folha
    liberar_no_huffman(no_nao_folha->esquerda); // Libera o filho
    liberar_no_huffman(no_nao_folha);           // Libera o nó não folha
}

// TESTES COMPRESSÃO

// Teste da função fila_prioridade_vazia
void test_fila_prioridade_vazia()
{
    NoHuffman *fila_vazia = NULL;    // Fila vazia
    NoHuffman no;                    // Nó não inicializado
    NoHuffman *fila_nao_vazia = &no; // Fila não vazia

    // Teste quando a fila é NULL
    CU_ASSERT(fila_prioridade_vazia(fila_vazia) == 1); // Espera-se que retorne 1 (verdadeiro)

    // Teste quando a fila não é NULL
    CU_ASSERT(fila_prioridade_vazia(fila_nao_vazia) == 0); // Espera-se que retorne 0 (falso)
}

// Teste da função inserir_na_fila_prioridade
void test_inserir_na_fila_prioridade()
{
    NoHuffman *fila = NULL;      // Inicializa a fila como NULL
    int tamanho_atual_lista = 0; // Inicializa o tamanho da lista

    // Insere um nó na fila de prioridade
    NoHuffman *novo_no = inserir_na_fila_prioridade(&fila, 5, 'A', &tamanho_atual_lista);

    CU_ASSERT(novo_no != NULL);           // Verifica se o novo nó foi criado
    CU_ASSERT(novo_no->frequencia == 5);  // Verifica a frequência do novo nó
    CU_ASSERT(novo_no->caractere == 'A'); // Verifica o caractere do novo nó
    CU_ASSERT(tamanho_atual_lista == 1);  // Verifica se o tamanho da lista foi atualizado

    // Insere outro nó com frequência menor
    novo_no = inserir_na_fila_prioridade(&fila, 3, 'B', &tamanho_atual_lista);

    CU_ASSERT(novo_no != NULL);           // Verifica se o novo nó foi criado
    CU_ASSERT(novo_no->frequencia == 3);  // Verifica a frequência do novo nó
    CU_ASSERT(novo_no->caractere == 'B'); // Verifica o caractere do novo nó
    CU_ASSERT(tamanho_atual_lista == 2);  // Verifica se o tamanho da lista foi atualizado

    // Verifica a ordem da fila de prioridade
    CU_ASSERT(fila->caractere == 'B');          // O nó com menor frequência deve ser a cabeça da fila
    CU_ASSERT(fila->proximo->caractere == 'A'); // O próximo nó deve ser 'A'

    // Libera a memória
    while (!fila_prioridade_vazia(fila))
    {
        NoHuffman *removido = remover_da_fila_prioridade(&fila, &tamanho_atual_lista);
        free(removido);
    }
}

// Teste da função remover_da_fila_prioridade
void test_remover_da_fila_prioridade()
{
    NoHuffman *fila = NULL;      // Inicializa a fila como NULL
    int tamanho_atual_lista = 0; // Inicializa o tamanho da lista

    // Insere nós na fila de prioridade
    inserir_na_fila_prioridade(&fila, 5, 'A', &tamanho_atual_lista);
    inserir_na_fila_prioridade(&fila, 3, 'B', &tamanho_atual_lista);

    // Remove um nó da fila
    NoHuffman *removido = remover_da_fila_prioridade(&fila, &tamanho_atual_lista);

    CU_ASSERT(removido != NULL);           // Verifica se um nó foi removido
    CU_ASSERT(removido->caractere == 'B'); // O nó removido deve ser 'B'
    CU_ASSERT(tamanho_atual_lista == 1);   // Verifica se o tamanho da lista foi atualizado

    // Libera a memória do nó removido
    free(removido);

    // Remove o próximo nó
    removido = remover_da_fila_prioridade(&fila, &tamanho_atual_lista);

    CU_ASSERT(removido != NULL);           // Verifica se um nó foi removido
    CU_ASSERT(removido->caractere == 'A'); // O nó removido deve ser 'A'
    CU_ASSERT(tamanho_atual_lista == 0);   // Verifica se o tamanho da lista foi atualizado

    // Libera a memória do nó removido
    free(removido);

    // Tenta remover de uma fila vazia
    removido = remover_da_fila_prioridade(&fila, &tamanho_atual_lista);
    CU_ASSERT(removido == NULL); // Verifica se não há mais nós na fila
}

// Teste da função obter_frequencia_caracter
void test_obter_frequencia_caracter()
{
    // Cria um arquivo temporário para o teste
    FILE *arquivo_teste = fopen("teste.txt", "w");
    // Escreve alguns caracteres no arquivo
    fputs("abacabadabac", arquivo_teste);
    fclose(arquivo_teste);

    // Abre o arquivo para leitura
    arquivo_teste = fopen("teste.txt", "r");
    int arr_frequencia[TAMANHO_ASCII] = {0}; // Inicializa o array de frequências
    int tamanho_atual_lista = 0;             // Inicializa o tamanho da lista

    // Chama a função para obter a frequência dos caracteres
    NoHuffman *fila = obter_frequencia_caracter(arquivo_teste, arr_frequencia, &tamanho_atual_lista);

    // Verifica se as frequências estão corretas
    CU_ASSERT(arr_frequencia['a'] == 5); // 'a' aparece 5 vezes
    CU_ASSERT(arr_frequencia['b'] == 3); // 'b' aparece 3 vezes
    CU_ASSERT(arr_frequencia['c'] == 2); // 'c' aparece 2 vezes
    CU_ASSERT(arr_frequencia['d'] == 2); // 'd' aparece 2 vezes
    CU_ASSERT(arr_frequencia['e'] == 0); // 'e' não aparece

    // Verifica se a fila de prioridade foi criada corretamente
    CU_ASSERT(tamanho_atual_lista > 0); // A lista deve ter pelo menos um nó

    // Libera a memória
    while (!fila_prioridade_vazia(fila))
    {
        NoHuffman *removido = remover_da_fila_prioridade(&fila, &tamanho_atual_lista);
        free(removido);
    }

    // Fecha o arquivo
    fclose(arquivo_teste);
    // Remove o arquivo temporário
    remove("teste.txt");
}

// Teste da função construir_arvore_huffman
void test_construir_arvore_huffman()
{
    NoHuffman *fila = NULL;      // Inicializa a fila como NULL
    int tamanho_atual_lista = 0; // Inicializa o tamanho da lista

    // Insere nós na fila de prioridade manualmente
    inserir_na_fila_prioridade(&fila, 5, 'a', &tamanho_atual_lista);
    inserir_na_fila_prioridade(&fila, 3, 'b', &tamanho_atual_lista);
    inserir_na_fila_prioridade(&fila, 2, 'c', &tamanho_atual_lista);
    inserir_na_fila_prioridade(&fila, 2, 'd', &tamanho_atual_lista);

    // Chama a função para construir a árvore de Huffman
    NoHuffman *raiz = construir_arvore_huffman(&fila, tamanho_atual_lista);

    // Verifica se a raiz da árvore foi criada corretamente
    CU_ASSERT(raiz != NULL);
    CU_ASSERT(raiz->frequencia == 12); // A frequência da raiz deve ser a soma das frequências

    // Verifica se os filhos da raiz estão corretos
    CU_ASSERT(raiz->esquerda != NULL); // Deve haver um nó filho à esquerda
    CU_ASSERT(raiz->direita != NULL);  // Deve haver um nó filho à direita

    // Libera a memória
    free(raiz); // Libera a raiz (e seus filhos, se necessário)
}

// Teste da função gerar_Nova_Tabela_ASCII_Hufmman
void test_gerar_Nova_Tabela_ASCII_Hufmman()
{
    // Cria uma árvore de Huffman manualmente
    NoHuffman *raiz = (NoHuffman *)malloc(sizeof(NoHuffman));
    raiz->caractere = '*';
    raiz->frequencia = 12;

    NoHuffman *folhaA = (NoHuffman *)malloc(sizeof(NoHuffman));
    folhaA->caractere = 'a';
    folhaA->frequencia = 5;
    raiz->esquerda = folhaA;

    NoHuffman *folhaB = (NoHuffman *)malloc(sizeof(NoHuffman));
    folhaB->caractere = 'b';
    folhaB->frequencia = 3;
    raiz->direita = folhaB;

    dado_objeto tabela[TAMANHO_ASCII] = {0}; // Inicializa a tabela
    dado_objeto codigo_inicial = {0, 0};     // Código inicial

    // Chama a função para gerar a nova tabela
    gerar_Nova_Tabela_ASCII_Hufmman(raiz, tabela, codigo_inicial);

    // Verifica se os códigos foram gerados corretamente
    CU_ASSERT(tabela['a'].conteudo == 0b00); // 'a' deve ter código 00
    CU_ASSERT(tabela['b'].conteudo == 0b01); // 'b' deve ter código 01

    // Libera a memória
    free(folhaA);
    free(folhaB);
    free(raiz);
}

// Teste da função calcular_tamanho_lixo
void test_calcular_tamanho_lixo()
{
    // Frequências de teste
    int frequencia[TAMANHO_ASCII] = {0};
    frequencia['a'] = 5;
    frequencia['b'] = 3;

    dado_objeto dados[TAMANHO_ASCII] = {0};
    dados['a'].tamanho = 2; // 'a' tem código de 2 bits
    dados['b'].tamanho = 3; // 'b' tem código de 3 bits

    // Chama a função para calcular o tamanho de lixo
    int lixo = calcular_tamanho_lixo(frequencia, dados);

    // Calcula o total de bits antes e depois da compressão
    long bit_antes = (frequencia['a'] + frequencia['b']) * 8; // 8 bits por caractere
    long bit_depois = (frequencia['a'] * dados['a'].tamanho) + (frequencia['b'] * dados['b'].tamanho);

    // O tamanho de lixo deve ser a diferença entre os dois totais
    CU_ASSERT(lixo == (bit_antes - bit_depois) % 8);
}

// Teste da função calcular_tamanho_arvore
void test_calcular_tamanho_arvore()
{
    // Cria uma árvore de Huffman manualmente
    NoHuffman *raiz = (NoHuffman *)malloc(sizeof(NoHuffman));
    raiz->caractere = '*';
    raiz->frequencia = 12;

    NoHuffman *folhaA = (NoHuffman *)malloc(sizeof(NoHuffman));
    folhaA->caractere = 'a';
    folhaA->frequencia = 5;
    raiz->esquerda = folhaA;

    NoHuffman *folhaB = (NoHuffman *)malloc(sizeof(NoHuffman));
    folhaB->caractere = 'b';
    folhaB->frequencia = 3;
    raiz->direita = folhaB;

    // Chama a função para calcular o tamanho da árvore
    int tamanho = calcular_tamanho_arvore(raiz);

    // Verifica se o tamanho calculado está correto
    CU_ASSERT(tamanho == 3); // Deve haver 3 nós (raiz + folha A + folha B)

    // Libera a memória
    free(folhaA);
    free(folhaB);
    free(raiz);
}

// Teste da função escrever_cabecalho_inicial
void test_escrever_cabecalho_inicial()
{
    FILE *arquivo = fopen("cabecalho_test.bin", "wb"); // Cria um arquivo binário para teste
    int tamanho_lixo = 3;                              // Exemplo de tamanho de lixo
    int tamanho_arvore = 255;                          // Exemplo de tamanho da árvore

    // Chama a função para escrever o cabeçalho
    escrever_cabecalho_inicial(arquivo, tamanho_lixo, tamanho_arvore);
    fclose(arquivo); // Fecha o arquivo

    // Abre o arquivo novamente para leitura
    arquivo = fopen("cabecalho_test.bin", "rb");
    unsigned char primeiro_byte;
    unsigned char segundo_byte;

    // Lê os bytes gravados
    fread(&primeiro_byte, sizeof(unsigned char), 1, arquivo);
    fread(&segundo_byte, sizeof(unsigned char), 1, arquivo);
    fclose(arquivo); // Fecha o arquivo

    // Verifica os valores dos bytes gravados
    CU_ASSERT(primeiro_byte == ((tamanho_lixo << 5) | (tamanho_arvore >> 8))); // Verifica o primeiro byte
    CU_ASSERT(segundo_byte == (tamanho_arvore & 0xFF));                        // Verifica o segundo byte

    // Remove o arquivo de teste
    remove("cabecalho_test.bin");
}

// Teste da função escrever_arvore_pre_ordem
void test_escrever_arvore_pre_ordem()
{
    FILE *arquivo = fopen("arvore_test.bin", "wb"); // Cria um arquivo binário para teste

    // Cria uma árvore de Huffman manualmente
    NoHuffman *raiz = (NoHuffman *)malloc(sizeof(NoHuffman));
    raiz->caractere = '*';
    raiz->frequencia = 12;

    NoHuffman *folhaA = (NoHuffman *)malloc(sizeof(NoHuffman));
    folhaA->caractere = 'a';
    folhaA->frequencia = 5;
    raiz->esquerda = folhaA;

    NoHuffman *folhaB = (NoHuffman *)malloc(sizeof(NoHuffman));
    folhaB->caractere = 'b';
    folhaB->frequencia = 3;
    raiz->direita = folhaB;

    // Chama a função para escrever a árvore
    escrever_arvore_pre_ordem(arquivo, raiz);
    fclose(arquivo); // Fecha o arquivo

    // Abre o arquivo novamente para leitura
    arquivo = fopen("arvore_test.bin", "rb");
    unsigned char caractere;

    // Lê os caracteres gravados e verifica
    fread(&caractere, sizeof(unsigned char), 1, arquivo);
    CU_ASSERT(caractere == '*'); // Verifica o caractere da raiz
    fread(&caractere, sizeof(unsigned char), 1, arquivo);
    CU_ASSERT(caractere == 'a'); // Verifica o caractere da folha A
    fread(&caractere, sizeof(unsigned char), 1, arquivo);
    CU_ASSERT(caractere == 'b'); // Verifica o caractere da folha B
    fclose(arquivo);             // Fecha o arquivo

    // Libera a memória
    free(folhaA);
    free(folhaB);
    free(raiz);

    // Remove o arquivo de teste
    remove("arvore_test.bin");
}

// Teste da função gravarCodigos
void test_gravarCodigos()
{
    FILE *arquivoComprimido = fopen("comprimido_test.bin", "wb"); // Cria um arquivo binário para teste
    FILE *arquivoPraComprimir = fopen("entrada_test.txt", "w");   // Cria um arquivo de entrada de texto

    // Escreve alguns caracteres de exemplo no arquivo de entrada
    fprintf(arquivoPraComprimir, "aaabb"); // Exemplos de caracteres
    fclose(arquivoPraComprimir);           // Fecha o arquivo de entrada

    dado_objeto tabela[TAMANHO_ASCII] = {0}; // Inicializa a tabela
    tabela['a'].conteudo = 0b00;             // Exemplo de código para 'a'
    tabela['a'].tamanho = 2;
    tabela['b'].conteudo = 0b01; // Exemplo de código para 'b'
    tabela['b'].tamanho = 3;

    // Chama a função para gravar os códigos
    arquivoPraComprimir = fopen("entrada_test.txt", "r");             // Reabre o arquivo de entrada para leitura
    gravarCodigos(arquivoComprimido, arquivoPraComprimir, tabela, 0); // Tamanho de lixo = 0
    fclose(arquivoPraComprimir);                                      // Fecha o arquivo de entrada
    fclose(arquivoComprimido);                                        // Fecha o arquivo comprimido

    // Abre o arquivo comprimido para verificar o conteúdo
    arquivoComprimido = fopen("comprimido_test.bin", "rb");
    unsigned char byte_lido;

    // Lê os bytes gravados e verifica
    fread(&byte_lido, sizeof(unsigned char), 1, arquivoComprimido);
    CU_ASSERT(byte_lido == 0b00011000); // Verifica o byte acumulado (código de 'a' e 'b')
    fclose(arquivoComprimido);          // Fecha o arquivo comprimido

    // Remove os arquivos de teste
    remove("comprimido_test.bin");
    remove("entrada_test.txt");
}

// TESTES DESCOMPRESSÃO

// Teste da função bit_ta_ativo
void test_bit_ta_ativo()
{
    unsigned char caracter = 0b10101010; // Caractere para teste
    int bit_posicao = 3;                 // Posição do bit que queremos verificar

    // Chama a função para verificar o bit
    unsigned int resultado = bit_ta_ativo(caracter, bit_posicao);

    // Verifica se o bit na posição 3 está ativo (1)
    CU_ASSERT(resultado == 0b00001000); // Deve retornar a máscara para o bit 3
}

// Teste da função obter_lixo
void test_obter_lixo()
{
    FILE *arquivoCompactado = fopen("test_lixo.bin", "wb");     // Cria um arquivo binário para teste
    unsigned char byte = 0b10101010;                            // Exemplo de byte com lixo
    fwrite(&byte, sizeof(unsigned char), 1, arquivoCompactado); // Escreve o byte no arquivo
    fclose(arquivoCompactado);                                  // Fecha o arquivo

    // Abre o arquivo para leitura
    arquivoCompactado = fopen("test_lixo.bin", "rb");
    short int lixo = obter_lixo(arquivoCompactado); // Chama a função para obter lixo
    fclose(arquivoCompactado);                      // Fecha o arquivo

    CU_ASSERT(lixo == 5); // Verifica se o lixo retornado está correto (5)

    // Remove o arquivo de teste
    remove("test_lixo.bin");
}

// Teste da função obter_tamanho_arvore
void test_obter_tamanho_arvore()
{
    FILE *arquivoCompactado = fopen("test_tamanho_arvore.bin", "wb"); // Cria um arquivo binário para teste
    unsigned char byte1 = 0b10100000;                                 // Exemplo de primeiro byte
    unsigned char byte2 = 0b00001111;                                 // Exemplo de segundo byte
    fwrite(&byte1, sizeof(unsigned char), 1, arquivoCompactado);      // Escreve os bytes no arquivo
    fwrite(&byte2, sizeof(unsigned char), 1, arquivoCompactado);
    fclose(arquivoCompactado); // Fecha o arquivo

    // Abre o arquivo para leitura
    arquivoCompactado = fopen("test_tamanho_arvore.bin", "rb");
    short int tamanho_arvore = obter_tamanho_arvore(arquivoCompactado); // Chama a função
    fclose(arquivoCompactado);                                          // Fecha o arquivo

    CU_ASSERT(tamanho_arvore == 1920); // Verifica se o tamanho da árvore está correto (1920)

    // Remove o arquivo de teste
    remove("test_tamanho_arvore.bin");
}

// Teste da função obterTamanhoCompressao
void test_obterTamanhoCompressao()
{
    FILE *arquivo = fopen("test_tamanho.bin", "wb");              // Cria um arquivo binário para teste
    unsigned char dados[] = {0xAA, 0xBB, 0xCC};                   // Dados de exemplo
    fwrite(dados, sizeof(unsigned char), sizeof(dados), arquivo); // Escreve os dados no arquivo
    fclose(arquivo);                                              // Fecha o arquivo

    // Abre o arquivo para leitura
    arquivo = fopen("test_tamanho.bin", "rb");
    unsigned long long int tamanho = obterTamanhoCompressao(arquivo); // Chama a função
    fclose(arquivo);                                                  // Fecha o arquivo

    CU_ASSERT(tamanho == 3); // Verifica se o tamanho retornado está correto (3 bytes)

    // Remove o arquivo de teste
    remove("test_tamanho.bin");
}

// Teste da função reconstruir_arvore_huffman
void test_reconstruir_arvore_huffman()
{
    // Cria um arquivo de teste com uma representação simples da árvore
    FILE *arquivoCompactado = fopen("test_arvore_huffman.bin", "wb");
    unsigned char dados[] = {0x61, 0x2A, 0x62, 0x2A, 0x63}; // Representação da árvore: a*(b*c)
    fwrite(dados, sizeof(unsigned char), sizeof(dados), arquivoCompactado);
    fclose(arquivoCompactado);

    short int tamanho_arvore = 5; // Tamanho da árvore conforme os dados escritos

    // Abre o arquivo para leitura
    arquivoCompactado = fopen("test_arvore_huffman.bin", "rb");
    NoHuffman *arvore = reconstruir_arvore_huffman(arquivoCompactado, &tamanho_arvore);
    fclose(arquivoCompactado);

    // Verifica se a árvore foi construída corretamente
    CU_ASSERT(arvore != NULL);                                       // A árvore não deve ser nula
    CU_ASSERT(arvore->caractere == 'a');                             // Raiz deve ser 'a'
    CU_ASSERT(arvore->direita->caractere == '*');                    // O próximo nó deve ser um nó interno
    CU_ASSERT(arvore->direita->esquerda->caractere == 'b');          // Subárvore esquerda deve ser 'b'
    CU_ASSERT(arvore->direita->direita->caractere == '*');           // Subárvore direita deve ser um nó interno
    CU_ASSERT(arvore->direita->direita->esquerda->caractere == 'c'); // Folha deve ser 'c'

    // Libere a memória alocada pela árvore (implementação da função para liberar memória necessária)
    liberar_arvore_huffman(arvore);
}

// Teste da função descomprimir_arquivo_usando_huffman
void test_descomprimir_arquivo_usando_huffman()
{
    // Cria um arquivo de teste com dados comprimidos
    FILE *arquivo_comprimido = fopen("test_descomprimido.bin", "wb");
    unsigned char dados[] = {0xAA, 0xBB, 0xCC}; // Dados comprimidos de exemplo
    fwrite(dados, sizeof(unsigned char), sizeof(dados), arquivo_comprimido);
    fclose(arquivo_comprimido);

    // Cria uma árvore Huffman de exemplo
    NoHuffman *arvore_huffman = criar_no_huffman('a', 0);         // Raiz com caractere 'a'
    arvore_huffman->esquerda = criar_no_huffman('b', 0);          // Folha 'b'
    arvore_huffman->direita = criar_no_huffman('*', 0);           // Nó interno
    arvore_huffman->direita->esquerda = criar_no_huffman('c', 0); // Folha 'c'

    // Abre o arquivo comprimido para leitura
    arquivo_comprimido = fopen("test_descomprimido.bin", "rb");
    int tamanho_lixo = 3;                                                      // Exemplo de lixo
    int tamanho_arq_comprimido_sem_arvore_sem_lixo = 10;                       // Exemplo de tamanho
    FILE *arquivo_descomprimido = fopen("test_saida_descomprimido.bin", "wb"); // Cria arquivo para saída descomprimida

    // Chama a função para descomprimir
    descomprimir_arquivo_usando_huffman(arquivo_comprimido, tamanho_lixo, tamanho_arq_comprimido_sem_arvore_sem_lixo, arvore_huffman, arquivo_descomprimido);

    fclose(arquivo_comprimido);    // Fecha o arquivo comprimido
    fclose(arquivo_descomprimido); // Fecha o arquivo de saída

    // Verifica o conteúdo do arquivo descomprimido
    arquivo_descomprimido = fopen("test_saida_descomprimido.bin", "rb");
    unsigned char resultado[3];                                        // Buffer para armazenar o resultado
    fread(resultado, sizeof(unsigned char), 3, arquivo_descomprimido); // Lê o conteúdo do arquivo
    fclose(arquivo_descomprimido);                                     // Fecha o arquivo de saída

    // Verifica se o resultado descomprimido é o esperado
    CU_ASSERT(memcmp(resultado, dados, sizeof(dados)) == 0); // O resultado deve ser igual aos dados originais

    // Libere a memória alocada pela árvore (implementação da função para liberar memória necessária)
    liberar_arvore_huffman(arvore_huffman);

    // Remove os arquivos de teste
    remove("test_descomprimido.bin");
    remove("test_saida_descomprimido.bin");
}

// HUFFMAN.H

// Teste da função comprimir
void test_comprimir()
{
    // Cria um arquivo de teste com alguns dados simples
    const char *caminho_arquivo = "test_entrada.txt";
    FILE *arquivo_entrada = fopen(caminho_arquivo, "w");
    const char *conteudo = "AAAAAABBBBBCCCCDDDEEF"; // Conteúdo de exemplo
    fwrite(conteudo, sizeof(char), strlen(conteudo), arquivo_entrada);
    fclose(arquivo_entrada);

    // Chama a função para comprimir o arquivo
    comprimir("test_entrada.txt");

    // Verifica se o arquivo comprimido foi criado
    const char *caminho_arquivo_comprimido = "test_entrada.txt.huff";
    FILE *arquivo_comprimido = fopen(caminho_arquivo_comprimido, "rb");
    CU_ASSERT(arquivo_comprimido != NULL); // O arquivo comprimido deve existir

    // Verifica se o arquivo comprimido não está vazio
    fseek(arquivo_comprimido, 0, SEEK_END);
    long tamanho_comprimido = ftell(arquivo_comprimido);
    CU_ASSERT(tamanho_comprimido > 0); // O arquivo comprimido deve ter tamanho maior que 0
    fclose(arquivo_comprimido);

    // Remove os arquivos de teste
    remove(caminho_arquivo);
    remove(caminho_arquivo_comprimido);
}

// Teste da função descomprimir
void test_descomprimir()
{
    // Cria um arquivo de entrada com alguns dados simples
    const char *caminho_arquivo_entrada = "test_entrada.txt";
    FILE *arquivo_entrada = fopen(caminho_arquivo_entrada, "w");
    const char *conteudo = "AAAAAABBBBBCCCCDDDEEF"; // Conteúdo de exemplo
    fwrite(conteudo, sizeof(char), strlen(conteudo), arquivo_entrada);
    fclose(arquivo_entrada);

    // Comprime o arquivo de entrada para criar um arquivo comprimido
    comprimir((char *)caminho_arquivo_entrada);

    // Caminho para o arquivo comprimido e para o arquivo descomprimido
    const char *caminho_arquivo_comprimido = "test_entrada.txt.huff";
    const char *caminho_arquivo_descomprimido = "test_entrada_descomprimido.txt";

    // Chama a função para descomprimir o arquivo
    descomprimir((char *)caminho_arquivo_comprimido);

    // Verifica se o arquivo descomprimido foi criado
    FILE *arquivo_descomprimido = fopen(caminho_arquivo_descomprimido, "rb");
    CU_ASSERT(arquivo_descomprimido != NULL); // O arquivo descomprimido deve existir

    // Verifica se o conteúdo do arquivo descomprimido é o esperado
    fseek(arquivo_descomprimido, 0, SEEK_END);
    long tamanho_descomprimido = ftell(arquivo_descomprimido);
    CU_ASSERT(tamanho_descomprimido == strlen(conteudo)); // O tamanho deve ser igual ao original

    // Rewind para ler o conteúdo
    fseek(arquivo_descomprimido, 0, SEEK_SET);
    char *buffer = malloc(tamanho_descomprimido + 1);
    fread(buffer, sizeof(char), tamanho_descomprimido, arquivo_descomprimido);
    buffer[tamanho_descomprimido] = '\0'; // Adiciona o terminador nulo

    CU_ASSERT_STRING_EQUAL(buffer, conteudo); // O conteúdo descomprimido deve ser igual ao original

    // Limpa
    free(buffer);
    fclose(arquivo_descomprimido);

    // Remove os arquivos de teste
    remove(caminho_arquivo_entrada);
    remove(caminho_arquivo_comprimido);
    remove(caminho_arquivo_descomprimido);
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Suite de Testes UTILS", NULL, NULL);

    //* UTILS.H
    CU_add_test(suite, "Teste da criação do nó Huffman", test_criar_no_huffman);
    CU_add_test(suite, "Teste da criação do dado_objeto", test_criar_dado_objeto);
    CU_add_test(suite, "Teste do ponteiro_void", test_ponteiro_void);
    CU_add_test(suite, "Teste de recuperar_caracter_ponteiro_void", test_recuperar_caracter_ponteiro_void);
    CU_add_test(suite, "Teste de e_folha", test_e_folha);

    CU_pSuite suite2 = CU_add_suite("suite de Testes COMPRESSAO", NULL, NULL);

    //* ALGORITMO_COMPRESSAO.H
    CU_add_test(suite2, "Teste da fila_prioridade_vazia", test_fila_prioridade_vazia);
    CU_add_test(suite2, "Teste de inserir_na_fila_prioridade", test_inserir_na_fila_prioridade);
    CU_add_test(suite2, "Teste de remover_da_fila_prioridade", test_remover_da_fila_prioridade);
    CU_add_test(suite2, "Teste de obter_frequencia_caracter", test_obter_frequencia_caracter);
    CU_add_test(suite2, "Teste de construir_arvore_huffman", test_construir_arvore_huffman);
    CU_add_test(suite2, "Teste de gerar_Nova_Tabela_ASCII_Hufmman", test_gerar_Nova_Tabela_ASCII_Hufmman);
    CU_add_test(suite2, "Teste de calcular_tamanho_lixo", test_calcular_tamanho_lixo);
    CU_add_test(suite2, "Teste de calcular_tamanho_arvore", test_calcular_tamanho_arvore);
    CU_add_test(suite2, "Teste de escrever_cabecalho_inicial", test_escrever_cabecalho_inicial);
    CU_add_test(suite2, "Teste de escrever_arvore_pre_ordem", test_escrever_arvore_pre_ordem);
    CU_add_test(suite2, "Teste de gravarCodigos", test_gravarCodigos);

    CU_pSuite suite3 = CU_add_suite("Suite de Testes DESCOMPRESSAO", NULL, NULL);

    //* ALGORITMO_DESCOMPRESSAO.H
    CU_add_test(suite3, "Teste de bit_ta_ativo", test_bit_ta_ativo);
    CU_add_test(suite3, "Teste de obter_lixo", test_obter_lixo);
    CU_add_test(suite3, "Teste de obter_tamanho_arvore", test_obter_tamanho_arvore);
    CU_add_test(suite3, "Teste de obterTamanhoCompressao", test_obterTamanhoCompressao);
    CU_add_test(suite3, "Teste de reconstruir_arvore_huffman", test_reconstruir_arvore_huffman);
    CU_add_test(suite3, "Teste de descomprimir_arquivo_usando_huffman", test_descomprimir_arquivo_usando_huffman);

    CU_pSuite suite4 = CU_add_suite("Suite de Testes HUFFMAN", NULL, NULL);

    //* HUFFMAN.H
    CU_add_test(suite4, "Teste de comprimir", test_comprimir);
    CU_add_test(suite4, "Teste de descomprimir", test_descomprimir);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
