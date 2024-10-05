#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Node* insert(Node* root, int value) {
    if (root == NULL) return createNode(value);
    
    if (value < root->value) root->left = insert(root->left, value);
    else root->right = insert(root->right, value);
    
    return root;
}

void printTree(Node* root, int depth) {
    if (root == NULL) {
        printf(" () "); 
        return;
    }

    if (depth == 0) printf("   ( %d ", root->value);
    else printf(" ( %d ", root->value);
    
    printTree(root->left, depth + 1);
    printTree(root->right, depth + 1);
    printf(") ");
}

int main() {
    Node* root = NULL;
    char input[100]; 
    
    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            printf("----\nSaindo...\n");
            break; 
        }

        char* token = strtok(input, " ");
        while (token != NULL) {
            int value = atoi(token);
            printf("----\nAdicionando %d\n", value);
            root = insert(root, value);
            printTree(root, 0);
            printf("\n");
            token = strtok(NULL, " ");
        }
    }
    printf("----\n");

    return 0;
}