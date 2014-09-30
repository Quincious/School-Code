#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "gc_lib.h"



int main(int argc, char** argv){
    register void* base asm("ebp");
    gc_init(100, base, false);
    
    void* x1 = gc_malloc(49);
    assert(x1 != NULL);
    void* x2 = gc_malloc(49);
    assert(x2 != NULL);
    assert((x2 == x1 + 49) || (x2 == x1 - 49));

    gc_free(x1);
    gc_free(x2);
    
    x1 = gc_malloc(90);
    assert(x1 != NULL);
    gc_shutdown();

    return 0;
}
