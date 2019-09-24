#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

char **commandSplit(char *);

int main()
{
	char input[MAX];
	char **command;
	int state = 1;
	
	char *commandBuiltins[] = {"list", "history", "printwd", "chdir"};
	
	while(state)
	{
		fgets(input, MAX, stdin);
		command = commandSplit(input);
		
		int i = 0;
		
		while(command[i])
		{
			printf("%d is %s \n", i,command[i]);
			i++;
		}
	}
	
	return 0;
}

char **commandSplit(char * input)
{
	int index = 0;
	char **command = malloc(MAX * sizeof(input));
	char *word;
	
	word = strtok(input, " ");
	while(word != NULL)
	{
		command[index] = word;
		index++;
		word = strtok(NULL, " ");
		
	}
	
	command[index] = NULL;
	
	
	return command;
}
