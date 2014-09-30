#include <assert.h>
#include <stdio.h>

#include "gc_lib.h"

int main( int argc, char* argv[] )
{
	register void* base asm("ebp");
    gc_init(10, base, true);
    
    int* a = gc_malloc(2);
    int* b = gc_malloc(4);
    
    *a = 2;
    *b = 0;
    
    assert( *a == 2 );
    assert( *b == 0 );
    
    *b = 1;
    
    assert( *a != 2 ); /* a and b memory overlap */
    assert( *b == 1 );
    
    gc_free( a );
    
    short* c = gc_malloc(2);
    int* d = gc_malloc(4);
    
    *c = 9;
    *d = 8;
    
    assert( *b == 1 );
    assert( *c == 9 );
    assert( *d == 8 );
    
    assert( (void*)c+2 == b && b == (void*)d-4 );
    
    char* e = gc_malloc(1);
    assert( e == NULL );
    
    gc_free( b );
    gc_free( c );
    gc_free( d );
    
    void* f = gc_malloc(10);
    assert( f != NULL );
    
    gc_free( f );
    
    a = NULL;
    c = NULL;
    f = NULL;
    short* g = gc_malloc(2);
    short* h = gc_malloc(2);
    int* i = gc_malloc(4);
    h = gc_malloc(2);
    g = 0;
    g = gc_malloc(2);
    
	print_heap();
    collect_garbage();
    print_heap();
	
    print_roots();
    printf("\n");
    print_heap();
    
    assert( g != NULL );
    
    gc_shutdown();
    return 0;
}
