#include "gc_lib.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct n {
    int payload;
    struct n* next;
} node;

int main(int argc, char** argv){
    register void* base asm("ebp");
    gc_init(40, base, true);
    
    node* head = gc_malloc(sizeof(node));
    node* next = gc_malloc(sizeof(node));
    head->next = next;
    next->next = head;

    next = NULL;
	
    node* next2 = gc_malloc(sizeof(node));
    assert(next2 == NULL);
    
    bool found_space = collect_garbage();
    assert(!found_space);

    gc_shutdown();
}
