#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"

void malloc_check(void* p){
    if(p == NULL)
    {
	fprintf(stderr, "malloc failed\n");
	exit(1);
    }
}

graph* build_graph(int size){
    graph* g = malloc(sizeof(graph));
    malloc_check(g);
    g->size = size;
    g->graph = malloc(sizeof(void*) * size);
    malloc_check(g->graph);
    for(int i = 0; i < size; i++){
	g->graph[i] = malloc(sizeof(node));
	malloc_check(g->graph[i]);
	pthread_mutex_init(&g->graph[i]->lock, NULL);
	g->graph[i]->nodeID = i;
	g->graph[i]->touched = false;
	g->graph[i]->threadID = -1;
    }

    for(int i = 0; i < size; i++){
	for(int j = 0; j < BRANCHING; j++){
	    int next =  (rand() % size);
	    /* if(next == i && i != 0){ */
	    /* 	next --; */
	    /* } else if(next == i && i == 0){ */
	    /* 	next ++; */
	    /* } */

	    g->graph[i]->next[j] = (g->graph[next]);
	}
    }
    return g;
}

void destroy_graph(graph* g){
    for(int i = 0; i < g->size; i++){
	free(g->graph[i]);
    }
    free(g->graph);
    free(g);
    return;
}

void print_node(node* n){
    printf("%3d (%s) (%d) ->", n->nodeID, n->touched ? "true " : "false",
	   n->threadID);
    
    for(int i = 0; i < BRANCHING; i++){
	printf(" %d", n->next[i]->nodeID);
    }
    printf("\n");
}

void print_graph(graph* g){
    for(int i = 0; i < g->size; i++){
	print_node(g->graph[i]);
    }
}

void print_tags(graph* g, int nthreads){
    int counts [nthreads];
    for(int i = 0; i < nthreads; i++){
	counts[i] = 0;
    }
    
    for(int i = 0; i < g->size; i++){
	int tagger = g->graph[i]->threadID;
	if(tagger >= 0)
	    counts[tagger] ++;
    }
    for(int i = 0; i < nthreads; i++){
	fprintf(stdout, "%d %d\n", i, counts[i]);
    }
}
