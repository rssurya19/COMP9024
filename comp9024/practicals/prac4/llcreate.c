#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} NodeT;

void freeLL(NodeT* list) {
    while (list != NULL) {
        NodeT* temp = list;
        list = list->next;
        free(temp);
    }
}

void showLL(NodeT* list) {
    while (list != NULL) {
        printf("%d", list->data);
        if (list->next != NULL) {
            printf("-->");
        }
        list = list->next;
    }
    printf("\n");
}

NodeT* joinLL(NodeT* list, int v) {
    NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = v;
    newNode->next = NULL;

    if (list == NULL) {
        return newNode;
    }

    NodeT* current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return list;
}

int main() {
    NodeT* all = NULL; 

    printf("Enter an integer: ");
    int num;
    while (scanf("%d", &num) == 1) {
        all = joinLL(all, num);
        printf("Enter an integer: ");
    }

    if (all != NULL) {
        printf("Done. List is ");
        showLL(all);
    } else {
        printf("Done.\n");
    }
    freeLL(all);

    return 0;
}