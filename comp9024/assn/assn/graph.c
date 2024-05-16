#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "list.h"
#include <limits.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include "dijkstra.h"
#include "pagerank.h"

#define MAX_VERTICES 100 

#define DAMPING_FACTOR 0.85
#define EPSILON 0.00001

char *my_strdup(const char *str) {
    if ((void *)str == NULL) return NULL;
    
    size_t len = strlen(str) + 1; 
    char *dup = (char *)malloc(len);
    if (dup != NULL) {
        memcpy(dup, str, len);
    }
    return dup;
}


// Define struct for graph representation
typedef struct Edge {
    string last;
    size_t weight;
    struct Edge *next;
    } Edge;
// Define struct for vertex representation
typedef struct Vertex {
    string label;
    Edge *edges;
    struct Vertex *next;
    size_t num_edges;
    double previous_rank;
    double page_rank;
    bool visited;
    int distance;
    int predecessor;
    } Vertex;

// Define struct for graph representation
typedef struct Graph_Repr {
    Vertex *Top_vertices;
    size_t nv;
    list *adjacency_lists;
    struct dijkstraVertex *dijkstra_v;
    } Graph_Repr;

typedef struct{
    char *label;
    double page_rank;
}NodeInfo;

// Create a new graph
graph graph_create(void) {
    graph new = (graph)malloc(sizeof(Graph_Repr));
    if (new != NULL) {
        new->Top_vertices = NULL;
        new->nv = 0;
        
        }
    return new;
}

// Destroy the graph and free all memory associated with it
void graph_destroy(graph g) {
    if (g != NULL) {
        Vertex *present_vertex = g->Top_vertices;
        Vertex *nextV = NULL;
        while (present_vertex != NULL){
            nextV = present_vertex->next;
            Edge *present_edge = present_vertex->edges;
            Edge *next_edge = NULL;
            while (present_edge != NULL) {
                next_edge = present_edge->next;
                free(present_edge->last);
                free(present_edge);
                present_edge = next_edge;
                }
                free(present_vertex->label);
                free(present_vertex);
                present_vertex = nextV;
        } free(g);
    }
}


// Show the contents of the graph
void graph_show(graph g, FILE *f, list ignore_list) {
    if (g == NULL || f == NULL || ignore_list == NULL || g->Top_vertices == NULL) return;
    list visited_vertices = list_create();
    Vertex *present_vertex = g->Top_vertices;
    while (present_vertex != NULL) {
        if (!list_contains(ignore_list, present_vertex->label) && !list_contains(visited_vertices, present_vertex->label)) {
            fprintf(f, "%s\n", present_vertex->label);
            list_add(visited_vertices, present_vertex->label); 
        }
        present_vertex = present_vertex->next;
    }

    present_vertex = g->Top_vertices;
    while (present_vertex != NULL) {
        if (!list_contains(ignore_list, present_vertex->label)) {
            Edge *present_edge = present_vertex->edges;
            while (present_edge != NULL) {
                if (!list_contains(ignore_list, present_edge->last)) {
                    fprintf(f, "%s %s %zu\n", present_vertex->label, present_edge->last, present_edge->weight);
                }
                present_edge = present_edge->next;
            }
        }
        present_vertex = present_vertex->next;
    }
    list_destroy(visited_vertices);
}

void graph_add_vertex(graph g, string label) {
    if (g == NULL || label == NULL) return;

    if (!graph_has_vertex(g, label)) {
        Vertex *new_vertex = (Vertex *)malloc(sizeof(Vertex));
        new_vertex->label = my_strdup(label);
        new_vertex->edges = NULL;
        new_vertex->next = NULL;
        if (g->Top_vertices == NULL) {
            g->Top_vertices = new_vertex;
        } else {
            Vertex *present = g->Top_vertices;
            while (present->next != NULL) {
                present = present->next;
            }
            present->next = new_vertex;
        }

    }
}


// Check if a vertex exists in the graph
bool graph_has_vertex(graph g, string label) {
    if (g == NULL || label == NULL) return false;
    Vertex *present_vertex = g->Top_vertices;
    while (present_vertex != NULL) {
        if (strcmp(present_vertex->label, label) == 0) return true;
        present_vertex = present_vertex->next;
    }

    return false;
}

size_t graph_vertices_count(graph g) {
    if (g == NULL) return 0;

    size_t count = 0;
    Vertex *present_vertex = g->Top_vertices;
    while (present_vertex != NULL) {
        count++;
        present_vertex = present_vertex->next;
    }
    return count;
}

