#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *criarNo(int data) {
    Node *newNode=(Node *)malloc(sizeof(Node));
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

Node *criaArvore(char *expr, int *pos) {
    if (expr[*pos] == '(') {
        (*pos)++;
        if(expr[*pos] == ')') {
            (*pos)++;
            return NULL;
        }
        int value=0;
        int sign=1;
        if (expr[*pos] == '-') {
            sign=-1;
            (*pos)++;
        }
        while(expr[*pos] >= '0' && expr[*pos] <= '9') {
            value=value * 10 + (expr[*pos] - '0');
            (*pos)++;
        }
        value *= sign;
        Node *node=criarNo(value);
        node->left=criaArvore(expr, pos);
        node->right=criaArvore(expr, pos);
        (*pos)++;
        return node;
    }
    return NULL;
}

int encontrarSoma(Node *root, int sum) {
    if(root==NULL) return 0;
    if(root->left==NULL && root->right==NULL && sum-root->data==0) return 1;
    return encontrarSoma(root->left, sum-root->data) || encontrarSoma(root->right, sum-root->data);
}

void limparArvore(Node *root) {
    if (root==NULL) return;
    limparArvore(root->left);
    limparArvore(root->right);
    free(root);
}

int main() {
    int sum;
    while (scanf("%d", &sum) == 1 && sum != -1000) {
        getchar();
        char expr[1000];
        fgets(expr, sizeof(expr), stdin);
        int pos=0;
        Node *root=criaArvore(expr, &pos);
        if(encontrarSoma(root, sum)) printf("sim\n");
        else printf("nao\n");
        limparArvore(root);
    }
    return 0;
}
