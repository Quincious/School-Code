#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <linux/time.h>

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
	unsigned long numOfReads = strtol(argv[1], &end1, 16);
	
	if(errno != 0 || numOfReads > 0xFFFFFFFFl )
	{
		fprintf(stderr, "%s is not a valid number (Overflow)\n", argv[1]);
		return -1;
	}
	
	if((*end1) != 0)
	{
		fprintf(stderr, "%s is not a valid number\n", argv[1]);
		return -1;
	}
	
	char *end2;
	unsigned long numOfItems = strtol(argv[2], &end2, 16);
	
	if(errno != 0 || numOfItems > 0xFFFFFFFFl )
	{
		fprintf(stderr, "%s is not a valid number (Overflow)\n", argv[2]);
		return -1;
	}
	
	if((*end2) != 0)
	{
		fprintf(stderr, "%s is not a valid number\n", argv[2]);
		return -1;
	}	
	
	/*FILE *cacheResults = fopen("cacheResults.txt", "a");

	if(cacheResults == NULL)
	{
		fprintf(stderr, "Error creating or opening file\n");
		return -1;
	}*/

	//for(unsigned long j = 200; j < 200000; j += 200)
	//{
		//numOfItems = j;

		unsigned int *numbers = malloc(sizeof(unsigned int) * numOfItems);

		if(numbers == 0)
		{
			fprintf(stderr, "Error: Not enough Memory!\n");
			return -1;
		}
	
		for(unsigned long i = 0; i < numOfItems; i++)
		{	
			numbers[i] = rand();
		}


		struct timeval startTime, endTime;

		unsigned int x = 0;
		double avgTime;
		
		for(int i = 0; i < 50; i++)
		{
			gettimeofday(&startTime);

			for(unsigned long l = 0; l < numOfReads; l++)
			{
				x += numbers[rand() % numOfItems];
			} 

			gettimeofday(&endTime);

			double timeTaken = ((double) (endTime.tv_usec - startTime.tv_usec)/1000000 + (double) (endTime.tv_sec - startTime.tv_sec));
			timeTaken = timeTaken * 100000;

			avgTime += timeTaken;
			x = 0;
		}	

		avgTime = avgTime / 50;

		printf("%lu\t%.2f\n", numOfItems, avgTime);
		//fprintf(cacheResults, "%lu\t%.2f\n", numOfItems, avgTime);

		free(numbers);
	//}	

	//fclose(cacheResults);
}