
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BSTree.h"
#define MAX_INPUT_LENGTH 100

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

typedef struct Node {
   int  data;
   Tree left, right;
} Node;

// make a new node containing data
Tree newNode(Item it) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   data(new) = it;
   left(new) = right(new) = NULL;
   return new;
}

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++)
	 putchar('\t');            // TAB character
      printf("%d\n", data(t));
      showTreeR(left(t), depth+1);
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}

// compute height of Tree
int TreeHeight(Tree t) {

   if (t == NULL)
      return -1;
   else {
      int L_maxheight = TreeHeight(left(t));
      int R_maxheight = TreeHeight(right(t));
      if(L_maxheight > R_maxheight)
         return L_maxheight +1;
      else 
         return R_maxheight +1;
   }

}

// count #nodes in Tree
int TreeNumNodes(Tree t) {
    if (t == NULL)
      return 0;
    else
      return 1 + TreeNumNodes(left(t)) + TreeNumNodes(right(t));
}

// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return false;
   else if (it < data(t))
      return TreeSearch(left(t), it);
   else if (it > data(t))
      return TreeSearch(right(t), it);
   else                                 // it == data(t)
      return true;
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it) {
   if (t == NULL)
      t = newNode(it);
   else if (it < data(t))
      left(t) = TreeInsert(left(t), it);
   else if (it > data(t))
      right(t) = TreeInsert(right(t), it);
   return t;
}

Tree joinTrees(Tree t1, Tree t2) {
   if (t1 == NULL)
      return t2;
   else if (t2 == NULL)
      return t1;
   else {
      Tree curr = t2;
      Tree parent = NULL;
      while (left(curr) != NULL) {    // find min element in t2
	 parent = curr;
	 curr = left(curr);
      }
      if (parent != NULL) {
	 left(parent) = right(curr);  // unlink min element from parent
	 right(curr) = t2;
      }
      left(curr) = t1;
      return curr;                    // min element is new root
   }
}

// delete an item from a Tree
Tree TreeDelete(Tree t, Item it) {
   if (t != NULL) {
      if (it < data(t))
	 left(t) = TreeDelete(left(t), it);
      else if (it > data(t))
	 right(t) = TreeDelete(right(t), it);
      else {
	 Tree new;
	 if (left(t) == NULL && right(t) == NULL) 
	    new = NULL;
	 else if (left(t) == NULL)    // if only right subtree, make it the new root
	    new = right(t);
	 else if (right(t) == NULL)   // if only left subtree, make it the new root
	    new = left(t);
	 else                         // left(t) != NULL and right(t) != NULL
	    new = joinTrees(left(t), right(t));
	 free(t);
	 t = new;
      }
   }
   return t;
}

Tree rotateRight(Tree n1) {
   if (n1 == NULL || left(n1) == NULL)
      return n1;
   Tree n2 = left(n1);
   left(n1) = right(n2);
   right(n2) = n1;
   return n2;
}

Tree rotateLeft(Tree n2) {
   if (n2 == NULL || right(n2) == NULL)
      return n2;
   Tree n1 = right(n2);
   right(n2) = left(n1);
   left(n1) = n2;
   return n1;
}

Tree insertAtRoot(Tree t, Item it) { 
   if (t == NULL) {
      t = newNode(it);
   } else if (it < data(t)) {
      left(t) = insertAtRoot(left(t), it);
      t = rotateRight(t);
   } else if (it > data(t)) {
      right(t) = insertAtRoot(right(t), it);
      t = rotateLeft(t);
   }
   return t;
}

int TreeWidth(Tree t) {
    int numNodes = TreeNumNodes(t);
    return 3 * numNodes;
}

// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         printf("Usage: %s <list of integers>\n", argv[0]);
//         return 1;
//     }

//     Tree t = newTree();

//     // Insert values into the tree from command-line arguments
//     for (int i = 1; i < argc; i++) {
//         int value = atoi(argv[i]);
//         t = TreeInsert(t, value);
//     }

//     // Calculate and print the height of the tree
//     int height = TreeHeight(t);
//     printf("Tree Height: %d\n", height);

//     // Calculate and print the width of the tree
//     int width = TreeWidth(t);
//     printf("Tree Width: %d\n", width);

//     // Free memory associated with the tree
//     freeTree(t);

//     return 0;
// }