#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include "myshell.h"

int main(void)
{
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