// Add a weighted directed edge to the graph
void graph_add_edge(graph g, string source, string last, size_t weight) {
    if (g == NULL || source == NULL || last == NULL || weight == 0 ||
        !graph_has_vertex(g, source) || !graph_has_vertex(g, last) ||
        graph_has_edge(g, source, last)) return;

    Vertex *src_vertex = g->Top_vertices;
    while (src_vertex != NULL && strcmp(src_vertex->label, source) != 0) {
        src_vertex = src_vertex->next;
    }
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    new_edge->last = my_strdup(last);
    new_edge->weight = weight;
    new_edge->next = NULL;
    if (src_vertex->edges == NULL) {
        src_vertex->edges = new_edge;
    } else {
        Edge *present_edge = src_vertex->edges;
        while (present_edge->next != NULL) {
            present_edge = present_edge->next;
        }
        present_edge->next = new_edge;
    }
}

// Check if an edge exists between two vertices in the graph
bool graph_has_edge(graph g, string source, string last) {
    if (g == NULL || source == NULL || last == NULL) return false;
    
    if (g->Top_vertices == NULL) return false;
    Vertex *src_vertex = g->Top_vertices;
    while (src_vertex != NULL && strcmp(src_vertex->label, source) != 0) {
        src_vertex = src_vertex->next;
    }
    if (src_vertex == NULL || src_vertex->edges == NULL) return false;
    Edge *present_edge = src_vertex->edges;
    while (present_edge != NULL) {
        if (strcmp(present_edge->last, last) == 0) {
            return true; 
        }
        present_edge = present_edge->next;
    }
    return false; 
}

// Get the weight of an edge between two vertices
size_t graph_get_edge(graph g, string source, string last) {
    if (g == NULL || source == NULL || last == NULL ||
        !graph_has_vertex(g, source) || !graph_has_vertex(g, last)) return 0;

    Vertex *src_vertex = g->Top_vertices;
    while (src_vertex != NULL && strcmp(src_vertex->label, source) != 0) {
        src_vertex = src_vertex->next;
    }

    if (src_vertex != NULL) {
        Edge *present_edge = src_vertex->edges;
        while (present_edge != NULL && strcmp(present_edge->last, last) != 0) {
            present_edge = present_edge->next;
        }
        if (present_edge != NULL) {
            return present_edge->weight;
        }
    }
    return 0;  
}

size_t vertex_edge_count(Edge *edge_list) {
    size_t count = 1;
    Edge *present_edge = edge_list;
    while (present_edge != NULL) {
        count++;
        present_edge = present_edge->next;
    }
    return count;
}
// Get the number of outgoing edges from a particular vertex in the graph
size_t graph_edges_count(graph g, string label) {
    if (g == NULL || label == NULL || !graph_has_vertex(g, label)) return 0;

    Vertex *vertex = g->Top_vertices;
    while (vertex != NULL && strcmp(vertex->label, label) != 0) {
        vertex = vertex->next;
    }

    if (vertex != NULL) {
        return vertex_edge_count(vertex->edges);
    }
    return 0;  
}

void vertex_set_edge(Edge *edge_list, string last, size_t weight) {
    if (edge_list == NULL || last == NULL) return;

    Edge *present_edge = edge_list;
    while (present_edge != NULL) {
        if (strcmp(present_edge->last, last) == 0) {
            present_edge->weight = weight;
            return;
        }
        present_edge = present_edge->next;
    }
}

// Implementation of graph_vertices_count_with_ignore
size_t graph_vertices_count_with_ignore(graph g, list ignore_list)
{
    if (g == NULL || g->Top_vertices == NULL)
        return 0;

    Vertex *present = g->Top_vertices;
    int count = 0;

    while (present != NULL)
    {
        if (list_contains(ignore_list, present->label) == false)
        {
            count++;
        }
        present = present->next;
    }
    return count;
}

// Check if a vertex has an edge connecting it to a destination
bool vertex_has_edge(Edge *edge_list, string last) {
    if (edge_list == NULL || last == NULL) return false;

    Edge *present_edge = edge_list;
    while (present_edge != NULL) {
        if (strcmp(present_edge->last, last) == 0) {
            return true;
        }
        present_edge = present_edge->next;
    }
    return false;
}


