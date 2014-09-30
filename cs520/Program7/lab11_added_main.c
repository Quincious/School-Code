#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "gc_lib.h"



int main(int argc, char** argv){
    register void* base asm("ebp");
    gc_init(100, base, false);
    
    void* x1 = gc_malloc(50);
    assert(x1 != NULL);
    printf("%p\n", x1);
    
    x1 = x1 + 1;

    print_roots();
    
    gc_shutdown();

    return 0;
}
