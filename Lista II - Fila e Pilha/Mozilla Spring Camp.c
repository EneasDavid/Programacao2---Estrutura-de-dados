#include <stdio.h>
#include <string.h>

#define max 50

typedef struct pilha{
    char item[max];
    int topo;
}Navegacao;

void create(Navegacao *pagina){
    pagina->topo=-1;
}

void push(Navegacao *pagina, char acao){
    pagina->topo++;
    pagina->item[pagina->topo]=acao;
}

void pop(Navegacao *pagina){
    pagina->topo--;
}

int main() {
    int back=-1;
    Navegacao navegador;
    create(&navegador);
    char entrada[max];

    while(scanf(" %s", entrada)!=EOF){
        if(strcmp(entrada, "ENTER")==0){
            push(&navegador, 1);
            back=0;
        }else if(strcmp(entrada, "BACK")==0 && navegador.topo>0){
            pop(&navegador);
            back++;
        }else if(strcmp(entrada, "FORWARD")==0 && back>0) {
            push(&navegador, 1);
            back--;
        }
    }
    printf("BACK: %d\nFORWARD: %d", navegador.topo, back);
    return 0;
}
