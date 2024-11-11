#include <stdio.h>

void swap(int *a, int *b) {
    *a = *a^*b;
    *b = *a^*b;
    *a = *a^*b;
}
/*
    na chamada recursiva do metodo quick_sort, 
    o segundo parametro deve ser o tamanho do
     vetor a partir do indice a, porem está 
     sendo atualizado durante a execução, o 
     que faz com que o loop seja infinito.

     para resolver vamos adicionar um parametro
     na função que referencie o maior index do 
     vetor.

*/
void quick_sort(int *v, int size, int indexMax) {
    if (size >= indexMax)  return;
    int pivot = v[size+(indexMax-size)>>1];
    int a = size;
    int b = indexMax;
    while (a <= b) {
        while (v[a] < pivot) a++;
        while (v[b] > pivot) b--;
        if (a < b){
            swap(&v[a], &v[b]);
            a++;
            b--;
        }
        if(size<b) quick_sort(v, size, b);
        if(a<indexMax) quick_sort(v, a, indexMax);
    }
}

int main(){
    int v[] = {3, 6, 8, 10, 1, 2, 1};
    int size = sizeof(v) / sizeof(v[0]);
    printf("[ ");
    for(int i = 0; i < size; i++) {
        printf("%d ", v[i]);
    }
    printf("]\n");
    quick_sort(v, 0, size - 1);
    printf("[ ");
    for(int i = 0; i < size; i++) {
        printf("%d ", v[i]);
    }
    printf("]\n");
    return 0;
}