#include<stdio.h>
int main(){
    int a=5;
    int b=8;
    int c=4;
    scanf("%d %d %d",&a,&b,&c);
    printf("%d\n",(a+b)%c);
    printf("%d\n",((a%c)+(b+c))%c);
    printf("%d\n",(a*b)%c);
    printf("%d\n",((a%c)*(b%c))%c);
    return 0;
}
