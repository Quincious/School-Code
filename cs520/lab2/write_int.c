/*
Jonathan Hart
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int main(int argc, char** argv)
{
	if(argc > 3)
	{
		printf("Too many arguments!\n");
		return -1;
	}
	else if(argc < 3)
	{
		printf("Not enough arguments!\n");
		return -1;
	}
	
	char* end;
	
	errno = 0;
	unsigned long input = strtol(argv[2], &end, 16);
	
	if(errno != 0 || input > 0xFFFFFFFFl )
	{
		printf("%s is not a valid number (Overflow)\n", argv[2]);
		return -1;
	}
	
	if((*end) != 0)
	{
		printf("%s is not a valid number\n", argv[2]);
		return -1;
	}
	
	FILE *file = fopen(argv[1], "w+");
	
	if(file == NULL) 
	{
		printf("error creating file\n");
		return -1;
	}
	
	fwrite((const void*) & input, sizeof(int), 1, file);
	
	fclose(file);
	
	return 0;		
}