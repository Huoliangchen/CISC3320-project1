#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50

char **commandSplit(char []);
void execute(char **);

int main()
{
	char input[MAX];
	char **command;
	int status;
	
	char *commandBuiltins[] = {"list", "history", "printwd", "chdir", "complie", "run", "\0"};
	
	while(status)
	{	
		printf("Myshell> ");
		fgets(input, MAX, stdin);
    if(input[strlen(input) - 1] == '\n')
          input[strlen(input) - 1] = '\0';

		command = commandSplit(input);
    if (!command[0]) {
            continue;
        }
        
		execute(command);
	}
	
	return 0;
}

char **commandSplit(char *input)
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

void execute(char **command)
{ 
  if(strcmp(command[0], "chdir") == 0){
    printf("cd");
  }
else if(strcmp(command[0], "list") == 0){
    printf("ls");
	pid_t pid;
        int status;
        pid = fork();
        if(pid < 0){
                printf("fork failed");
        }
        if(pid == 0){
                if(execlp(command[1], "ls", NULL) < 0){
                        perror(command[1]);
                        exit(1);
                }
        }else {
                wait(NULL);
                }

  }
  else if(strcmp(command[0], "history") == 0){
    printf("his");
  }
  else if(strcmp(command[0], "printwd") == 0){
    printf("wd");
  }
  else if(strcmp(command[0], "complie") == 0){
    printf("complie");
  }
  else if(strcmp(command[0], "run") == 0){
    printf("run");
  }else if (strcmp(command[0], "exit") == 0)){	
	exit(0);	  
  }else{
    printf("command doese not exist.\n");
  }
}
