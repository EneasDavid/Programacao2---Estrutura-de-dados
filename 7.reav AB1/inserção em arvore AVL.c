#include <stdio.h>
#include <stdlib.h>
 
int flag = 0;
 
typedef struct avl_tree avl;
 
struct avl_tree {
    int item;
    int h;
    avl *left;
    avl *right;
};
 
int max(int a, int b) {
    return (a > b) ? a : b;
}
 
int height(avl *tree) {
    if(tree == NULL) {
        return -1;
    }
    else {
        return 1 + max(height(tree->left), height(tree->right));
    }
}
 
avl *create_avl(int item, avl *left, avl *right) {
    avl *new_avl = (avl*)malloc(sizeof(avl));
    new_avl->item = item;
    new_avl->left = left;
    new_avl->right = right;
    new_avl->h = height(new_avl);
    return new_avl;
}
 
avl *rotate_left(avl *tree) {
    avl *subtree_root = NULL;
    if(tree != NULL && tree->right != NULL) {
        subtree_root = tree->right;
        tree->right = subtree_root->left;
        subtree_root->left = tree;
    }
    subtree_root->h = height(subtree_root);
    tree->h = height(tree);
    return subtree_root;
}
 
avl *rotate_right(avl *tree) {
    avl *subtree_root = NULL;
    if(tree != NULL & tree->left != NULL) {
        subtree_root = tree->left;
        tree->left = subtree_root->right;
        subtree_root->right = tree;
    }
    subtree_root->h = height(subtree_root);
    tree->h = height(tree);
    return subtree_root;
}
 
int balance_factor(avl *tree) {
    if(tree != NULL) {
        return (height(tree->left) - height(tree->right));
    }
    return 0;
}
 
void generate_parenthesis_btree(avl *bt) {
    printf(" (");
    if(bt != NULL) {
        printf(" %d ", bt->item);
        generate_parenthesis_btree(bt->left);
        generate_parenthesis_btree(bt->right);
    }
    printf(") ");
}
 
avl *add_leaf_avl(avl *save, avl *tree, int item) {
    if(tree == NULL) {
        return create_avl(item, NULL, NULL);
    } else if(tree->item > item) {
        tree->left = add_leaf_avl(save, tree->left, item);
    } else {
        tree->right = add_leaf_avl(save, tree->right, item);
    }
    tree->h = height(tree);
    avl *child;
    if(balance_factor(tree) == 2 || balance_factor(tree) == -2) {
        printf("Antes de ajustar balanceamento...\n  ");
        generate_parenthesis_btree(save);
        if(balance_factor(tree) == 2) {
            child = tree->left;
            if(balance_factor(child) == -1) {
                tree->left = rotate_left(child);
            }
            tree = rotate_right(tree);
        } else if(balance_factor(tree) == -2) {
            child = tree->right;
            if(balance_factor(child) == 1) {
                tree->right = rotate_right(child);
            }
            tree = rotate_left(tree);
        }
        flag = 1;
    }
    return tree;
}
 
int main() {
    int item;
    avl *avl = NULL;
    while(scanf("%d", &item) != EOF) {
        printf("----\n");
        printf("Adicionando %d\n", item);
        avl = add_leaf_avl(avl, avl, item);
        if (!flag) {
            printf("Continuou AVL...\n");
        } else {
            printf("\nDepois de ajustar balanceamento...\n");
        }
        printf("  ");
        generate_parenthesis_btree(avl);
        printf("\n");
        flag = 0;
    }
    printf("----\n");
    return 0;
}