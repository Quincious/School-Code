#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "gc_lib.h"



int main(int argc, char** argv){
    register void* base asm("ebp");
    gc_init(100, base, false);
    
    void* x1 = gc_malloc(49);
    void* x2 = gc_malloc(49);
    assert(x2 != NULL);
    x1 = gc_malloc(49);
    assert(x1 == NULL);
    gc_shutdown();

    return 0;
}
