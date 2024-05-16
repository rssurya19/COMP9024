#include <stdio.h>
#include <stdlib.h>
#include "WGraph.h"

// double popularityRank(Graph g, int v, int numOfVertices);
double popularityRank(Graph g, int v, int numOfVertices) {
    int inDegree = 0, outDegree = 0;
    for(int i =0; i<numOfVertices; i++) {
        if (adjacent(g, i,v) >0){
            inDegree++;
        }
        if (adjacent(g,v,i) > 0){
            outDegree++;
        }
    }
    return outDegree == 0 ? (double)inDegree / 0.5: (double)inDegree / outDegree;
}
int main(void) {
    int numOfVertices;
    printf("Enter the number of vertices: ");
    if (scanf("%d", &numOfVertices) !=1) {
        printf("Invalid input.\n");
        return 1;
    }

    Graph g = newGraph(numOfVertices);
    int from,to;
    while(1) {
        printf("Enter an edge (from): ");
        if (scanf("%d", &from) !=1) {
            printf("Done.\n");
            break;
        }
        printf("Enter an edge (to): ");
        if (scanf("%d", &to) !=1) {
            printf("Invalid input.\n");
            freeGraph(g);
            return 1;
        }
        Edge e ={from,to, 1};
        insertEdge(g,e);
    }
    printf("\nPopularity ranking:\n");

    double ranks[numOfVertices];
    int vertices[numOfVertices];
    for (int i = 0; i < numOfVertices; i++) {
        vertices[i] = i;
        ranks[i] = popularityRank(g,i,numOfVertices);
    }
    for (int i=0; i< numOfVertices - 1;i++){
        for (int j = 0; j<numOfVertices-i-1; j++){
            if (ranks[j] < ranks[j+1]){
                double temp = ranks[j];
                ranks[j] = ranks[j+1];
                ranks[j+1] = temp;
                int tempv =vertices[j];
                vertices[j] = vertices[j+1];
                vertices[j+1] = tempv;
            }
        }
    }


    for (int i = 0; i <numOfVertices; i++){

        printf("%d %.1f\n", vertices[i], ranks[i]);
    }
    freeGraph(g);
    return 0;
}



// #include <stdio.h>
// #include <stdlib.h>
// #include "WGraph.h"

// // Function to calculate the popularity rank for a vertex
// double popularityRank(Graph g, int v, int numOfVertices) {
//     int inDegree = 0, outDegree = 0;
//     for(int i = 0; i < numOfVertices; i++) {
//         if (adjacent(g, i, v) > 0) {
//             inDegree++;
//         }
//         if (adjacent(g, v, i) > 0) {
//             outDegree++;
//         }
//     }
//     return outDegree == 0 ? (double)inDegree / 0.5 : (double)inDegree / outDegree;
// }

// int main(void) {
//     int numOfVertices;
//     printf("Enter the number of vertices: ");
//     if (scanf("%d", &numOfVertices) != 1) {
//         printf("Invalid input.\n");
//         return 1;
//     }

//     Graph g = newGraph(numOfVertices);
//     int from, to;
//     while (1) {
//         printf("Enter an edge (from): ");
//         if (scanf("%d", &from) != 1) {
//             printf("Done.\n");
//             break;
//         }
//         printf("Enter an edge (to): ");
//         if (scanf("%d", &to) != 1) {
//             printf("Invalid input.\n");
//             freeGraph(g);
//             return 1;
//         }
//         Edge e = {from, to, 1};
//         insertEdge(g, e);
//     }

//     printf("\nPopularity ranking:\n");

//     // Arrays to store vertex indices and their corresponding popularity ranks
//     int vertices[numOfVertices];
//     double ranks[numOfVertices];

//     // Calculate popularity ranks for each vertex
//     for (int i = 0; i < numOfVertices; i++) {
//         vertices[i] = i; // Store vertex index
//         ranks[i] = popularityRank(g, i, numOfVertices); // Calculate popularity rank
//     }

//     // Bubble sort ranks array and corresponding vertex indices in decreasing order of popularity
//     for (int i = 0; i < numOfVertices - 1; i++) {
//         for (int j = 0; j < numOfVertices - i - 1; j++) {
//             if (ranks[j] < ranks[j + 1]) {
//                 // Swap ranks
//                 double tempRank = ranks[j];
//                 ranks[j] = ranks[j + 1];
//                 ranks[j + 1] = tempRank;
//                 // Swap corresponding vertex indices
//                 int tempVertex = vertices[j];
//                 vertices[j] = vertices[j + 1];
//                 vertices[j + 1] = tempVertex;
//             }
//         }
//     }

//     // Print popularity rankings
//     for (int i = 0; i < numOfVertices; i++) {
//         printf("%d %.1f\n", vertices[i], ranks[i]);
//     }

//     freeGraph(g);
//     return 0;
// }
