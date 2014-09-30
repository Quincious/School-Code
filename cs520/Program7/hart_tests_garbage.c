#include "gc_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char** argv)
{
	//freeing and coalescing tests
    register void* base asm("ebp");
    bool initTest = gc_init(100, base, true);
    
	if(initTest == false)
	{
		printf("gc_init unsuccessful\n");
		return -1;
	}
	    
    void* test1 = gc_malloc(90);    
    void* test2 = gc_malloc(20);
	if(test2 != NULL)
	{
		printf("test2 malloc fail unsuccessful\n");
		return -1;
	}
    
    void* test3 = gc_malloc(10);
   
    gc_free(test1);	
	
	void* test4 = gc_malloc(20);
    void* test5 = gc_malloc(20);
	
	//uncomment this to test garbage collector and pointer in heap
	//*((void**)test4) = *((void**)test5);
	
   	test5 = gc_malloc(20);
	void* test6 = gc_malloc(30);	
	
	
	void* test7 = gc_malloc(20);	
	assert(test7 != NULL);
			
	// print_heap();
	// printf("**************\n");
	// collect_garbage();
	// print_heap();
	
	/* 
	Example Output:
	(with line 33 commented)
	Size: -1 In Use: true Address: 0x23a2010
	Size: 20 In Use: true Address: 0x23a2010
	Size: 20 In Use: true Address: 0x23a2024
	Size: 20 In Use: true Address: 0x23a2038
	Size: 30 In Use: false Address: 0x23a204c
	Size: 10 In Use: true Address: 0x23a206a
	**************
	Size: -1 In Use: true Address: 0x23a2010
	Size: 20 In Use: true Address: 0x23a2010
	Size: 20 In Use: false Address: 0x23a2024 //This becomes false after collection
	Size: 20 In Use: true Address: 0x23a2038
	Size: 30 In Use: false Address: 0x23a204c
	Size: 10 In Use: true Address: 0x23a206a
	End of Program.

	Example Output:
	(with line 33 NOT commented)
	Size: -1 In Use: true Address: 0x1309010
	Size: 20 In Use: true Address: 0x1309010
	Size: 20 In Use: true Address: 0x1309024
	Size: 20 In Use: true Address: 0x1309038
	Size: 30 In Use: false Address: 0x130904c
	Size: 10 In Use: true Address: 0x130906a
	**************
	Size: -1 In Use: true Address: 0x1309010
	Size: 20 In Use: true Address: 0x1309010
	Size: 20 In Use: true Address: 0x1309024
	Size: 20 In Use: true Address: 0x1309038
	Size: 30 In Use: false Address: 0x130904c
	Size: 10 In Use: true Address: 0x130906a
	End of Program.
	*/
	
	
	gc_free(test5);			 
	gc_free(test3);
    gc_free(test4);

	
	gc_shutdown();
	
    printf("End of Program.\n");
    return 0;
}