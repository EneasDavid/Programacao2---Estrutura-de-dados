#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bool isBSTUtil(Node* node, int min, int max) {
    if (node == NULL) return true;

    if (node->value < min || node->value > max) return false;

    return isBSTUtil(node->left, min, node->value - 1) && 
           isBSTUtil(node->right, node->value + 1, max);
}

bool isBST(Node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

Node* buildTree(const char* str, int* index) {
    if (str[*index] == '\0') return NULL;

    if (str[*index] == '(') {
        (*index)++;
        if (str[*index] == ')') {
            (*index)++;
            return NULL;
        }

        int value = 0;
        while (str[*index] >= '0' && str[*index] <= '9') {
            value = value * 10 + (str[*index] - '0');
            (*index)++;
        }

        Node* node = createNode(value);
        node->left = buildTree(str, index);
        node->right = buildTree(str, index);

        (*index)++; 
        return node;
    }
    return NULL;
}

void freeTree(Node* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    char entrada[1000];
    scanf("%s", entrada);

    int index = 0;
    Node* root = buildTree(entrada, &index);
    
    if (isBST(root)) printf("VERDADEIRO\n");
    else printf("FALSO\n");
    
    freeTree(root);

    return 0;
}