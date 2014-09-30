#ifndef GC_LIB_H
#define GC_LIB_H

#include <stdbool.h>

/**
   Initialize the garbage collection system

   long heapsize: Maximum size of the heap

   void* main_base: Pointer to the base of the stack of the main
      function.

   bool autofree: Determines whether or not gc system should attempt
      to free things automatically.

   return: Whther or not it was possible to initialize the gc system
   with the requested amount of space.
 */
bool gc_init(long heapsize, void* main_base, bool autofree);

/**
   Shuts down the garbage collection system.  This should free all
   memory related to the garbage collection system.
 */
void gc_shutdown(void);

/**
   unsigned long size: How much space from the heap is being
   requested.

   return: A pointer to the base of the chunk of memory of size bytes.
   If it was not possible to allocate the memory, the value NULL
   should be returned.  
 */
void* gc_malloc(unsigned long size);

/**
   Print information about the heap.  This function will not be used
   for testing, and is present for your convenience.  I found it
   useful to allow functions outside the heap to be able to cause the
   heap to print itself out, for debugging purposes.
 */
void print_heap(void);

/**
   An explicit request to go and collect all of the garbage.
 */
bool collect_garbage(void);

/**
   Prints all of the base pointers of the roots of the garbage
   collection system.

   Begins by printing the words "Roots:" followed by a new line.

   Roots are printed out one per line, as follows:

   fprintf(stdout, "%p\n", pointer);

   where pointer is the base address of the region that has been
   identified as a root.
 */
void print_roots(void);

/**
   An explicit request to free a particular pointer controlled by the
   gc system.

   void* pointer: A pointer that should be released.
 */
void gc_free(void* pointer);

#endif
