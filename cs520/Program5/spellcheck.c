/*
Jonathan Hart
Program 5
11/3/13

*/


#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pthread.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "hashtable_constants.h"

#define MUTEX_AMOUNT 150
#define HASH_SIZE 12289
#define MAX_WORD_SIZE 50

struct hashTable {
	pthread_mutex_t *lock;
	int collisions;
	char** words;
};

struct bufferForThreads{
	char* buffer;
	int startIndex;
	int endIndex;	
};

struct hashTable hashTables[HASH_SIZE];
pthread_mutex_t *mutexPool[MUTEX_AMOUNT];

unsigned long power(unsigned long x, unsigned long y)
{
	unsigned long retVal = x;

	for(unsigned long i = 0; i < y; i++)
		retVal *= retVal;

	return retVal;
}

unsigned long hashKey(char * str)
{
	unsigned long key = 0;
	for(unsigned long j = 0; j <= 51; j++)
	{
		if(str[j] == '\0')
			break;
		
		key += power((unsigned long)str[j], (j + 1));
	}
	key = key % HASH_SIZE;
	return key;
}

void* testWords(void *ptr)
{
	//printf("Thread Start\n");
	struct bufferForThreads *ret = (struct bufferForThreads*)ptr;

	char* word = malloc(MAX_WORD_SIZE + 1);
	int count = 0;

	for(int i = ret->startIndex; i < ret->endIndex; i++)
	{
		char c = ret->buffer[i];

		if(c == '\0')//no more words
			break;

		if(isspace(c))
		{
			word[count] = '\0';
			//printf("Test word: %s\n", word);
			unsigned int key = hashKey(word);
			int collisionIndex = hashTables[key].collisions;
			int foundWord = 0;

			for(int j = 0; j < collisionIndex; j++)
			{	
				//printf("Key: %d -- Word: %s\n", key, hashTables[key].words[j]);

				if(strcmp(hashTables[key].words[j], word) == 0)
				{
					foundWord = 1;
					break;
				}
			}

			if(foundWord == 0)
				printf("Not a word: %s\n", word);
			//else
			//	printf("Key: %d -- Is a word: %s\n",key, word);

			count = 0;
		}
		else
		{
			word[count] = c;
			count++;
			if(count > MAX_WORD_SIZE)
			{
				fprintf (stderr, "Invalid Word Found!\n");
				exit(0);
			}
		}
	}

	//printf("Thread End\n");
	free(word);
	return NULL;
}

void* fillHashTable(void *ptr)
{
	//printf("Thread Start\n");
	struct bufferForThreads *ret = (struct bufferForThreads*)ptr;

	char* word = malloc(MAX_WORD_SIZE + 1);
	int count = 0;

	for(int i = ret->startIndex; i < ret->endIndex; i++)
	{
		char c = ret->buffer[i];

		if(c == '\0')//no more words
			break;

		if(isspace(c))
		{
			word[count] = '\0';
			unsigned int key = hashKey(word);

			pthread_mutex_lock(hashTables[key].lock);

			int collisionIndex = hashTables[key].collisions;
			hashTables[key].words[collisionIndex] = (char*)malloc(count + 1);
			for(int q = 0; q <= count; q++)
				hashTables[key].words[collisionIndex][q] = word[q];

			hashTables[key].collisions++;

			pthread_mutex_unlock(hashTables[key].lock);

			/*if(hashTables[key].collisions > highestColl)
				highestColl = hashTables[key].collisions;*/
			
			count = 0;	
			//printf("Added: %s to hashtable at key: %d\n",word,key);
		}
		else
		{
			word[count] = c;
			count++;
			if(count > MAX_WORD_SIZE)
			{
				fprintf (stderr, "Invalid Word Found!\n");
				exit(0);
			}
		}
	}

	free(word);
	//printf("Thread End\n");

	return NULL;
}

void initTable()
{
	for(int m = 0; m < MUTEX_AMOUNT; m++)
	{
		mutexPool[m] = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(mutexPool[m],NULL);
	}

	for(unsigned int k = 0; k < HASH_SIZE; k++)
	{
		hashTables[k].lock = mutexPool[k / MUTEX_AMOUNT];
		hashTables[k].collisions = 0;
		hashTables[k].words = malloc(HASH_SIZE / 2 * MAX_WORD_SIZE);
	}
}



