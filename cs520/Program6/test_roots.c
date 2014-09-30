/* test_roots.c
 * @author Seth Hager
 * test driver for gc_lib.c
 */

#include "gc_lib.h"
#include <stdlib.h>
#include <stdio.h>

int main( int argc, const char* argv[] ){

    fprintf( stdout, 
            "\ngc_init( 128, base, false )... print_heap( ) is called then ... print_roots( ) is called\n" );
    
    fprintf( stdout, 
            "One record should print, then Roots: with no output\n" );

    register void* base asm("ebp");
    gc_init( 128, base, false );

    print_heap( );
    print_roots( );

    fprintf( stdout, 
            "There is one ptr of size 100 that is gc_malloc\n" );
    
    fprintf( stdout, 
            "There are two local pointers that point inside of the size 100 block\n" );

    fprintf( stdout, 
            "There is one local pointer that points inside the our heap above the size 100 block\n\n\n" );

    void* ptr = gc_malloc( 100 );
    void* ptr2 = ptr + 10;
    ptr2++;
    void* ptr3 = ptr2 - 4;
    ptr3++;
    void* ptr4 = ptr + 101;
    ptr4++;

    print_heap( );
    print_roots( );
    
    fprintf( stdout, 
            "1 root should be printed all with the same address\n" );

}
