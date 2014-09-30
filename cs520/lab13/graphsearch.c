#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"

#define NTHREADS 4

typedef struct s{
	node* cur;
	struct s* next;
}stackItem;

typedef struct{
	stackItem* head;
	pthread_mutex_t lock;
}stack;

typedef struct{
	int threadNumber;
	stack* st;
}threadArgs;


void dfs(node* n){
    if(n->touched)
	return;
    n->touched = true;
    n->threadID = 0;
    n->threadID = 0;
    for(int i = 0; i < BRANCHING; i++){
	node* nextNode = n->next[i];
	dfs(nextNode);
    }
}

void dfsStack(stack* st){
    
	while(st->head != NULL)
	{		
		node* current = st->head->cur;
		st->head = st->head->next;
		if(!current->touched)			
		{
			current->touched = true;
			current->threadID = 0;
			
			for(int i = 0; i < BRANCHING; i++){
				node* nextNode = current->next[i];
				
				stackItem *newItem = malloc(sizeof(stackItem));
				newItem->cur = nextNode;
				newItem->next = st->head;
				st->head = newItem;
			}
		}
		
	}
	
}

void* dfsMulti(void* p)
{
	threadArgs* arg = (threadArgs *)p;
	
	stack* st = arg->st;
	int num = arg->threadNumber;
	
	//printf("Inside Thread #%d\n", num);	
	pthread_mutex_lock(&st->lock);
	
	//printf("Thread #%d has stack lock\n", num);	
	while(st->head != NULL)
	{			
		node* current = st->head->cur;
		stackItem* next = st->head->next;
		free(st->head);
		st->head = next;
		
		pthread_mutex_unlock(&st->lock);		
		
		pthread_mutex_lock(&current->lock);
		
		if(!current->touched)			
		{
			current->touched = true;
			current->threadID = num;
			
			pthread_mutex_unlock(&current->lock);
			
			for(int i = 0; i < BRANCHING; i++){
				node* nextNode = current->next[i];
				
				stackItem *newItem = malloc(sizeof(stackItem));
				newItem->cur = nextNode;
				
				pthread_mutex_lock(&st->lock);
				
				newItem->next = st->head;
				st->head = newItem;				
				
				pthread_mutex_unlock(&st->lock);				
			}
		}
		else
			pthread_mutex_unlock(&current->lock);
			
		
		pthread_mutex_lock(&st->lock);	
	}	
	
	pthread_mutex_unlock(&st->lock);
	return NULL;
}

int main(int argc, char** argv){
	graph* g = build_graph(2000);	
	
	stack* st = malloc(sizeof(stack));
	st->head = malloc(sizeof(stackItem));
	st->head->next = NULL;
	st->head->cur = g->graph[0];	
	
	for(int i = 1; i < NTHREADS; i++)
	{
		stackItem* new = malloc(sizeof(stackItem));
		new->cur = g->graph[i];
		new->next = st->head;
		st->head = new;
	}
	
	pthread_mutex_init(&st->lock, NULL);
		
	pthread_t threads[NTHREADS];
	threadArgs* args[NTHREADS];
	
	for(int i= 0; i < NTHREADS; i++)
	{
		args[i] = malloc(sizeof(threadArgs));
		args[i]->st = st;
		args[i]->threadNumber = i;
		
		pthread_create(&threads[i], NULL, dfsMulti, args[i]);
	}
	
	for(int i= 0; i < NTHREADS; i++)
	{
		pthread_join(threads[i], NULL);
		free(args[i]);
	}	
		
	//dfsStack(st);
	print_tags(g, NTHREADS);	
	free(st);
	destroy_graph(g);
	return 0;

}
