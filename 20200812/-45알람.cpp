#include<stdio.h>
int main(){
    int H=10;
    int M=10;
    scanf("%d %d",&H,&M);
    if(M>=45){
        M-=45;
    }
    else{
        M=(M+60)-45;
        H-=1;
    }
    printf("%d %d",(H+24)%24,M);
        return 0;
    }
