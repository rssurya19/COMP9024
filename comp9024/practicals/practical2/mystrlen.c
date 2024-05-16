#include "mystrlen.h"

int mystrlen(char *s) {
    int a = 0; 
    while (*s!='\0' && a < MAXLEN) {
        a++;
        s++;
    }
    return a; 
}