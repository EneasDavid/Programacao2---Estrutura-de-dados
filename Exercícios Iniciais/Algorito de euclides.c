#include <stdio.h>
int mdc(int x, int y){
    int resto=x%y;
    if(resto==0){
        return y;
    }else{
        return mdc(y,resto);
    }
}
void entrada(int z){
    if(z>0){
        int x, y;
        scanf("%d%d", &x, &y);
        printf("MDC(%d,%d) = %d\n",x,y,mdc(x,y));
        entrada(z-1);
    }
}
int main() {
    int qtn;
    scanf("%d", &qtn);
    entrada(qtn);
	return 0;
}