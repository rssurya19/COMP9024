#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* swap the values of two integer variables */
void swap(int *p, int *q) {
   int temp = *p;
   *p = *q;
   *q = temp;
}

/* copy the values of integer array a[] to b[] */
void copy(int a[], int b[], int size) {
   int i;
   for (i = 0; i < size; i++) {
      b[i] = a[i];
   }
}

/* print all the values of a dynamic integer array */
void print(int *b, int size) {
   int i;
   for (i = 0; i < size; i++) {
      printf("%d", b[i]);
   }
   putchar('\n');
   free(b);
}

/* DO NOT MODIFY ANY OF THE CODE ABOVE THIS LINE */

void f1(void) {
   int ar[3] = {10, 20, 30};
   int *cp = malloc(3 * sizeof(int));
   assert(cp != NULL);
   copy(ar, cp, 3);
   print(cp, 3);
}

void f2(void) {
   int a = 9024;
   int *c = malloc(sizeof(int));
   assert(c != NULL);
   *c = 2024;
   swap(&a, c);
   printf("%d %d\n", a, *c);
   free(c);
}

void f3(void) {
   int ar[2] = {90, 24};
   int *cp = malloc(2 * sizeof(int));
   assert(cp != NULL);
   copy(ar, cp, 2);
   printf("%d %d\n", cp[0], cp[1]);
   free(cp);
}

void f4(void) {
   int ar[3] = {90, 24, 42};
   int *cp = malloc(3 * sizeof(int));
   assert(cp != NULL);
   copy(ar, cp, 3);
   print(cp, 3);
}

void f5(void) {
   int ar[2] = {90, 24};
   int *cp = malloc(2 * sizeof(int));
   assert(cp != NULL);
   copy(ar, cp, 2);
   print(cp, 2);
}

void f6(void) {
   int ar[3] = {2, 1, 0};
   int *cp = malloc(3 * sizeof(int));
   assert(cp != NULL);
   copy(ar, cp, 2);
   print(cp, 3);
//    free(cp);
}

void f7(void) {
   int *cp = malloc(sizeof(int));
   assert(cp != NULL);
   *cp = 90;
   int a[1] = {24};
   swap(&a[0], cp);
   printf("%d %d\n", a[0], *cp);
   free(cp);
}

void f8(void) {
   int a = 90;
   int *c = malloc(sizeof(int));
   assert(c != NULL);
   *c = 24;
   swap(&a, c);
   printf("%d %d\n", a, *c);
   free(c);
}


int main(void) {
   printf("f1: ");
   f1();
   printf("f2: ");
   f2();
   printf("f3: ");
   f3();
   printf("f4: ");
   f4();
   printf("f5: ");
   f5();
   printf("f6: ");
   f6();
   printf("f7: ");
   f7();
   printf("f8: ");
   f8();

   return 0;
}