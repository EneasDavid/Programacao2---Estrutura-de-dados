#include <stdio.h>

// Um ponteiro armazena o endereço de memória de outra variável.

int main() {
    // Declaração de uma variável e de um ponteiro
    int valor, *endereco;

    // Atribuindo o endereço da variável 'valor' ao ponteiro 'endereco'
    endereco = &valor;

    // Usando o ponteiro para receber um valor do usuário usando scanf
    printf("Digite um valor: ");
    scanf("%d", endereco);

    // Exibindo o endereço de memória e o valor armazenado através do ponteiro
    printf("Endereco de Memoria: %p\nValor Armazenado: %d\n",endereco, *endereco);

    return 0;
}