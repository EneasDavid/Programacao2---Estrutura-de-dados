#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Armazena o primeiro item da fila
typedef struct _stack STACK;

//Armazena o conteudo do no e um ponteiro para o proximo no da fila
typedef struct _node NODE;

struct _stack
{
    NODE* head;
};
struct _node
{
    int element;
    NODE* next;
};

//Cria uma stack com o a head NULL
STACK* Create_stack();

//Recebe um elemento e cria e retorna um novo node
// com o elemento passado
NODE* create_node(int element);

//Verifica se a pilha esta vazia
int IS_EMPTY(STACK* stack);

//Recebe uma pilha e Retorna o elemento que esta no topo da fila
int POP(STACK* stack);

//Recebe uma pilha e um inteiro e retorna a nova pilha
//Adiciona um novo node no topo da pilha
void PUSH(STACK* stack, int element);

//Recebe a pilha e a operacao a ser feita
//faz a operacao da calculadora
void result(STACK* stack, char operation);

//Recebe uma pilha vazia e quantas strings serao lidas
//Le as n strings que vao seguir e resolve as expressoes
void Calculadora(STACK* calculadora, int size);

int main()
{
    STACK* calculadora = Create_stack();
    int k;
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 1: %d\n", POP(calculadora));
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 2: %d\n", POP(calculadora));

}
STACK* Create_stack() {
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->head = NULL;
    return stack;
}

NODE* create_node(int element) {
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    new_node->element = element;
    new_node->next = NULL;
    return new_node;
}

int IS_EMPTY(STACK* stack) {
    return stack->head == NULL;
}

int POP(STACK* stack) {
    if (IS_EMPTY(stack)) {
        printf("Pilha vazia!\n");
        exit(EXIT_FAILURE); // Termina o programa se a pilha estiver vazia
    }
    NODE* top_node = stack->head;
    int top_value = top_node->element;
    stack->head = top_node->next;
    free(top_node);
    return top_value;
}

void PUSH(STACK* stack, int element) {
    NODE* new_node = create_node(element);
    new_node->next = stack->head;
    stack->head = new_node;
}

void result(STACK* stack, char operation) {
    int a, b, res;
    b = POP(stack); // O segundo elemento
    a = POP(stack); // O primeiro elemento
    switch (operation) {
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            res = a / b;
            break;
        default:
            printf("Opera��o inv�lida!\n");
            exit(EXIT_FAILURE);
    }
    PUSH(stack, res); // Adiciona o resultado de volta � pilha
}

void Calculadora(STACK* calculadora, int size) {
    char input[10];
    for (int i = 0; i < size; i++) {
        scanf("%s", input);
        if (isdigit(input[0])) {
            // Se o input � um n�mero, converte e empilha
            PUSH(calculadora, atoi(input));
        } else {
            // Se n�o, � uma opera��o
            result(calculadora, input[0]);
        }
    }
}
