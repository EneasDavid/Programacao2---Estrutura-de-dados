#include <stdio.h>
//pesquisar tad em c
//Notação basica de lista encadeada
typedef struct _node{
    int valor; //valor do no
    struct _node *proximo; // ponteiro que aponta para a proxima possição
    //Na linha a cima não use-se o node que é definido a baixo porque o programa ainda não tem conhecimento da proxima linha
}Node;
//Começo da lista encadeada
typedef struct _linked_list{
    Node *comeco;
}LinkedList;

int main(){

    return 0;
}