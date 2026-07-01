#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char value;
    int is_leaf;
    char tree[205];
    struct Node *left;
    struct Node *right;
} Node;

Node *create_leaf(char c) {
    Node *node = malloc(sizeof(Node));

    node->value = c;
    node->is_leaf = 1;
    node->left = NULL;
    node->right = NULL;

    node->tree[0] = c;
    node->tree[1] = '\0';

    return node;
}

Node *create_internal(Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));

    node->value = '*';
    node->is_leaf = 0;
    node->left = left;
    node->right = right;

    strcpy(node->tree, left->tree);
    strcat(node->tree, right->tree);
    strcat(node->tree, "*");

    return node;
}

void print_steps(Node *node) {
    if (node == NULL) return;

    printf("------------------------------\n");
    printf("The tree %s has:\n", node->tree);
    printf("- Left subtree: %s\n", node->left ? node->left->tree : "");
    printf("- Right subtree: %s\n", node->right ? node->right->tree : "");
    printf("------------------------------\n");

    print_steps(node->left);
    print_steps(node->right);
}

void print_codes(Node *node, char code[], int depth) {
    if (node == NULL) return;

    if (node->is_leaf) {
        code[depth] = '\0';
        printf("%c : %s\n", node->value, code);
        return;
    }

    code[depth] = '0';
    print_codes(node->left, code, depth + 1);

    code[depth] = '1';
    print_codes(node->right, code, depth + 1);
}

int main(void) {
    char input[205];
    Node *stack[205];
    int top = 0;

    scanf("%204s", input);

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '*') {
            Node *right = stack[--top];
            Node *left = stack[--top];

            stack[top++] = create_internal(left, right);
        } else {
            stack[top++] = create_leaf(input[i]);
        }
    }

    Node *root = stack[0];
    char code[205];

    print_steps(root);

    printf("\nDecoding Tree is:\n\n");
    print_codes(root, code, 0);

    return 0;
}
