#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 50


char **commandSplit(char []);           //function to split char into word.
void execute(char **, char*[], int);    //function that the shell execute command.

int main()
{
	char input[MAX];
	char **command;
	char *history[MAX];
	int historycount = 0;
	int status;
	char path[MAX];
	
	printf("/**************************************************************/\n");     //print function command
	printf("                 WELCOME TO MY SHELL!\n");
	printf("use command list to list files and directory of a given directory;\n");
	printf("use command history to list commands entered in the past;\n");
	printf("use command printwd to print current working directory;\n");
	printf("use command chdir to change to a given directory;\n");
	printf("use command gcc to complie;\n");
	printf("use command ./a.out to run.\n");
	printf("/**************************************************************/\n");
	
	while(status)
	{	
		getcwd(path, sizeof(path));                                         //show current working directory
		printf("\033[1;32mMyshell>");
		printf("\033[1;34m%s", path);
		printf("\033[0m$ ");
	 
		fgets(input, MAX, stdin);				//get input from user
   		if(input[strlen(input) - 1] == '\n')			//try to get rid of '\n' that fgets keep.
          	input[strlen(input) - 1] = '\0';                        //and replace it with '\0'.
	
    		if(input[0] != '\0' && input[0] != ' '){               //if input is not null or space, add to history
		history[historycount] = strdup(input);
    		historycount++;
    		}
		
		command = commandSplit(input);			//change char arrry to a word array.
		if (!command[0]) {				//if command is empty, skip it.
            		continue;
		}
        	execute(command, history, historycount);        //execute the command if there is one.
	}
	
	return 0;
}

char **commandSplit(char *input)
{
	int index = 0;
	char **command = malloc(MAX * sizeof(input));
	char *word;                                          // a char array to store each word from the command temporarily.
	
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

void execute(char **command, char *history[], int historycount)
{ 
  if(strcmp(command[0], "chdir") == 0){                          //function to change directory
	
	  if(command[2] != NULL){                               //only accept one arguments
		printf("too many arguments.\n");
	  }else if(chdir(command[1]) < 0){
		perror(command[1]);
	}
  }
else if(strcmp(command[0], "list") == 0){                  //function to list files or directories of a giving directroy.
   
	pid_t pid;
        
        pid = fork();
        if(pid < 0){
                printf("fork failed");
        }
        if(pid == 0){
                if(execvp("ls", command) < 0){
                        perror(command[0]);
                        exit(1);
                }
        }else {
                wait(NULL);
                }

  }
  else if(strcmp(command[0], "history") == 0 && command[1] == NULL){                //function to show pass command history
    
	  if(history[0] == NULL){
	  	printf("No history.\n");
	  }else{
	  	int index = 0;
		for(int i = 0; i < historycount; i++)
		{
			index = i+1;
			printf("%d %s\n", index, history[i]);
		}
	  }
  }
  else if(strcmp(command[0], "printwd") == 0){             //function to show current directory
    // printf("wd");
	pid_t pid;
        
        pid = fork();
        if(pid < 0){
                printf("fork failed");
        }
        if(pid == 0){
                if(execvp("pwd", command) < 0){
                        perror(command[0]);
                        exit(1);
                }
        }else {
                wait(NULL);
                }
  }
  else if(strcmp(command[0], "gcc") == 0){            //function to complie program
    	pid_t pid;
        
        pid = fork();
        if(pid < 0){
                printf("fork failed");
        }
        if(pid == 0){
                if(execvp("gcc", command) < 0){
                        perror(command[0]);
                        exit(1);
                }
        }else {
                wait(NULL);
                }
  }
  else if(strcmp(command[0], "./a.out") == 0){     //function to run program
    //printf("run");
	pid_t pid;
        
        pid = fork();
        if(pid < 0){
                printf("fork failed");
        }
        if(pid == 0){
                if(execl("./a.out", "a.out", NULL) < 0){
                        perror(command[0]);
                        exit(1);
                }
        }else {
                wait(NULL);
                }
  }else if (strcmp(command[0], "exit") == 0){	
	exit(0);	  
  }else{
    printf("command doese not exist.\n");
  }
}
