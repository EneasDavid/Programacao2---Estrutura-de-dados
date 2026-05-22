#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *criarNo(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

char proximoChar() {
    char c;
    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\n' && c != '\r' && c != '\t') {
            return c;
        }
    }
    return EOF;
}

Node *criaArvore(int *valido) {
    char c = proximoChar();
    
    if (c == '(') {
        c = proximoChar();
        if (c == ')') {
            return NULL; 
        }
        
        int value = 0;
        int sign = 1;
        
        if (c == '-') {
            sign = -1;
            c = proximoChar();
        }
        
        while (c >= '0' && c <= '9') {
            value = value * 10 + (c - '0');
            c = getchar();
        }
        value *= sign;
        
        ungetc(c, stdin);
        
        Node *node = criarNo(value);
        *valido = 1;
        
        node->left = criaArvore(valido);
        node->right = criaArvore(valido);
        
        proximoChar(); 
        
        return node;
    }
    return NULL;
}

int encontrarSoma(Node *root, int sum) {
    if (root == NULL) return 0;
    
    if (root->left == NULL && root->right == NULL) {
        return (sum - root->data == 0);
    }
    
    return encontrarSoma(root->left, sum - root->data) || 
           encontrarSoma(root->right, sum - root->data);
}

void limparArvore(Node *root) {
    if (root == NULL) return;
    limparArvore(root->left);
    limparArvore(root->right);
    free(root);
}

int main() {
    int sum;
    
    while (scanf("%d", &sum) == 1) {
        if (sum == -1000) break;
        
        int temArvore = 0;
        Node *root = criaArvore(&temArvore);
        
        if (!temArvore) {
            printf("nao\n");
        } else if (encontrarSoma(root, sum)) {
            printf("sim\n");
        } else {
            printf("nao\n");
        }
        
        limparArvore(root);
    }
    
    return 0;
}
