#include "gc_lib.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	//freeing and coalescing tests
    register void* base asm("ebp");
    bool initTest = gc_init(100, base, false);
    
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
   	test5 = gc_malloc(20);   
	
	printf("test5: %p\n", test5);
	
	print_heap();
	print_roots();
	
	/* Example Output:
	
	bash-4.2$ ./simple
	test5: 0x168f038
	Size: -1 In Use: true Address: 0x168f010
	Size: 20 In Use: true Address: 0x168f010
	Size: 20 In Use: true Address: 0x168f024
	Size: 20 In Use: true Address: 0x168f038
	Size: 30 In Use: false Address: 0x168f04c
	Size: 10 In Use: true Address: 0x168f06a
	Size: 0 In Use: false Address: 0x168f074
	Inside print_roots
	Roots:
	0x168f010
	0x168f038
	0x168f06a
	End of Program.

	Address: 0x168f024 is in use but not a root!
	*/
	
	
	gc_free(test5);			 
	gc_free(test3);
    gc_free(test4);

	
	gc_shutdown();
	
    printf("End of Program.\n");
    return 0;
}