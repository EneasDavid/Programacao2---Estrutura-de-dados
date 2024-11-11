#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

typedef struct{
    char itens[MAX_SIZE];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p){
    p->topo=-1;
}

int pilhaCheia(Pilha *p){
    return p->topo==MAX_SIZE-1;
}

int pilhaVazia(Pilha *p){
    return p->topo==-1;
}

void empilhar(Pilha *p, char item){
    if(!pilhaCheia(p)) p->itens[++p->topo]=item;
}

char desempilhar(Pilha *p){
    if(!pilhaVazia(p)) return p->itens[p->topo--];
    return '\0'; 
}

int estaBalanceada(const char *str){
    Pilha pilha;
    inicializarPilha(&pilha);
    
    for(int i=0; str[i] != '\0'; i++){
        char atual=str[i];
        if(atual==' ') continue;
        if(atual=='('||atual=='['){
            empilhar(&pilha, atual);
        }else if(atual==')'||atual==']'){
            if(pilhaVazia(&pilha)) return 0;
            char topo=desempilhar(&pilha);
            if((atual==')' && topo != '(')||(atual==']' && topo != '[')) return 0;
        }
    }
    return pilhaVazia(&pilha);
}

int main(){
    int n;
    scanf("%d", &n);
    getchar();
    for(int i=0; i < n; i++){
        char str[MAX_SIZE];
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")]='\0';
        if(estaBalanceada(str)) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
