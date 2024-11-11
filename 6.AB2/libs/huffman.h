#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "algoritimo_descompressao.h"
#include "algoritimo_compressao.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void comprimir(char *caminho_arquivo);

void descomprimir(char *caminho_arquivo_comprimido);

#endif