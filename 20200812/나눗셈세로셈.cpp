#include<stdio.h>
int main(){
    int a=472;
    int b=385;
    scanf("%d %d",&a,&b);
    printf("%d\n",a*(b%10));
    printf("%d\n",a*(b%100-(b%10))/10);
    printf("%d\n",a*(b-b%100)/100);
    printf("%d\n",a*b);
           return 0;
}
