#include<stdio.h>
int main(){
    int n=2,m;
    scanf("%d",&n);
    for(m=1;m<=9;m++){
    printf("%d * %d = %d\n",n,m,(n*m));
    }
    return 0;
}
