#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_CARACTER 16

typedef struct no vizinho;
typedef struct grafo grafo;
typedef struct list lista;

struct no{
    char item[16];
    vizinho *next;
};

struct grafo{
    int visitado[MAX];
    int tamanho_atual;
    int vertice_deletado[MAX];
    char vertice_atual[MAX][MAX_CARACTER];
    vizinho *vertices[MAX];
};

struct list{
    char item[16];
    lista *next;
};

grafo* criar_grafo(){
    grafo *novo_grafo=(grafo*)malloc(sizeof(grafo));
    novo_grafo->tamanho_atual=0;
    for(int i=0; i < MAX; i++){
        novo_grafo->vertices[i]=NULL;
        novo_grafo->visitado[i]=0;
        novo_grafo->vertice_deletado[i]=0;
    }
    return novo_grafo;
}

vizinho* add_vizinho(vizinho *vertice_vizinho ,char vizinho_atual[]){
    vizinho *novo_vizinho=(vizinho*)malloc(sizeof(vizinho));
    strcpy(novo_vizinho->item, vizinho_atual);
    novo_vizinho->next=vertice_vizinho;
    return novo_vizinho;
}

int verifica_vertice(grafo *GRAFO, char vertice_testado[]){
    int i;
    for(i=0; i < MAX; i++){
        if(GRAFO->vertice_atual[i][0]=='\0'){
           strcpy(GRAFO->vertice_atual[i], vertice_testado);
           GRAFO->tamanho_atual++;
           break; 
        }
        if(strcmp(GRAFO->vertice_atual[i], vertice_testado) == 0) break;
    }
    return i;   
}

void add_edge(grafo *GRAFO, char vertice_atual[], char vizinho_atual[]){
    int i=verifica_vertice(GRAFO, vertice_atual);
    verifica_vertice(GRAFO, vizinho_atual);
    GRAFO->vertices[i]=add_vizinho(GRAFO->vertices[i], vizinho_atual);
}

void print_graph(grafo *GRAFO){
    vizinho *aux;
    for(int i=0; i<GRAFO->tamanho_atual; i++){
        if(!(GRAFO->vertice_deletado[i])){
            printf("V�rtice: %s\n", GRAFO->vertice_atual[i]);
        }
        aux=GRAFO->vertices[i];
        while(aux){
            printf("vizinho: %s ", aux->item);
            aux=aux->next;
        }
        printf("\n\n");
    }
}

void deleta_vizinhos(grafo *GRAFO, char vizinho_atual[]){
    vizinho *current, *previus;
    for(int i=0; i<GRAFO->tamanho_atual; i++){
        if(!(GRAFO->vertice_deletado[i]) && GRAFO->vertices[i]!=NULL){
          current=GRAFO->vertices[i];
          previus=NULL;
          while((current!=NULL) && strcmp(current->item, vizinho_atual)!=0){
              previus=current;
              current=current->next;
          }
          if(previus==NULL && current!=NULL){
              GRAFO->vertices[i]=current->next;
              free(current);
          }else if(current!=NULL && previus!=NULL){
              previus->next=current->next;
              free(current);
          }
        }
    }
}

lista* add_list(lista *lista_pa_printar, char vertice_pa_printar[]){
    lista *novo_vertice_pa_printar=(lista*)malloc(sizeof(lista)), *current, *previus;
    strcpy(novo_vertice_pa_printar->item, vertice_pa_printar);
    if(lista_pa_printar==NULL){
        novo_vertice_pa_printar->next=lista_pa_printar;
        lista_pa_printar=novo_vertice_pa_printar;
    }else{
        current=lista_pa_printar, previus=NULL;
        while(current!=NULL && strcmp(current->item, novo_vertice_pa_printar->item)<0){
            previus=current;
            current=current->next;
        }
        if(current==NULL){
            novo_vertice_pa_printar->next=NULL;
            previus->next=novo_vertice_pa_printar;
        }else if(current==lista_pa_printar){
            novo_vertice_pa_printar->next=lista_pa_printar;
            lista_pa_printar=novo_vertice_pa_printar;
        }else{
            previus->next=novo_vertice_pa_printar;
            novo_vertice_pa_printar->next=current;
        }
    }   
    return lista_pa_printar;
}

lista* print_lista(lista *lista_pa_printar){
  lista *aux;
  while(lista_pa_printar!=NULL){
    aux=lista_pa_printar->next;
    printf("%s\n", lista_pa_printar->item);
    free(lista_pa_printar);
    lista_pa_printar=aux;
  }
  return NULL;
}

void remocao(grafo *GRAFO, lista *lista_pa_printar){
    for(int i=0; i<GRAFO->tamanho_atual; i++){
        if(GRAFO->vertices[i]==NULL && GRAFO->vertice_deletado[i]!=1){
            lista_pa_printar=add_list(lista_pa_printar, GRAFO->vertice_atual[i]);
            GRAFO->vertice_deletado[i]=1;
            deleta_vizinhos(GRAFO, GRAFO->vertice_atual[i]);  
        }
    }
    lista_pa_printar=print_lista(lista_pa_printar);
    return;
}

int grafo_esta_vazio(grafo *GRAFO){
  for(int i=0; i<GRAFO->tamanho_atual; i++){
    if(!(GRAFO->vertice_deletado[i])){
      return 0;
    }
  }
  for(int i=0; i<GRAFO->tamanho_atual; i++){
      GRAFO->vertices[i]=NULL;
      GRAFO->visitado[i]=0;
      GRAFO->vertice_deletado[i]=0;
      strcpy(GRAFO->vertice_atual[i], "\0");
  }
  GRAFO->tamanho_atual=0;
  return 1;
}

int main(){
    grafo *GRAFO=criar_grafo();
    lista *lista_pa_printar=NULL;
    int numero_de_testes;
    char vertice_atual[16], vizinho_atual[16];
    while(scanf("%d", &numero_de_testes)!=EOF){
      while(numero_de_testes!=0){
          scanf(" %s %s", vertice_atual, vizinho_atual);
          add_edge(GRAFO, vertice_atual, vizinho_atual);
          numero_de_testes--;
      }
      while(!(grafo_esta_vazio(GRAFO))){
        remocao(GRAFO, lista_pa_printar);
      }
    }
    return 0;
}