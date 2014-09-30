#include "gc_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct n {
    int payload;
    struct n* next;
} node;

int main(int argc, char** argv){
    register void* base asm("ebp");
    gc_init(50, base, true);
    
    node* head = NULL;
    for(int i = 0; i < 3; i++){
	printf("%d\n", i);
	node* next = gc_malloc(sizeof(node));
	assert(next != NULL);
	next->payload = i;
	next->next = head;
	head = next;
	next = NULL;
    }
    head = NULL;

    for(int i = 0; i < 3; i++){
	printf("%d\n", i);
	node* next = gc_malloc(sizeof(node));
	assert(next != NULL);
	next->payload = i;
	next->next = head;
	head = next;
	next = NULL;
    }

    

    gc_shutdown();
}
