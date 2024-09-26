#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* findNode(Node* root, int value) {
    if (root == NULL) return NULL;
    if (root->value == value) return root;
    Node* left = findNode(root->left, value);
    if (left != NULL) return left;
    return findNode(root->right, value);
}

Node* parseTree(char* str, int* index) {
    if (str[*index] == '(') (*index)++;
    if (str[*index] == ')') {
        (*index)++; 
        return NULL;
    }
    int sign = 1;
    if (str[*index] == '-') {
        sign = -1;
        (*index)++;
    }
    int value = 0;
    while (str[*index] >= '0' && str[*index] <= '9') {
        value = value * 10 + (str[*index] - '0');
        (*index)++;
    }
    value *= sign;
    Node* node = newNode(value);
    node->left = parseTree(str, index);
    node->right = parseTree(str, index);
    (*index)++;
    return node;
}

void concatTrees(Node* base, Node* toConcat) {
    if (base == NULL || toConcat == NULL) return;
    Node* targetNode = findNode(base, toConcat->value);
    if (targetNode != NULL) {
        if (targetNode->left == NULL) {
            targetNode->left = toConcat->left;
        } else {
            concatTrees(targetNode->left, toConcat->left);
        }

        if (targetNode->right == NULL) {
            targetNode->right = toConcat->right;
        } else {
            concatTrees(targetNode->right, toConcat->right);
        }
    }
}

void printTree(Node* root) {
    if (root == NULL) {
        printf("()");
        return;
    }

    printf("(%d", root->value);
    printTree(root->left);
    printTree(root->right);
    printf(")");
}

int main() {
    char input[1001];
    fgets(input, 1001, stdin);
    int index = 0;
    Node* baseTree = parseTree(input, &index);
    while (1) {
        fgets(input, 1001, stdin);
        if (strcmp(input, "()\n") == 0) {
            break;
        }
        index = 0;
        Node* newTree = parseTree(input, &index);
       concatTrees(baseTree, newTree);
    }

    printTree(baseTree);
    printf("\n");

    return 0;
}