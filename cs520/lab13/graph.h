#ifndef GRAPH_H
#define GRAPH_H

#include <pthread.h>
#include <stdbool.h>

#define BRANCHING 4

typedef struct n {
    int nodeID;
    bool touched;
    int threadID;
    pthread_mutex_t lock;
    struct n* next[BRANCHING];
} node;

typedef struct {
    int size;
    node** graph;
} graph;

graph* build_graph(int size);
void print_graph(graph* g);
void print_tags(graph* g, int nthreads);
void destroy_graph(graph* g);


#endif
