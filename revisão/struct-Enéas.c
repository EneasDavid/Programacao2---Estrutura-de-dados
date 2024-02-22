#include <stdio.h>
#include <string.h>
#define max_size 255

//Struct é uma forma de criar um tipo de dado proprio

//In this way u ever need to use 'struct' to call the new type
struct Pessoa{
    char nome[max_size];
    int idade;
};

//In here when use 'typedef' in front of 'struct' we dispense with the use of 'struct every time we need to call a new type
typedef struct _aluno{
    char nome[max_size];
    int idade;
} Aluno;
//This is very important, notice the 'Aluno', now we need this global variable

int main(){
    /*
    aqui o 'struct Pessoa' vira um tipo de variavel
    barney torna-se o nome de nossa variavel
    e os atributos de Pessoa acabam por ser, indutivamente, os atributos de barney
    os quais podemos acessar com barney.atributo;
    */
    //In here we need use 'srtuct' else we get a erro
    struct Pessoa barney;
    strcpy(barney.nome, "Barney");
    printf("%s\n", barney.nome);

    //but here we usen't that, because now we use the global variable 'Aluno'
    Aluno eneas;
    strcpy(eneas.nome,"Enéas");
    printf("%s\n", eneas.nome);
    
    printf("Pessoa %lu\nAluno %lu\n", sizeof(barney),sizeof(Aluno));
    
    Aluno david = {.nome="David", .idade=20};
    printf("nome %s, idade %d\n", david.nome, david.idade);
    
    //in this way we can use malloc for acess the position and atribut 
    Aluno *ted = (Aluno*) calloc(1, sizeof(Aluno));
    strcpy(ted->nome, "Ted");
    //notice we need a new thing the '->'(arrow operator) to call the attributes
    (*ted).idade=18;
    //as the arrow operator is an indication of a pointer we can struct that like a pointer to, look the exemple up
    printf("nome %s, idade %d", ted->nome, ted->idade);
    return 0;
}