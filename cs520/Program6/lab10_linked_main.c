#include "gc_lib.h"
#include <stdlib.h>

typedef struct n {
    int payload;
    struct n* next;
} node;

int main(int argc, char** argv){
    register void* base asm("ebp");
    gc_init(100, base, false);
    
    node* head = NULL;
    for(int i = 0; i < 3; i++){
	node* next = gc_malloc(sizeof(node));
	next->payload = i;
	next->next = head;
	head = next;
	next = NULL;
    }
//    collect_garbage();
//    print_heap();
    head = NULL;
    for(int i = 0; i < 3; i++){
	node* next = gc_malloc(sizeof(node));
	next->payload = i;
	next->next = head;
	head = next;
	next = NULL;
    }

    

    gc_shutdown();
}
