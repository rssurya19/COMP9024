#include <stdio.h>
int main(void) {
    int s1, s2, s3;
    scanf("%d %d %d", &s1, &s2, &s3);

    if (( s1 <= 0 || s2 <= 0 || s3 <= 0) && (s1+s2 >= s3)) {
        printf("Not a triangle \n");
    } else if ((s1 == s2 && s2==s3) && (s1+s2 >= s3)) {
        printf("Equilateral triangle \n");
    }  else if ((s1 == s2 || s2 == s3 || s1 == s3) && (s1+s2 >= s3)){
        printf("Isosceles triangle \n");
    } else {
        printf("Scalene triangle \n");
    }

    return 0;
}