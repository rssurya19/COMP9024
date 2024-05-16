// for each vertex v in the graph:
// degreeof_v = 0
// for each vertex w inthe fraph:
// if v and w are adjacent:
// degreeof_v++
// print degreeof_v

#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"

#define MAX_VERTICES 1000

int main(void) {
    int n;
    printf("Enter the number of vertices:");
    if (scanf("%d", &n) != 1 || n < 1 || n> MAX_VERTICES){
        printf("Invalid input \n");
        return 1;
    }
    Graph g = newGraph(n);

    int start, till;
    while (printf("Enter an edge (from): ") && scanf("%d", &start) == 1 &&
           printf("Enter an edge (to): ") && scanf("%d", &till) == 1) {
            if(start < 0 || start >= n || till < 0 || till >= n){
                printf("Invalid vertx number \n");
                continue;
                }
        Edge e = {start, till};
        insertEdge(g,e);
        }
    printf("Done.\n");
    for (int v = 0; v < n; v++) {
        int degree = 0;
        for (int w = 0; w < n; w++) {
            if (adjacent(g, v, w))
                degree++;
        }
        printf("Degree of node %d: %d\n", v, degree);
    }

     printf("3-cliques:\n");
    for (int v = 0; v < n; v++) {
        for (int u = v+1; u < n ; u++) {
            if (adjacent(g,v,u)){
                for (int w = u + 1; w < n; w++) {
                    if(adjacent(g,v,w) && adjacent(g,u,w)){
                        printf("%d-%d-%d\n", v, u, w);
                    }
                }
            }
    }
    }
     int num_edges = 0;
    for (int v = 0; v < n; v++) {
        for (int w = v + 1; w < n; w++) {
            if (adjacent(g, v, w))
                num_edges++;
        }
    }
    double density = (double)(2 * num_edges) / (n * (n));
    printf("Density: %.3f\n", density);

    freeGraph(g);

    return 0;
}