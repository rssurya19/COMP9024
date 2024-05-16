#include <stdio.h>
#include <stdlib.h>
#include "IntStack.h"
#include "IntQueue.h"

int main(void) {
    int n;
    char str[BUFSIZ];

    QueueInit();

    printf("Enter a number: ");
    scanf("%s", str);
    n= atoi(str);
    if (n> 0){
        QueueEnqueue(n);
    }

    while (!QueueIsEmpty()) {
        printf("%d", QueueDequeue());
    }

    return 0;  

}