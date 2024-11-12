![Badge em desenvolvimento](https://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=YELLOW&style=for-the-badge)
![C](https://img.shields.io/badge/C-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

# Projeto de Estrutura de Dados II
## Huffman

O projeto consiste em implementar o algoritmo de Huffman para compressão de arquivos. O algoritmo de Huffman é um método de compressão que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser comprimido para determinar códigos de tamanho variável para cada símbolo. O algoritmo foi desenvolvido por David A. Huffman em 1952, enquanto era um estudante de graduação no MIT, e foi publicado em 1952.

## Tabela de Conteúdos

- [Instalação](#instalação)
- [Método de Uso](#método-de-uso)
- [Integrantes](#integrantes)
- [Cabeçalho](#cabeçalho)

## Instalação

```bash
git clone https://github.com/EneasDavid/Huffman/tree/main
```

## Método de Uso
Para compilar o projeto, execute o comando abaixo no terminal. O comando gera um executável chamado `huff`:

```bash
gcc -o huff src/utils.c src/algoritimo_compressao.c src/algoritimo_descompressao.c src/huffman.c src/main.c
```

Para executar o projeto, basta rodar:

```bash
./huff
```

O programa solicitará o arquivo a ser comprimido.

## Integrantes
| Discente    | Curso                    |
|-------------|--------------------------|
| David Enéas | Ciência da Computação     |

## Cabeçalho

A estrutura do cabeçalho do arquivo comprimido é organizada da seguinte forma:

### Estrutura

#### Primeiro Byte (1 byte - 8 bits)
- **3 bits iniciais** (mais à esquerda): tamanho do lixo (bits que sobraram para completar o byte na árvore de Huffman)
- **5 bits**: início do tamanho da árvore de Huffman

#### Segundo Byte (1 byte - 8 bits)
- **8 bits**: continuam representando o tamanho da árvore de Huffman

#### Próximos Bytes (N bytes)
- **N bytes**: representam a árvore de Huffman

#### Dados Comprimidos
Após os dados da árvore e extensão, temos:
- **N bytes**: representam os dados comprimidos
