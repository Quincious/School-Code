/*
Jonathan Hart
Program 6
11/17/2013
*/

#include "gc_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct node_t{
	long size;
	bool inUse;
	bool isRoot;
	bool isGarbage;
	bool checked;
	void* heapPtr;
	struct node_t* next;
	struct node_t* prev;	
}node;

static node* headPtr;
static void* mainBase;
static void* heapBase;
static bool autoFree;
static long heapSize;

static void coalesceCheck()
{	
	//printf("Inside Coalesce!\n");
	node* cur = headPtr->next;
	
	while(cur->next != NULL)
	{
		if(!cur->inUse && cur->size == 0)
		{
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			
			node* temp = cur->next;
			free(cur);
			cur = temp;
		}
		else if(!cur->inUse && !cur->next->inUse)
		{
			cur->next->size += cur->size;
			cur->next->heapPtr = cur->heapPtr;
			cur->next->prev = cur->prev;
			cur->prev->next = cur->next;
			
			node* temp = cur->next;
			free(cur);
			cur = temp;
		}
		else
			cur = cur->next;
	}
	
	if(!cur->inUse && cur->size == 0)
	{
		cur->prev->next = cur->next;
					
		node* temp = cur->next;
		free(cur);
		cur = temp;
	}
	
} 

static void markPointer(void * ptr)
{
	if(ptr < heapBase || ptr >= (heapBase + heapSize))
		return;
	
	node* cur = headPtr->next;
	
	while(cur != NULL)
	{
		if((ptr >= cur->heapPtr && ptr < (cur->heapPtr + cur->size)) && cur->inUse)
		{
			//printf("Found in root!\n");
			cur->isRoot = true;
			cur->isGarbage = false;
			return;
		}
		
		cur = cur->next;
	}
}

static void checkPointerInHeap(void * ptr)
{
	if(ptr < heapBase || ptr >= (heapBase + heapSize))
		return;
	
	node* cur = headPtr->next;
		
	while(cur != NULL)
	{
		if((ptr >= cur->heapPtr && ptr < (cur->heapPtr + cur->size)) && cur->inUse)
		{
			//printf("Found in heap pointer! Address: %p\n", cur->heapPtr);
			//Already checked. Prevent possible Infinite loop
			if(cur->checked || cur->isRoot)
				return;			
				
			cur->checked = true;
			cur->isGarbage = false;
			
			ptr = cur->heapPtr;
			
			while(ptr < (cur->heapPtr + cur->size))
			{
				checkPointerInHeap(*((void**)ptr));
				
				ptr += 4;
			}
			
			return;
		}
		
		cur = cur->next;
	}

}


static void* dummyFunction()
{	
	register void* base asm("esp");
	
	return base;
}

static void* gc_malloc_helper(unsigned long size)
{
	if(size <= 0)
		return NULL;
	
	node* cur = headPtr->next;
	
	node* newNode = malloc(sizeof(node));
	newNode->size = size;
	newNode->inUse = true;
	
	//find the first available spot to malloc
	while(cur != NULL)
	{
		if(cur->size < size || cur->inUse)
			cur = cur->next;
		else
			break;
	}
	
	if(cur == NULL)//no room available
		return NULL;
	else //found room 
	{
		newNode->next = cur;
		newNode->prev = cur->prev;
		newNode->heapPtr = cur->heapPtr;
		cur->size -= size;
		cur->heapPtr += size;
		cur->prev->next = newNode;
		cur->prev = newNode;			
	}
	
	void* retPtr = newNode->heapPtr;
	assert(retPtr >= heapBase);
	assert(retPtr < heapBase + heapSize);
	
	coalesceCheck();
	
	return retPtr;	
}

