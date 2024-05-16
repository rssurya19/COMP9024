#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"


void dfscycle(Graph g, int v, bool visited[], bool *iscycle, int firstnode){
    visited[v] = true;
    int i;
    for (i = 0; i < numOfVertices(g); i++){
        if(adjacent(g,v,i)) {
            if (!visited[i]){
                dfscycle(g,i,visited,iscycle,v);
            }
            else if(i!= firstnode){
                *iscycle = true;
                return;
            } 
        }
    }
}
int main() {
    int n;
    printf("Enter the number of vertices:");
    scanf("%d", &n);
    Graph g = newGraph(n);
    int start,till;
    
    while(printf("Enter an edge (from):") && scanf("%d", &start) == 1 && printf("Enter an edge (to):") && scanf("%d", &till) ==1){
        if(start < 0 || start >= n || till< 0 || till >= n){
            break;
        }
        insertEdge(g,(Edge){start, till});
        
    }
    
    printf("Done.\n");



    bool visited[n];
    int i;
    for (i=0; i < n; i++){
        visited[i] = false;
    }

    bool iscycle =false;
    for(i=0;i<n;i++){
        if (!visited[i]){
            dfscycle(g,i,visited,&iscycle, -1);
            if (iscycle){
                printf("The graph has a cycle.\n");
                freeGraph(g);
                return 0;
            }
        }
    }

    printf("the graph is acyclic.\n");
    freeGraph(g);
    return 0;
}