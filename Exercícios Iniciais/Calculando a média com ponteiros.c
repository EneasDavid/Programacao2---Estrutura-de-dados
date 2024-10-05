#include <stdio.h>
 void calcular_media (int *A, int *B){
    /*
    deve
    verificar maior e menor valor (e armazenar essa info)
    deve substituir o maior valor pelo resto da media
    deve substituir a menor pelo valor inteiro da divisão
    */
    int *maior=A,*menor=B;
    int media=(*A+*B)>>1;
    int resto=(*A+*B)%2;
    if(*maior<*menor){
        maior=B;
        menor=A;
    }
    *maior=resto;
    *menor=media;
 }
int main(){
    int a, b;
    scanf("%d%d",&a, &b);
    calcular_media(&a,&b);
    printf("A = %d\nB = %d\n", a, b);
    return 0;
}