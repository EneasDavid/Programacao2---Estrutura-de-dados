#include <stdio.h>

void changeValues(int *pointerA, int *pointerB){
    *pointerA=*pointerA^*pointerB;
    *pointerB=*pointerA^*pointerB;
    *pointerA=*pointerA^*pointerB;
}
int main(){
    int a, b;

    scanf("%d%d",&a, &b);

    printf("a: %d b: %d\n", a, b);
    changeValues(&a,&b);
    printf("a: %d b: %d\n", a, b);

    return 0;
}