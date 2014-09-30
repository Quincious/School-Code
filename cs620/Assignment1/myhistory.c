//Jonathan Hart
//cp620 Assignment 2 part 2
//myhistory.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include "myhistory.h"

int main(void)
{
	historycount = 0;

	while(1)
	{
		printf("myshell> ");
		executecmd();
	}

	//should never reach here
	printf("Shell loop broken.\n");
	return EXIT_FAILURE;
}

void executecmd()
{
	char cmd[CMD_MAX_LENGTH];
	
	//get input command
	fgets(cmd, CMD_MAX_LENGTH, stdin);

	//ensure null terminator at end
	int endofcmd = strlen(cmd) - 1;
	while(isspace(cmd[endofcmd]))
		cmd[endofcmd--] = '\0';
	
	//prep cmd for execution
	char * finalcmd[CMD_MAX_LENGTH];
	int index = 0;
	
	finalcmd[index] = strtok(cmd, " ");
	
	while(index < CMD_MAX_LENGTH && finalcmd[index] != NULL)
		finalcmd[++index] = strtok(NULL, " ");

	//execute command
	if(finalcmd[0] == NULL)
		return;
	else if(!strcmp(finalcmd[0], "quit"))
		exit(EXIT_SUCCESS);

	//add cmd to history
	//if history full, remove oldest to make room
	if(historycount == 100)
		shifthistory();

	strcpy(history[historycount], finalcmd[0]);
	historycount++;

	//if history, do not call execvp
	if(!strcmp(finalcmd[0], "history"))
	{
		printhistory();
		return;
	}

	pid_t pid = fork();
	
	if(pid < 0)
		printf("Error: pid < 0");
	else if(pid > 0)
	{
		int status = 0;
		wait(&status);
	}
	else
	{
		execvp( finalcmd[0], finalcmd);

		//if reaches this point, unknown command
		printf("Unknown command: %s\n", finalcmd[0]);
		abort();
	}
	
}

void shifthistory()
{
	int i;	
	for(i = 0; i < historycount; i++)
		strcpy(history[i], history[i+1]);

	historycount--;
}

void printhistory()
{
	int i;
	for(i = 0; i<historycount; i++)
		printf("%d: %s\n",i+1,history[i]);
}

