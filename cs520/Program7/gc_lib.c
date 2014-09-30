/*
Jonathan Hart
Program 6
11/17/2013
*/

#include "gc_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#define FIND_ROOTS_THREADS 2
#define HEAP_SEARCH_THREADS 2

typedef struct node_t{
	long size;
	bool inUse;
	bool isRoot;
	bool isGarbage;
	bool checked;
	void* heapPtr;
	struct node_t* next;
	struct node_t* prev;
	pthread_mutex_t lock;
}node;

typedef struct{
	void* startPtr;
	void* endPtr;	
}findRootsArgs;

typedef struct s{
	void* cur;
	struct s* next;
}stackItem;

typedef struct{
	stackItem* head;
	pthread_mutex_t lock;
}stack;

static node* headPtr;
static node* tailPtr;
static void* mainBase;
static void* heapBase;
static bool autoFree;
static long heapSize;
static bool endThread;
static void* frontIndex;
static stack* ptrStack ;

static void coalesceCheck()
{	
	//printf("Inside Coalesce!\n");
	node* cur = headPtr->next;
	
	while(cur->next != tailPtr)
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
	
	while(cur != tailPtr)
	{
		if((ptr >= cur->heapPtr && ptr < (cur->heapPtr + cur->size)) && cur->inUse)
		{
			//printf("Found Root!\n");
			cur->isRoot = true;
			cur->isGarbage = false;
			return;
		}
		
		cur = cur->next;
	}
}

static void* find_roots(void* p)
{
	findRootsArgs *arg = (findRootsArgs*)p;
	
	void* curPtr = arg->startPtr;
	
	while(arg->endPtr < curPtr)
	{
		void* ptr = *((void**)curPtr);		
		markPointer(ptr);
		curPtr -= 4;
	}

	return NULL;
}

static void* multiCheckPointerInHeap(void * p)
{
	int tries = 0;
	pthread_mutex_lock(&ptrStack->lock);
	
	while(ptrStack->head != NULL || tries < 50)
	{		
		if(ptrStack->head == NULL)
		{
			pthread_mutex_unlock(&ptrStack->lock);
			tries++;
			continue;
		}
		
		void* ptr = ptrStack->head->cur;
		stackItem* next = ptrStack->head->next;
		free(ptrStack->head);
		ptrStack->head = next;		
		
		pthread_mutex_unlock(&ptrStack->lock);
		
		if(ptr < heapBase || ptr >= (heapBase + heapSize))
			continue;
		
		node* cur = headPtr->next;
			
		while(cur != tailPtr)
		{
			if((ptr >= cur->heapPtr && ptr < (cur->heapPtr + cur->size)) && cur->inUse)
			{
				//printf("Found in heap pointer! Address: %p\n", cur->heapPtr);
				//Already checked. Prevent possible Infinite loop
				if(cur->checked || cur->isRoot)
					break;			
					
				cur->checked = true;
				cur->isGarbage = false;
				
				ptr = cur->heapPtr;
				
				while(ptr < (cur->heapPtr + cur->size))
				{
					pthread_mutex_lock(&ptrStack->lock);
					
					stackItem* new = malloc(sizeof(stackItem));
					new->cur = ptr;
					new->next = ptrStack->head;
					ptrStack->head = new;
					
					pthread_mutex_unlock(&ptrStack->lock);
					
					ptr += 4;
				}
				
				break;
			}
			
			cur = cur->next;
		}
		
		pthread_mutex_lock(&ptrStack->lock);				
	}
	
	return NULL;
}

