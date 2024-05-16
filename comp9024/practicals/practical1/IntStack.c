#include "IntStack.h"
#include <assert.h>

typedef struct {
   int item[MAXITEMS];
   int  top;
} stackRep;                   

static stackRep stackObject;  

void StackInit() {            
   stackObject.top = -1;
}

int StackIsEmpty() {          
   return (stackObject.top < 0);
}

void StackPush(int a) {     
   assert(stackObject.top < MAXITEMS-1);
   stackObject.top++;
   int i = stackObject.top;
   stackObject.item[i] = a;
}

int StackPop() {             
   assert(stackObject.top > -1);
   int i = stackObject.top;
   int a = stackObject.item[i];
   stackObject.top--;
   return a;
}