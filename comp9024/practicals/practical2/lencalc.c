#include <stdio.h>
#include "mystrlen.h"

int main(void) {
    char s[MAXLEN];
    int a;

    while(1) {
        printf("Enter a string:");
        if(fgets(s,sizeof(s), stdin) == NULL){
            break;
        }

        if(s[0] == '\n'){
            printf("Goodbye!\n");

            break;
        }


        a = mystrlen(s);
        printf("%d\n",a);
    }
    
    return 0;
}