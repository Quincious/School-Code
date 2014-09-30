#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdbool.h>

typedef struct n {
    int index;
    int payload;
    struct n* next;
    struct n* prev;
	bool checked;
} node;

typedef struct {
    node* head;
    node* tail;
} list;

typedef struct{
	list* fullList;
	int numToCheck;
}threadArg;

#define MAX_PAYLOAD 100000000
const int FIND_THREAD_AMT = 2;
bool endThread;
int frontIndex;

/**
   Builds a list of the specified size.
 */
list* build_list(int size){
    list* l = malloc(sizeof(list));
    assert(l != NULL);
    node* first = malloc(sizeof(node));
    assert(first != NULL);
    
    l->head = first;
    l->tail = first;
    first->next = NULL;
    first->prev = NULL;
    first->payload = rand() % MAX_PAYLOAD;
    first->index = 0;
	first->checked = false;
    int current_sum = 0;
    for(int i = 1; i < size; i++){
	node* new_node = malloc(sizeof(node));
	assert(new_node != NULL);
	new_node->next = l->head;
	l->head->prev = new_node;
	l->head = new_node;
	new_node->prev = NULL;

	int amt = rand() % 100;
	current_sum += amt;
	new_node->index = current_sum;
	new_node->payload = rand() % MAX_PAYLOAD;
	    new_node->checked = false;
    }
    return l;
}

void print_list_forwards(list* l){
    node* current = l->head;
    while(current != NULL){
	fprintf(stdout, "%d->%d ", current->index, current->payload);
	current = current->next;
    }
    fprintf(stdout, "\n");
}

void print_list_backwards(list* l){
    node* current = l->tail;
    while(current != NULL){
	fprintf(stdout, "%d->%d ", current->index, current->payload);
	current = current->prev;
    }
    fprintf(stdout, "\n");
}

node* scan_list(list* l, int x){
    node* current = l->head;
    while(current != NULL){
	if(current->payload > x)
	    return current;
	current = current->next;
    }
    return NULL;
}

void* scan_list_front(void* x){
	threadArg *arg = (void*)x;
	
	int num = arg->numToCheck;
	node* current = arg->fullList->head;
	
	while(current != NULL && !endThread){
		frontIndex = current->index;
		if(current->payload > num)
		{
			//printf("Front Found!\n");
			endThread = true;
			return (void*)current;
		}
		current = current->next;
	}
    
	endThread = true;
	return NULL;
}

void* scan_list_back(void* x){
	threadArg *arg = (void*)x;
	
	int num = arg->numToCheck;
	node* current = arg->fullList->tail;
	
	while(current != NULL && !endThread && current->index < frontIndex){
		if(current->payload > num)
		{
			//printf("Back Found!\n");
			endThread = true;
			return (void*)current;
		}
			current = current->prev;
	}
	endThread = true;
	return NULL;
}

int main(int argc, char** argv){
	
	if(argc < 3)
	{
		fprintf(stderr, "Too few Arguments!\n");
		return -1;
	}
	
	if(argc > 3)
	{
		fprintf(stderr, "Too many Arguments!\n");
		return -1;
	}
	
	pthread_t front, back;
	threadArg* arg = malloc(sizeof(threadArg));
	
	endThread = false;
	
	int length = atoi(argv[1]);
	arg->fullList = build_list(length);
	arg->numToCheck = atoi(argv[2]);
	
	frontIndex = arg->fullList->head->index;
		
	void *retVal1, *retVal2;
	//node* p = scan_list(l, value);
	
	pthread_create(&front, NULL, scan_list_front, arg);
	pthread_create(&back, NULL, scan_list_back, arg);
		
	pthread_join(front, &retVal1);
	pthread_join(back, &retVal2);
	
	//print_list_forwards(arg->fullList);
	
	if(retVal1 != NULL){
		fprintf(stdout, "index: %d\n", ((node*)retVal1)->index);
	}
	else if(retVal2 != NULL){
		fprintf(stdout, "index: %d\n", ((node*)retVal2)->index);
	}
	else {
		fprintf(stdout, "Not Found\n");
	}
	return 0;
}
