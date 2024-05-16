


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_TEXT_LENGTH 1024
#define TEXT_FORMAT_STRING "%[^\n]%*c"



int findIndex(char *alphabet, char c){
    int len = strlen(alphabet);
    for(int i=0; i<len; i++){
        if (alphabet[i] == c){
            return i;
        }
    }
    return -1;
}

int *lastOccurrence(char *pattern, char *alphabet){
    int pattern_len = strlen(pattern);
    int alphabet_len = strlen(alphabet);
    int *last = malloc(alphabet_len * sizeof(int));
    if(!last){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i=0;i<alphabet_len; i++){
        last[i]= -1;
    }

    for (int i=0;i<pattern_len;i++){
        last[findIndex(alphabet, pattern[i])] =i;
    }

    return last;
}

int BoyerMooreMatch(char *T, char *P, char *A){
    int *L =lastOccurrence(P,A);
    int n = strlen(T);
    int m=strlen(P);
    int i= m-1,j= m-1;

    while(i<n){
        if(T[i] == P[j]){
            if (j==0){
                return i;
            } else{
                i--;
                j--;
            }
        } else{
            int index =findIndex(A,T[i]);
            i= i+m - fmin(j, 1+L[index]);
            j = m-1;
        }
    }
        return -1;

}
int main(){
    printf("Enter alphabet: ");
    char alphabet[MAX_TEXT_LENGTH];
    scanf(TEXT_FORMAT_STRING,alphabet);
    printf("Enter text: ");
    char text[MAX_TEXT_LENGTH];
    scanf(TEXT_FORMAT_STRING, text);

    printf("Enter pattern: ");
    char pattern[MAX_TEXT_LENGTH];
    scanf(TEXT_FORMAT_STRING, pattern);

    printf("\n");
    
    int *L =lastOccurrence(pattern, alphabet);
    int alphabet_len = strlen(alphabet);
    for(int i=0;i<alphabet_len;i++){
        printf("L[%c]= %d\n",alphabet[i], L[i]);
    }

    printf("\n");

    int match_index = BoyerMooreMatch(text, pattern, alphabet);
    if(match_index == -1){
        printf("No match.\n");
    } else{
        printf("Match found at position %d. \n", match_index);
    }
    free(L);
    return 0;

}




