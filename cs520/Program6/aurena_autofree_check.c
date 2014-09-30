/* Author: Anthony Urena
 * Date:   11/16/13
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "gc_lib.h"

int main(int argc, char** argv){
    register void* base asm("ebp");
    gc_init(64, base, true);

    void* array = gc_malloc(4*sizeof(int*));
    assert(array != NULL);

    int** b = (int**)array;
    // creating garbage
    for(int i = 0; i < 4; i++) {
      b[i] = gc_malloc(sizeof(int));
      assert(b[i] != NULL);
    }
    // this isn't garbage
    for(int i = 0; i < 4; i++) {
      b[i] = gc_malloc(sizeof(int));
      assert(b[i] != NULL);
    }

    //uncomment this if you have issues
    //print_heap();
    fprintf(stdout, "%p - the only root\n", array);
    print_roots();
    collect_garbage();

    //uncomment this if you have issues
    //print_heap();
    fprintf(stdout, "\n%p - should still be the only root\n", array);
    print_roots();

    array = gc_malloc(4*sizeof(int**));
    // this should be NULL because memory is maxed here
    assert(array == NULL);
    array = NULL;
    b = NULL;
    array = gc_malloc(8*sizeof(int**));
    assert(array != NULL);

    fprintf(stdout, "\nYou should see one node with 64 bytes in use.\n");
    print_heap();
    fprintf(stdout, "%p - the only root\n", array);
    print_roots();

    gc_shutdown();
    return 0;
}