bool gc_init(long heapsize, void* main_base, bool autofree)
{
	//printf("Inside Init!\n");
	heapBase = malloc(heapsize);
	
	if(heapBase == NULL)
		return false;
	
	autoFree = autofree;
	mainBase = main_base;
	heapSize = heapsize;
	
	headPtr = malloc(sizeof(node));
	
	if(headPtr == NULL)
		return false;
	
	headPtr->size = -1;
	headPtr->inUse = true;
	headPtr->heapPtr = heapBase;
	headPtr->next = NULL;
	headPtr->prev = NULL;
	
	node* newNode = malloc(sizeof(node));	
	
	if(newNode == NULL)
		return false;
	
	newNode->size = heapsize;
	newNode->inUse = false;
	newNode->heapPtr = heapBase;
	newNode->next = NULL;
	newNode->prev = headPtr;
	
	headPtr->next = newNode;
	
	return true;
}

void gc_shutdown(void)
{
	//printf("Inside gc_shutdown\n");
	
	node* cur = headPtr;
	node* next = headPtr->next;
	
	//free all nodes
	while(next != NULL)
	{
		free(cur);
		cur = next;
		next = cur->next;
	}
	
	free(cur);
	free(heapBase);	
}

void* gc_malloc(unsigned long size)
{
	//printf("Inside Malloc! Size = %u\n", size);
	void* retPtr = gc_malloc_helper(size);
	
	if(retPtr == NULL && autoFree)
	{	
		bool collect = collect_garbage();
		
		if(collect)
			retPtr = gc_malloc_helper(size);		
	}
		
	return retPtr;
}

void print_heap(void)
{
	//printf("Inside Print!\n");
	node* cur = headPtr;
	
	while(cur != NULL)
	{
		printf("Size: %ld ",cur->size);
		printf("In Use: %s ",cur->inUse ? "true" : "false");
		printf("Address: %p\n", cur->heapPtr);
		
		cur = cur->next;
	}
}

bool collect_garbage(void)
{
	//printf("Inside collect!\n");
	void* base = dummyFunction();
	void* curStackPtr = mainBase;
	bool retVal = false;
	
	node* cur = headPtr->next;	
	
	//Reset flags
	while(cur != NULL)
	{
		cur->isRoot = false;
		cur->isGarbage = true;
		cur->checked = false;
		
		cur = cur->next;
	}
	
	//flag roots
	while(base < curStackPtr)
	{
		void * ptr = *((void**)curStackPtr);
		
		markPointer(ptr);
		
		curStackPtr -= 4;	
	}

	cur = headPtr->next;
	
	//check for inHeap pointers
	while(cur != NULL)
	{		
		
		if(cur->isRoot)
		{
			void * ptr = cur->heapPtr;
			
			while(ptr < (cur->heapPtr + cur->size))
			{
				checkPointerInHeap(*((void**)ptr));
				
				ptr += 4;
			}
		}
			
		cur = cur->next;
	}
	
	cur = headPtr->next;
	
	//remove garbage
	while(cur != NULL)
	{
		//garbage found
		if(cur->isGarbage && cur->inUse)
		{		
			retVal = true;
			node * next = cur->next;
			gc_free(cur->heapPtr);				
			cur = next;
		}
		else
			cur = cur->next;
	}	

	return retVal;
}

void print_roots(void)
{	
	//printf("Inside print_roots\n");
	
	node* cur = headPtr->next;
	
	while(cur != NULL)
	{
		cur->isRoot = false;
		
		cur = cur->next;
	}		
	
	void* base = dummyFunction();
	void* curStackPtr = mainBase;
	
	while(base < curStackPtr)
	{
		void * ptr = *((void**)curStackPtr);
		
		markPointer(ptr);
		
		curStackPtr -= 4;	
	}
	
	cur = headPtr->next;
	
	printf("Roots:\n");
	
	while(cur != NULL)
	{		
		if(cur->isRoot == true)
		{
			fprintf(stdout, "%p\n", cur->heapPtr);
		}
		
		cur = cur->next;
	}
}

void gc_free(void* pointer)
{
	//printf("Inside Free!\n");
	node* cur = headPtr->next;
	bool found = false;
	
	while(cur != NULL)
	{
		if(cur->heapPtr == pointer)
		{
			found = true;
			break;
		}
		cur = cur->next;
	}
	
	if(!found || pointer == NULL)
		return;
		
	cur->inUse = false;
	
	coalesceCheck();		
}

