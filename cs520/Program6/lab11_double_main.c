#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "gc_lib.h"



int main(int argc, char** argv){
    register void* base asm("ebp");
    gc_init(100, base, false);
    
    void* x1 = gc_malloc(8);
    assert(x1 != NULL);
    void* x2 = gc_malloc(8);
    assert(x2 != NULL);
    assert((x2 == x1 + 8) || (x2 == x1 - 8));

    printf("%p\n", x1);
    printf("%p\n", x2);

    void* x3 = x1;
    if(x3 == NULL){
	fprintf(stderr, "uh-oh\n");
    }

    print_roots();
    
    gc_shutdown();

    return 0;
}
