#include <stdio.h>
#include <stdlib.h>
#include "IntStack.h"

int main(void) {
    int n;
    char str[BUFSIZ];

    StackInit();

    printf("Enter a number: ");
    scanf("%s", str);
    n= atoi(str);
    while (n > 0) {
        int r = n%2;
        StackPush(r);
        n/=2;    
        }

    while (!StackIsEmpty()) {
        printf("%d", StackPop());
    }

    return 0;  

}