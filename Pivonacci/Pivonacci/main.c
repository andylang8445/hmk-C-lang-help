//
//  main.c
//  Pivonacci
//
//  Created by Hongjun Yun on 2020-10-30.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int n;
    scanf("%d",&n);
    int n1=1,n2=1;
    for(int i=2;i<n;i++){
        int tmp=n1+n2;
        n1=n2;
        n2=tmp;
    }
    printf("%d",n2);
    return 0;
}
