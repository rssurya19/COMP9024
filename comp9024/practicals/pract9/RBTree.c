#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "RBTree.h"

#define PRINT_COLOUR_RED   "\x1B[31m"
#define PRINT_COLOUR_RESET "\x1B[0m"

#define data(tree)   ((tree)->data)
#define left(tree)   ((tree)->left)
#define right(tree)  ((tree)->right)
#define colour(tree) ((tree)->colour)
#define isRed(tree)  ((tree) != NULL && (tree)->colour == RED)

typedef enum {RED, BLACK} Colr;

typedef struct Node {
    int  data;
    Colr colour;
    struct Node *left, *right;
} Node;

Tree newTree() {
    return NULL;
}

Tree newNode(Item it) {
    Tree new = malloc(sizeof(Node));
    assert(new != NULL);
    data(new) = it;
    colour(new) = RED;
    left(new) = right(new) = NULL;
    return new;
}

Tree rotateRight(Tree);
Tree rotateLeft(Tree);

Tree insertRB(Tree tree, Item item, bool inRight) {
    if (tree == NULL) {
        return newNode(item);
    }

    if (item == data(tree)) {
        return tree;
    }

    if (left(tree) != NULL && right(tree) != NULL && isRed(left(tree)) && isRed(right(tree))) {

        colour(tree) = RED;
        colour(left(tree)) = BLACK;
        colour(right(tree)) = BLACK;
    }

    if (item < data(tree)) {
        left(tree) = insertRB(left(tree), item, false);
        if (isRed(tree) && isRed(left(tree)) && inRight) {
           tree = rotateRight(tree);
        }
        if (isRed(left(tree)) && isRed(left(left(tree)))) {
            tree = rotateRight(tree);
            colour(tree) = BLACK;
            colour(right(tree)) = RED;
        }
    } else {
        right(tree) = insertRB(right(tree), item, true);
        if (isRed(tree) && isRed(right(tree)) && !inRight) {
           tree = rotateLeft(tree);
        }
        if (isRed(right(tree)) && isRed(right(right(tree)))) {
           tree = rotateLeft(tree);
           colour(tree) = BLACK;
           colour(left(tree)) = RED;
        }
     }

    return tree;
}

Tree TreeInsert(Tree t, Item it) {

    t = insertRB(t, it, false);
    colour(t) = BLACK;
    return t;
}

bool TreeSearch(Tree t, Item it) {
    if (t == NULL)
        return false;
    else if (it < data(t))
        return TreeSearch(left(t), it);
    else if (it > data(t))
        return TreeSearch(right(t), it);
    else
        return true;
}

Tree rotateRight(Tree n1) {
    if (n1 == NULL || left(n1) == NULL)
        return n1;
    Tree n2 = left(n1);
    left(n1) = right(n2);
    right(n2) = n1;
    colour(n2) = colour(n1);
    colour(n1) = RED;
    return n2;
}

Tree rotateLeft(Tree n2) {
    if (n2 == NULL || right(n2) == NULL)
        return n2;
    Tree n1 = right(n2);
    right(n2) = left(n1);
    left(n1) = n2;
    colour(n1) = colour(n2);
    colour(n2) = RED;
    return n1;
}

void freeTree(Tree t) {
    if (t != NULL) {
        freeTree(left(t));
        freeTree(right(t));
        free(t);
    }
}

void showTreeR(Tree t, int depth) {
    if (t != NULL) {
        showTreeR(right(t), depth+1);
        int i;
        for (i = 0; i < depth; i++)
            putchar('\t');
        if (isRed(t))
            printf("%s%d%s\n", PRINT_COLOUR_RED, data(t), PRINT_COLOUR_RESET);
        else
            printf("%d\n", data(t));
        showTreeR(left(t), depth+1);
    }
}

void showTree(Tree t) {
    showTreeR(t, 0);
}