size_t V_Ecount_ignore(Edge *edge_list, list ignore_list)
{
    if (edge_list == NULL || ignore_list == NULL)
        return 0;

    Edge *present_edge = edge_list;
    size_t count = 0;

    while (present_edge != NULL)
    {
        if (list_contains(ignore_list, present_edge->last) == false)
        {
            count++;
        }
        present_edge = present_edge->next;
    }
    return count;
}


/////////////////////////// PageRank /////////////////////////////////
// Implementation of page_rank_vertices
void page_rank_vertices(graph g, Vertex *V, double damping_factor, list ignore_list)
{
    if (g == NULL || V == NULL || ignore_list == NULL)
        return;
    
    Vertex *I = NULL;
    I = g->Top_vertices;
    if (I == NULL)
        return;

    double n;
    while (I != NULL)
    {
        if (list_contains(ignore_list, I->label) == false && graph_has_edge(g, I->label, V->label))
        {
            n = V_Ecount_ignore(I->edges, ignore_list);
            V->page_rank = V->page_rank + ((damping_factor * I->previous_rank) / n);
        }
        I = I->next;
    }
}

// Implementation of graph_pagerank
void graph_pagerank(graph g, double damping_factor, double epsilon, list ignore_list)
{
    if (g == NULL || g->Top_vertices == NULL)
        return;

    double n = graph_vertices_count_with_ignore(g, ignore_list);

    Vertex *V = g->Top_vertices;
    if (V == NULL)
        return;

    while (V != NULL)
    {
        V->previous_rank = 0.0;
        V->page_rank = 1.0 / n;
        V = V->next;
    }

    bool converged;
    do
    {
        converged = true;

        V = g->Top_vertices;
        if (V == NULL)
            return;
        while (V != NULL)
        {
            V->previous_rank = V->page_rank;
            V = V->next;
        }

        double sink_rank = 0;
        V = g->Top_vertices;
        if (V == NULL)
            return;
        while (V != NULL)
        {
            if (list_contains(ignore_list, V->label) == false && V_Ecount_ignore(V->edges, ignore_list) == 0)
            {
                sink_rank = sink_rank + (damping_factor * (V->previous_rank / n));
            }
            V = V->next;
        }

        V = g->Top_vertices;
        if (V == NULL)
            return;
        while (V != NULL)
        {
            if (list_contains(ignore_list, V->label) == false)
            {
                V->page_rank = sink_rank + ((1 - damping_factor) / n);
                page_rank_vertices(g, V, damping_factor, ignore_list);
            }

            if (list_contains(ignore_list, V->label) == false && fabs(V->page_rank - V->previous_rank) > epsilon)
            {
                converged = false;
            }
            V = V->next;
        }
    } while (!converged);
}

// Implementation of compare_page_rank
int compare_page_rank(const void *a, const void *b)
{
    const NodeInfo *nodeA = (const NodeInfo *)a;
    const NodeInfo *nodeB = (const NodeInfo *)b;

    if (nodeA->page_rank > nodeB->page_rank)
        return -1; 
    if (nodeA->page_rank < nodeB->page_rank)
        return 1;
    return 0;
}

// Implementation of graph_show_pagerank
void graph_show_pagerank(graph g, FILE *f, list ignore_list)
{
    if (g == NULL || ignore_list == NULL)
        return;

    int num_nodes = 0;
    Vertex *present_vertex = g->Top_vertices;
    while (present_vertex != NULL)
    {
        if (list_contains(ignore_list, present_vertex->label) == false)
        {
            num_nodes++;
        }
        present_vertex = present_vertex->next;
    }

    NodeInfo *node_info = malloc(num_nodes * sizeof(NodeInfo));
    if (node_info == NULL)
    {
        fprintf(stderr, "Error allocating memory\n");
        return;
    }

    int i = 0;
    present_vertex = g->Top_vertices;
    while (present_vertex != NULL)
    {
        if (list_contains(ignore_list, present_vertex->label) == false)
        {
            node_info[i].label = present_vertex->label;
            node_info[i].page_rank = present_vertex->page_rank;
            i++;
        }
        present_vertex = present_vertex->next;
    }

    qsort(node_info, num_nodes, sizeof(NodeInfo), compare_page_rank);

    for (i = 0; i < num_nodes; i++)
    {
        if (f != NULL)
        {
            fprintf(f, "%s: %.3f\n", node_info[i].label, node_info[i].page_rank);
        }
        else
        {
            printf("%s: %.3f\n", node_info[i].label, node_info[i].page_rank);
        }
    }

    free(node_info);
}

