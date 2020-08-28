#include <stdio.h>
 
int main() {
    int n=5;
    scanf("%d", &n);
    for (int i = n; i > 0; --i) {
        printf("%d\n", i);
    }
    return 0;
}