int main(int argc, char** argv)
{	
	pthread_t *writeThreads = (pthread_t*)malloc(sizeof(pthread_t) * N_WRITE_THREADS);
	pthread_t *readThreads = (pthread_t*)malloc(sizeof(pthread_t) * N_READ_THREADS);
	initTable();

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
		
	FILE *dictionary = fopen(argv[1], "r");
	FILE *wordCheck = fopen(argv[2], "r");
	
	if(dictionary == NULL || wordCheck == NULL ) //ensure input file exists
	{
		fprintf(stderr, "Error accessing input files\n");
		return -1;
	}
		
	struct stat fileStat1;
	struct stat fileStat2;
	
	stat(argv[1], &fileStat1);
	stat(argv[2], &fileStat2);
	
	char* dictBuffer = (char*)malloc(fileStat1.st_size + 1);
	char* wordCheckBuff = (char*)malloc(fileStat2.st_size + 1);
	
	if (dictBuffer == NULL || wordCheckBuff == NULL) 
	{
		fprintf (stderr, "Memory error");
		return -1;
	}
	
	fread(dictBuffer, 1, (int)fileStat1.st_size, dictionary);
	fread(wordCheckBuff, 1, (int)fileStat2.st_size, wordCheck);

	fclose(dictionary);
	fclose(wordCheck);

	dictBuffer[(int)fileStat1.st_size] = '\0';
	wordCheckBuff[(int)fileStat2.st_size] = '\0';
	
	int jumpSize = ((int)fileStat1.st_size / N_WRITE_THREADS) + 1;
	int jumpSize2 = ((int)fileStat2.st_size / N_READ_THREADS) + 1;

	struct bufferForThreads *writeStructs = (struct bufferForThreads*)malloc(sizeof(struct bufferForThreads) * N_WRITE_THREADS);
	struct bufferForThreads *readStructs = (struct bufferForThreads*)malloc(sizeof(struct bufferForThreads) * N_READ_THREADS);

	//printf("Creating Threads....\n");

	for(int i = 0; i < N_WRITE_THREADS; i++)
	{
		int start = i * jumpSize;
		int end = (i * jumpSize) + jumpSize;

		if(i != 0)
		{
			while(!isspace(dictBuffer[start - 1]))
				start++;
		}

		if(i != N_WRITE_THREADS - 1)
		{
			while(!isspace(dictBuffer[end]))
				end++;
		}

		writeStructs[i].buffer = dictBuffer;
		writeStructs[i].startIndex = start;
		writeStructs[i].endIndex = end;
		pthread_create(&writeThreads[i], NULL, fillHashTable, (void*)&writeStructs[i]);
	}

	for(int i = 0; i < N_WRITE_THREADS; i++)
	{
		pthread_join(writeThreads[i], NULL);
	}

	//printf("Finished adding to hashtable!\n");
	//printf("Highest Collision = %d\n", highestColl);
	

	for(int i = 0; i < N_READ_THREADS; i++)
	{
		int start = i * jumpSize2;
		int end = (i * jumpSize2) + jumpSize2;

		if(i != 0)
		{
			while(!isspace(wordCheckBuff[start - 1]))
				start++;
		}

		if(i != N_READ_THREADS - 1)
		{
			while(!isspace(wordCheckBuff[end]))
				end++;
		}

		readStructs[i].buffer = wordCheckBuff;
		readStructs[i].startIndex = start;
		readStructs[i].endIndex = end;
		pthread_create(&readThreads[i], NULL, testWords, (void*)&readStructs[i]);
	}

	for(int i = 0; i < N_READ_THREADS; i++)
	{
		pthread_join(readThreads[i], NULL);
	}
	

	free(wordCheckBuff);
	free(dictBuffer);
	free(writeThreads);
	free(readThreads);
	free(writeStructs);
	free(readStructs);
	
	for(int i = 0; i < MUTEX_AMOUNT; i++)
		pthread_mutex_destroy(mutexPool[i]);

	for(int i = 0; i < HASH_SIZE; i++)
	{
		for(int j = 0; j < hashTables[i].collisions; j++)
			free(hashTables[i].words[j]);
		free(hashTables[i].words);
	}
	
	//printf("done\n");
	
	return 0;	
}