//////////////dijkstra///////////////////////

void graph_initialize_dijkstra_v(graph g) {
    Vertex *present_vertex = g->Top_vertices;
    while (present_vertex != NULL) {
        
        present_vertex->predecessor = -1;
        present_vertex->distance = INT_MAX;
        present_vertex->visited = false;
        present_vertex = present_vertex->next;
    }
}

Vertex *graph_min_distance_vertex(graph g, list ignore_list) {
    int min_distance = INT_MAX;
    Vertex *min_vertex = NULL;

    Vertex *present_vertex = g->Top_vertices;
    while (present_vertex != NULL) {
        if (!present_vertex->visited && present_vertex->distance < min_distance && !list_contains(ignore_list, present_vertex->label)) {
            min_distance = present_vertex->distance;
            min_vertex = present_vertex;
        }
        present_vertex = present_vertex->next;
    }

    return min_vertex;
}
Vertex *graph_get_vertex(graph g, string label) {
    if (g == NULL || label == NULL) return NULL;

    Vertex *present_vertex = g->Top_vertices;
    while (present_vertex != NULL) {
        if (strcmp(present_vertex->label, label) == 0) {
            return present_vertex;
        }
        present_vertex = present_vertex->next;
    }

    return NULL; 
}

int graph_vertex_index(graph g, string label) {
    if (g == NULL || label == NULL) return -1;

    Vertex *present_vertex = g->Top_vertices;
    int index = 0;
    while (present_vertex != NULL) {
        if (strcmp(present_vertex->label, label) == 0) {
            return index;
        }
        present_vertex = present_vertex->next;
        index++;
    }

    return -1; 
}

void graph_shortest_path(graph g, string source_vertex, list ignore_list) {
    if (g == NULL || source_vertex == NULL || !graph_has_vertex(g, source_vertex)) {
        return;
    }

    Vertex *source_vertex_ptr = graph_get_vertex(g, source_vertex);

    graph_initialize_dijkstra_v(g);

    source_vertex_ptr->distance = 0;

    for (size_t count = 0; count < g->nv - 1; count++) {
        Vertex *u = graph_min_distance_vertex(g, ignore_list);
        if (u == NULL) {
            break;
        }
        u->visited = true;

        Vertex *present_vertex = g->Top_vertices;
        while (present_vertex != NULL) {
            if (!present_vertex->visited && graph_has_edge(g, u->label, present_vertex->label)) {
                size_t weight = graph_get_edge(g, u->label, present_vertex->label);
                if (u->distance != INT_MAX && u->distance + weight < present_vertex->distance) {
                    present_vertex->distance = u->distance + weight;
                    present_vertex->predecessor = graph_vertex_index(g, u->label);
                }
            }
            present_vertex = present_vertex->next;
        }
    }
}
string graph_vertex_label_by_index(graph g, int index) {
    if (g == NULL || index < 0) return NULL;

    Vertex *present_vertex = g->Top_vertices;
    int present_index = 0;
    while (present_vertex != NULL) {
        if (present_index == index) {
            return present_vertex->label;
        }
        present_vertex = present_vertex->next;
        present_index++;
    }

    return NULL; 
}
void graph_show_path(graph g, FILE *f, string last, list ignore_list) {
    if (g == NULL || last == NULL || !graph_has_vertex(g, last)) {
        return;
    }

    Vertex *last_vertex = graph_get_vertex(g, last);

    if (last_vertex->distance == INT_MAX) {
        return;
    }

    list path = list_create();
    Vertex *present_vertex = last_vertex;
    while (present_vertex != NULL) {
        string vertex_name = present_vertex->label;
        list_push(path, vertex_name);

        int predecessor_index = present_vertex->predecessor;
        if (predecessor_index != -1) {
            present_vertex = graph_get_vertex(g, graph_vertex_label_by_index(g, predecessor_index));
        } else {
            break;
        }
    }

    string previous_V = NULL;
    while (!list_is_empty(path)) {
        string vertex_name = (string)list_pop(path);
        if (previous_V != NULL) {
            if (f != NULL) {
                fprintf(f, "\n-> ");
            } else {
                printf(" \n-> ");
            }
        }
        if (f != NULL) {
            fprintf(f, "%s", vertex_name);
        } else {
            printf("%s", vertex_name);
        }
        previous_V = vertex_name;
    }

    list_destroy(path);
}

