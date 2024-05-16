
#include <stdio.h>
#include <stdbool.h>
#include "PQueue.h"

#define VERY_HIGH_VALUE 999999

void dijkstraSSSP(Graph g, Vertex source) {
    int dist[MAX_NODES];
    int pred[MAX_NODES];
    bool vSet[MAX_NODES];
    int s;

    PQueueInit();
    int nV = numOfVertices(g);
    for (s=0; s<nV; s++) {
        joinPQueue(s);
        dist[s] = VERY_HIGH_VALUE;
        pred[s] = -1;
        vSet[s] = true;
    }

    dist[source] = 0;

    while (!PQueueIsEmpty()) {
        Vertex u= leavePQueue(dist);
        vSet[u] = false;

        for (Vertex v=0; v<nV; v++){
            int weight = adjacent(g,u,v);
            if (weight >0 && vSet[v]){
                int alt =dist[u] + weight;
                if (alt < dist[v]){
                    dist[v] = alt;
                    pred[v] = u;
                    joinPQueue(v);
                }
            }
        }
    }

    for(Vertex i =0; i<nV; i++){
        if (dist[i] == VERY_HIGH_VALUE){
            printf("%d: no path\n", i);
        } else {
            printf("%d: distance =%d,shortest path: ", i, dist[i]);
            int current = i;
            int path[MAX_NODES];
            int pathL = 0;
            while(current!= -1){
                path[pathL++] = current;
                current = pred[current];
            }
            printf("%d", path[pathL -1]);
            for(int j = pathL - 2; j>=0; j--){
                printf("-%d",path[j]);
            }
            printf("\n");
        }
    }
}

void reverseEdge(Edge *e) {
    Vertex temp = e->v;
    e->v = e->w;
    e->w = temp;
}

int main(void) {
    Edge e;
    int n, source;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph g = newGraph(n);

    printf("Enter the source node: ");
    scanf("%d", &source);
    printf("Enter an edge (from): ");
    while(scanf("%d", &e.v) ==1) {
        printf("Enter an edge (to): ");
        scanf("%d",&e.w);
        printf("Enter the weight: ");
        scanf("%d", &e.weight );
        insertEdge(g,e);
        reverseEdge(&e);
        insertEdge(g,e);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");

    dijkstraSSSP(g, source);
    freeGraph(g);
    return 0;
}