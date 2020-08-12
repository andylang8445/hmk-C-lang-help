#include<stdio.h>
int main(){
    int a=1;
        int b=2;
        scanf("%d %d",&a,&b);
    if(a>b){
        printf(">");
    }
    else if(a<b){
        printf("<");
    }
    else{
        printf("==");
    }
    return 0;
}
