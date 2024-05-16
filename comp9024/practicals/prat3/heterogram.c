#include <stdio.h>
#include <stdbool.h>

bool isHeterogram(char A[]){
    bool charSet[26] = {0};
    int i;

    for( i = 0; A[i]!='\0'; i++) {
        if (A[i] >= 'a' && A[i] <= 'z'){
            
            if(!charSet[A[i] - 'a'])
            charSet[A[i] -'a'] = 1;
        else 
        return false;
        
        }
        else if (A[i]>= 'A' && A[i]<= 'Z'){

            if(!charSet[A[i] -'A'])
            charSet[A[i] - 'A'] = 1;
        else
        return false;
        }
    }
    return true;
}

int main(){
    char str[64];
    printf("Enter a word or phrase: ");
    scanf("%[^\n]%*c",str);


    if (isHeterogram(str)) {
        printf("\"%s\" is a heterogram \n", str);
    }
    else {
        printf("\"%s\" is not a heterogram \n", str);
    }
    return 0;
}
