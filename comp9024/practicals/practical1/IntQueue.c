#include "IntQueue.h"
#include <assert.h>

typedef struct {
   int item[MAXITEMS];
   int right;
   int left;
} queueRep;                   

static queueRep queueObject;  

void QueueInit() {           
   queueObject.right = -1;
   queueObject.left = 0;
}

int QueueIsEmpty() {          
   return (queueObject.right < queueObject.left);
}

void QueueEnqueue(int a) {     
   assert(queueObject.right< MAXITEMS-1);
   queueObject.right++;
   int i = queueObject.right;
   queueObject.item[i] = a;
}
 
int QueueDequeue() {             
   assert(queueObject.left> -1);
   int i = queueObject.left;
   int a = queueObject.item[i];
   queueObject.left++;
   return a;
}