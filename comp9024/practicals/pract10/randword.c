

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <length> <seed>\n", argv[0]);
        return 1;
    }
    int length = atoi(argv[1]);
    int seed = atoi(argv[2]);

    srand(seed);

    char* string = malloc((length + 1) * sizeof(char));
    for (int i =0; i < length; i++){
        string[i] = 'a' + rand()%26;
    }

    string[length] = '\0';
    printf("%s\n", string);
    free(string);
    return 0;
    }