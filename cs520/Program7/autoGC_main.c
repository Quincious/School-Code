/*
automatic garbage collection, only deals with roots from 
the stack into the gc_heap, not roots from the gc_heap 
into the gc_heap.

Author: David Arnoldy
*/

#include "gc_lib.h"
#include <stdio.h>

int main(int argc, char ** argv){
	register void * base asm("ebp");
	
	gc_init(400, base, true);
	
	void * x1 = gc_malloc(50);
	*((int *)x1) = 1;
	
	void * x2 = gc_malloc(50);
	*((int *)x2) = 22;
	
	void * x3 = gc_malloc(50);
	*((int *)x3) = 333;
	
	void * x4 = gc_malloc(50);
	*((int *)x4) = 4444;
	
	void * x5 = gc_malloc(50);
	*((int *)x5) = 55555;
	
	void * x6 = gc_malloc(50);
	*((int *)x6) = 666666;
	
	void * x7 = gc_malloc(50);
	*((int *)x7) = 7777777;
	
	void * x8 = gc_malloc(50);
	*((int *)x8) = 88888888;
	
	print_roots();
	
	bool result = true;
	printf("attempting to gc_malloc(75) with no space\n");
	void * x9 = gc_malloc(75);
	if(x9 == NULL){
		printf("correct: not enough space\n");
	}
	else{
		printf("wrong: found imaginary space "
		"or deleted non-garbage to make space\n");
		result = false;
	}
	
	x5 = NULL;
	
	print_roots();
	
	printf("attempting to gc_malloc(75) with "
	"insufficient space\n");
	x9 = gc_malloc(75);
	if(x9 == NULL){
		printf("correct: still not enough space\n");
	}
	else{
		printf("wrong: found imaginary space "
		"or deleted non-garbage to make space\n");
		result = false;
	}
	
	x6 = NULL;
	
	print_roots();
	
	printf("try gc_malloc(75), success needs a GC with a coalesce\n");
	x9 = gc_malloc(75);
	if(x9 == NULL){
		printf("wrong: collect_garbage should have made "
		"the space\n");
		result = false;
	}
	else{
		printf("correct: collect_garbage made space\n");
	}
	
	/*this checks the "coalesce" function again*/
	print_roots();
	x7 = NULL;
	collect_garbage();
	print_roots();
	
	printf("overall result: ");
	if(result){printf("completely correct\n");}
	else{printf("wrong\n");}
	
	gc_shutdown();
	
	return 0;
}