static void checkPointerInHeap(void * ptr)
{
	if(ptr < heapBase || ptr >= (heapBase + heapSize))
		return;
	
	node* cur = headPtr->next;
		
	while(cur != tailPtr)
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

static void* gc_malloc_front_search(void* p)
{	
	unsigned long *size = (unsigned long*)p;
		
	node* current = headPtr->next;
	
	while(current != tailPtr && !endThread){
		frontIndex = current->heapPtr;
		if(current->size > *size)
		{
			printf("Front Found!\n");
			endThread = true;
			return (void*)current;
		}
		current = current->next;
	}
    
	endThread = true;
	return NULL;

}

static void* gc_malloc_back_search(void* p)
{
	unsigned long *size = (unsigned long*)p;
	
	node* current = tailPtr->prev;
	
	while(current != headPtr && !endThread && current->heapPtr > frontIndex){
		if(current->size > *size)
		{
			printf("Back Found!\n");
			endThread = true;
			return (void*)current;
		}
			current = current->prev;
	}
	endThread = true;
	return NULL;
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
	
	void *frontRet, *backRet;
	pthread_t front, back;
	
	endThread = false;
	
	pthread_create(&front, NULL, gc_malloc_front_search, (void*)&size);
	pthread_create(&back, NULL, gc_malloc_back_search, (void*)&size);
		
	pthread_join(front, &frontRet);
	pthread_join(back, &backRet); 
	
	if(frontRet == NULL && backRet == NULL)//no room available
		return NULL;
	else if(frontRet != NULL)//found room 
	{
		newNode->next = (node*)frontRet;
		newNode->prev = ((node*)frontRet)->prev;
		newNode->heapPtr = ((node*)frontRet)->heapPtr;
		((node*)frontRet)->size -= size;
		((node*)frontRet)->heapPtr += size;
		((node*)frontRet)->prev->next = newNode;
		((node*)frontRet)->prev = newNode;			
	}
	else
	{
		newNode->next = (node*)backRet;
		newNode->prev = ((node*)backRet)->prev;
		newNode->heapPtr = ((node*)backRet)->heapPtr;
		((node*)backRet)->size -= size;
		((node*)backRet)->heapPtr += size;
		((node*)backRet)->prev->next = newNode;
		((node*)backRet)->prev = newNode;	
	}
	
	
	/* while(cur != tailPtr)
	{
		if(cur->size < size || cur->inUse)
			cur = cur->next;
		else
			break;
	}
	
	if(cur == tailPtr)
		return NULL;
	else
		newNode->next = cur;
		newNode->prev = cur->prev;
		newNode->heapPtr = cur->heapPtr;
		cur->size -= size;
		cur->heapPtr += size;
		cur->prev->next = newNode;
		cur->prev = newNode; */
	
	
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
	tailPtr = malloc(sizeof(node));
	
	if(headPtr == NULL || tailPtr == NULL)
		return false;
	
	headPtr->size = -1;
	headPtr->inUse = true;
	headPtr->heapPtr = heapBase;
	headPtr->next = tailPtr;
	headPtr->prev = NULL;
	
	tailPtr->size = -1;
	tailPtr->inUse = true;
	tailPtr->heapPtr = heapBase + heapSize;
	tailPtr->next = NULL;
	tailPtr->prev = headPtr;
	
	node* newNode = malloc(sizeof(node));	
	
	if(newNode == NULL)
		return false;
	
	newNode->size = heapsize;
	newNode->inUse = false;
	newNode->heapPtr = heapBase;
	newNode->next = tailPtr;
	newNode->prev = headPtr;
	
	headPtr->next = newNode;
	tailPtr->prev = newNode;
	
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
	while(cur != tailPtr)
	{
		cur->isRoot = false;
		cur->isGarbage = true;
		cur->checked = false;
		
		cur = cur->next;
	}
	
	//flag roots
	pthread_t rootsThreads[FIND_ROOTS_THREADS];
	findRootsArgs* rootArgs[FIND_ROOTS_THREADS];
			
	for(int i = 0; i < FIND_ROOTS_THREADS; i++)
	{
		rootArgs[i] = malloc(sizeof(findRootsArgs));
		rootArgs[i]->startPtr = curStackPtr - (((curStackPtr - base) / FIND_ROOTS_THREADS) * i);
		rootArgs[i]->endPtr = curStackPtr - (((curStackPtr - base) / FIND_ROOTS_THREADS) * (i+1));
		
		while((unsigned long)rootArgs[i]->startPtr % 4 != 0)
			rootArgs[i]->startPtr -= 1;		
	}
	
	for(int i = 0; i < FIND_ROOTS_THREADS; i++)
		pthread_create(&rootsThreads[i], NULL, find_roots, rootArgs[i]);

	for(int i = 0; i < FIND_ROOTS_THREADS; i++)
		pthread_join(rootsThreads[i], NULL);
	
	/* while(base < curStackPtr)
	{
		void * ptr = *((void**)curStackPtr);
		
		markPointer(ptr);
		
		curStackPtr -= 4;	
	} */

	cur = headPtr->next;
	
	ptrStack = malloc(sizeof(stack));
	pthread_mutex_init(&ptrStack->lock, NULL);
	ptrStack->head = NULL;
	
	//check for inHeap pointers
	while(cur != tailPtr)
	{				
		if(cur->isRoot)
		{
			void * ptr = cur->heapPtr;
			
			while(ptr < (cur->heapPtr + cur->size))
			{
				stackItem* new = malloc(sizeof(stackItem));
				new->cur = ptr;
				new->next = ptrStack->head;
				ptrStack->head = new;				
				
				//checkPointerInHeap(*((void**)ptr));				
				ptr += 4;
			}
		}
			
		cur = cur->next;
	}
	
	pthread_t threads[HEAP_SEARCH_THREADS];
	
	for(int i= 0; i < HEAP_SEARCH_THREADS; i++)
	{		
		pthread_create(&threads[i], NULL, multiCheckPointerInHeap, NULL);
	}
	
	for(int i= 0; i < HEAP_SEARCH_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}	
	
	free(ptrStack);
	
	cur = headPtr->next;
	
	//remove garbage
	while(cur != tailPtr)
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
	
	while(cur != tailPtr)
	{
		cur->isRoot = false;
		
		cur = cur->next;
	}		
	
	void* base = dummyFunction();
	void* curStackPtr = mainBase;
	
	pthread_t rootsThreads[FIND_ROOTS_THREADS];
	findRootsArgs* rootArgs[FIND_ROOTS_THREADS];
			
	for(int i = 0; i < FIND_ROOTS_THREADS; i++)
	{
		rootArgs[i] = malloc(sizeof(findRootsArgs));
		rootArgs[i]->startPtr = curStackPtr - (((curStackPtr - base) / FIND_ROOTS_THREADS) * i);
		rootArgs[i]->endPtr = curStackPtr - (((curStackPtr - base) / FIND_ROOTS_THREADS) * (i+1));
		
		while((unsigned long)rootArgs[i]->startPtr % 4 != 0)
			rootArgs[i]->startPtr -= 1;		
	}
	
	for(int i = 0; i < FIND_ROOTS_THREADS; i++)
		pthread_create(&rootsThreads[i], NULL, find_roots, rootArgs[i]);

	for(int i = 0; i < FIND_ROOTS_THREADS; i++)
		pthread_join(rootsThreads[i], NULL);
	
	
	/* while(base < curStackPtr)
	{
		void * ptr = *((void**)curStackPtr);
		
		markPointer(ptr);
		
		curStackPtr -= 4;	
	} */
	
	cur = headPtr->next;
	
	printf("Roots:\n");
	
	while(cur != tailPtr)
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
	
	while(cur != tailPtr)
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

