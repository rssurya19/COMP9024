// Priority Queue ADO header ... COMP9024 24T1
#ifndef PQUEUE_H
#define PQUEUE_H
#include "WGraph.h"
#include <stdbool.h>

#define MAX_NODES 1000

void   PQueueInit();
void   joinPQueue(Vertex);
Vertex leavePQueue(int[]);
bool   PQueueIsEmpty();

#endif