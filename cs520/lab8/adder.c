//Jonathan Hart
//Lab 8
//10/23/2013

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pthread.h>
#include <tgmath.h>
 
typedef struct results{
	double sum;
	char* buffer;
	int startIndex;
	int endIndex;
	
}results;
 
void* adder(void *ptr)
{
	struct results *ret = (struct results*)ptr;
	//printf("Inside thread function");
	
	for(int i = ret->startIndex; i < ret->endIndex; i++)
	{
		if(ret->buffer == '\0')
			break;
			
		ret->sum += sin(ret->buffer[i]);
	}
	
	return NULL;
}

int main(int argc, char** argv)
{
	if(argc > 3)
	{
		fprintf(stderr, "Too many arguments!\n");
		return -1;
	}
	else if(argc < 3)
	{
		fprintf(stderr, "Not enough arguments!\n");
		return -1;
	}
	
	char* end1;	
	errno = 0;
	unsigned long numOfThreads = strtol(argv[2], &end1, 16);
	
	if(errno != 0 || numOfThreads > 0xFFFFFFFFl )
	{
		fprintf(stderr, "%s is not a valid number (Overflow)\n", argv[2]);
		return -1;
	}
	
	if((*end1) != 0)
	{
		fprintf(stderr, "%s is not a valid number\n", argv[2]);
		return -1;
	}
	
	FILE *inputFile = fopen(argv[1], "r");
	
	if(inputFile == NULL) //ensure input file exists
	{
		fprintf(stderr, "Error accessing input file\n");
		return -1;
	}
	
	struct stat fileStat;
	
	stat(argv[1], &fileStat);
	
	char* buffer = (char*)malloc(fileStat.st_size + 1);
	
	if (buffer == NULL) 
	{
		fprintf (stderr, "Memory error");
		return -1;
	}
	
	fread(buffer, 1, (int)fileStat.st_size, inputFile);
	
	fclose(inputFile);	
	
	buffer[(int)fileStat.st_size] = '\0';
	
	//printf("size: %d\n%s\n", (int)fileStat.st_size, buffer);
	
	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * numOfThreads);
	results *retStructs = (results*)malloc(sizeof(results) * numOfThreads);
	int jumpSize = ((int)fileStat.st_size / numOfThreads) + 1;
	
	for(int i = 0; i < numOfThreads; i++)
	{
		retStructs[i].buffer = buffer;
		retStructs[i].sum = 0;
		retStructs[i].startIndex = i * jumpSize;
		retStructs[i].endIndex = (i * jumpSize) + jumpSize;
		pthread_create(&threads[i], NULL, adder, (void*)&retStructs[i]);
	}
	
	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join(threads[i], NULL);
	}	
	
	double totalSum = 0;
	
	for(int i = 0; i < numOfThreads; i++)
	{
		totalSum += retStructs[i].sum;
	}	
	
	printf("Sum= %f\n", totalSum);
	
	free(buffer);
	free(threads);
	free(retStructs);
	return 0;	
}
