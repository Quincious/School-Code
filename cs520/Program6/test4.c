#include "gc_lib.h"
#include <stdio.h>

int main(int argc, char** argv){
    register void* base asm("ebp");
    printf("base-%p\n", base);
    gc_init(300, base, false);
    void* x = gc_malloc(4);
    gc_free(x);
    void* x2 = gc_malloc(16);
    void* x3 = gc_malloc(16);
    void* x4 = gc_malloc(24);
    void* x5 = gc_malloc(16);
    void* x6 = gc_malloc(16);
    void* x7 = gc_malloc(16);
    *((int*) x6) = 12345;
    *((void **)x4) = x3;
    *((void **)x5) = x6;
    *((void **)x3) = x4;
    *((int*) x7) = 9999;

	print_heap();
    collect_garbage();
    print_roots();

    printf("valid roots should be-(%p, %p, %p)\n", x5, x6, x7);


    gc_shutdown();
    return 0;
}
