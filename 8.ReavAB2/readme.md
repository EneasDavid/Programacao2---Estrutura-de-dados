![Badge em desenvolvimento](https://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=YELLOW&style=for-the-badge)
![C](https://img.shields.io/badge/C-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)


# Projeto de Estrutura de Dados II - REAV
Huffman 
O projeto consiste em implementar o algoritmo de Huffman para compressão de arquivos. O algoritmo de Huffman é um método de compressão que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser comprimido para determinar códigos de tamanho variável para cada símbolo. O algoritmo foi desenvolvido por David A. Huffman em 1952, enquanto era um estudante de graduação no MIT, e foi publicado em 1952.


## Tabela de conteúdos

- [Instalação](#instalação)
- [Método de Uso](#método-de-uso)
- [Integrantes](#Integrantes)
- [Cabeçalho](#Cabeçalho)

## Instalação

```bash
git clone https://github.com/EneasDavid/Huffman/tree/main
```

## Método de Uso
Para compilar o projeto, basta executar o comando `gcc -o huff src/utils.c src/algoritimo_compressao.c src/algoritimo_descompressao.c src/huffman.c src/main.c` no terminal. O comando irá gerar um executável chamado `huff`.


Para executar o projeto, basta rodar o comando `./huff` no terminal. O programa irá solicitar o arquivo a ser comprimido.
#### de forma resumida

```bash
gcc -o huff src/utils.c src/algoritimo_compressao.c src/algoritimo_descompressao.c src/huffman.c src/main.c
```
```bash
./huff
```

## Integrantes
| Discente | Curso | 
| -------- | -------- |
| David Enéas | Ciência da Computação |  

## Cabeçalho

A disposição do cabeçalho do arquivo comprimito é feito da seguinte forma:
1 byte 
[][][][][][][][]

Onde:
[][][] -> Tamanho do lixo (resto de bits que faltou para completar o byte na arvore do huffman)
[][][][][] -> Começo do tamanho do arquivo
[][][][][][][][] -> resto do tamanho do arquivo 

assim ficando os dois primeiros byte
Primeiro byte
---------1 byte de 8 bits --------------
3 bits iniciais (mais a esquerda) para o tamnho do lixo
5 bits para o tamanho da arvore de huffman

Segundo byte
---------1 byte de 8 bits --------------
8 bits para o tamanho da arvore de huffman

N bytes
---------n byte de 8 bits --------------
arvore de huffman
Segundo byte

--------------ALTERAÇÃO-----------------
---------1 byte de 8 bits --------------
3 bits para o tamanho da extensão do arquivo
5 bits para de lixo 

---------N byte de 8 bits --------------
8 bits para letra da extensão do arquivo
--------------ALTERAÇÃO-----------------

N bytes
---------n byte de 8 bits --------------
Dados comprimidos
