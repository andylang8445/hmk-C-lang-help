#include<stdio.h>
int main(){
    int N, n, k, l, m, p, count = 0;
    scanf("%d", &N);
    n=N ;
    while(1){
        k=n/10;
            m=n%10;
            l=(k+m)%10;
        count++;
        p=m*10+l;
        n=p;
        if(p==N)break;
    }
    printf("%d\n", count);
}
