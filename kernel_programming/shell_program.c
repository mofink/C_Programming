
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAXLEN 1000
#define MAXARGS 10
#define PRINT printf("PING\n"); //for debugging

struct command_struct /*read the cmd line input into here */
{
	char *name;
	char *argv[MAXLEN];
} *command;

int getword(char *s);
void assign_to_struct(struct command_struct *command,char * s, int j);
void copy_word(char *s1, char *s2);
int count_array(char **s);
int buildpath(char *s,char *mypath, char *dir);
 
int main(void)
{	
	printf("Welcome to Mo's Terminal Application\nTo quit use the 'exit' command\n");
	int exit_flag = 0;
	char *username;
	username = getlogin();
	char cwd[MAXLEN];

	command = (struct command_struct *) malloc(sizeof(struct command_struct));
	command->name = (char *) malloc(sizeof(char)*MAXLEN);
	int i;
	for (i = 0; i < MAXARGS; ++i)
	{
		command->argv[i] = (char *) malloc(sizeof(char)*MAXLEN);
	}
	char *filename = (char *) malloc(sizeof(char)*MAXLEN);
	char *mypath; 
	int *num_args = (int *) malloc(sizeof(int)); //make num_args global
	
	while (!exit_flag)
	{

		int j = 0, c;
		char *dir = ".";
		
		printf("%s@%s$ ", username, getcwd(cwd, sizeof(cwd)));
		

		for (;;) /*infinite loop waiting for input */
		{	
			char word[MAXLEN]; /*have to redefine buffer each iter because of pointer assignment */
			c = getword(word);
			assign_to_struct(command,word,++j);
			
			if (c == '\n')
			{
				assign_to_struct(command,"SIGCLOSE",++j); //SIGCLOSE is a madeup signal to indicate end of argument list, assume user will not input this 
				*num_args = count_array(command->argv);
				break;
			}
		}
		


		mypath=getenv("PATH"); // cheating 
		if (strcmp(command->name,"exit")) // skip buildpath if cmd = exit
		{
			if (buildpath(filename,mypath,dir))
			{	




				//printf("The complete file path for %s is %s\n",command->name,filename);
				pid_t pid;
				if ((pid = fork()) < 0)
				{
					printf("Failed to fork. Aborting...\n");
					abort();
				}
				else if (pid == 0) // This is the child process 
				{

					if (*num_args == 0)
					{
						//printf("Hello from the child process: calling 'execvp' to execute %s with no arguments\n",filename);
						char * args[] = {".",NULL};
						execvp(filename,args);
					}
					else // has arguments
					{
						//int i;
						//printf("Hello from the child process: calling 'execvp' to execute %s with %d arguments: ",filename,*num_args);
						//for (i = 0; i < *num_args; ++i)
						//{
						//	printf("%s ",command->argv[i]);
						//}
						//printf("\n");
						char * args[*num_args + 2]; //have to add name of command to beginning and NULL to the end for exec call
						args[0] = filename;
						int i;
						for (i = 0; i < *num_args; ++i)
						{
							args[i+1] = command->argv[i];
						}
						args[i+1] = NULL;
					
						
						execvp(filename,args);
					}
					exit(0);
				}
				else
				{
					//printf("Hello from the parent process with pid %d: waiting for child to terminate\n...\n",pid);
					int status;
    				waitpid(pid, &status, 0);
    				//printf("Child process returned with exit status %d\n",status);
				}	
				
			}

			*num_args = 0;
			command->name[0] = '\0';
		}


		
		else //(!strcmp(command->name,"exit"))
		{
			exit_flag = 1;
			printf("So long and thanks for all the fish\nExiting....\n");
			free(username);
			free(command->name);
			while(command->argv[i++])
			{
				free(command->argv[i]);
			}
			free(filename);
			free(num_args);
		}
		

	}


}

int getword(char *s)
{	
	int c;
	int i = 0;
	while ((c = getchar()) > 0 && c != '\n' && c != ' ' && c != '\t')
	{
		s[i++] = c;
	}
	s[i] = '\0';
	return c;
}

void assign_to_struct(struct command_struct *command, char * s, int j)
{
	if (j == 1)
	{
		strcpy(command->name, s);
	}
	else
	{
		strcpy(command->argv[j-2], s);	
	}
}

int count_array(char **s)
{
	int i = 0;
	while(command->argv[i])
	{
		if (!strcmp(command->argv[i],"SIGCLOSE"))
		{
			break;
		}
		i++;
	}
	return i; //account for NULL appended to the end of argument list
}

int buildpath(char *filename, char *mypath, char *dir)
{

	
	sprintf(filename,"%s/%s",dir, command->name);
	if (access(filename,F_OK) == 0) /* http://pubs.opengroup.org/onlinepubs/009695399/functions/access.html */
	{
		/* printf("FOUND LOCALLY\n"); */
		return 1;
	}
	
	int c, i, j;
	i = j = 0;
	filename[0] = '\0'; /* reset */

	if (command->name[0] == '/') /* case absolute path */
	{
		if (access(command->name,F_OK) == 0) 
		{
			return 1;
		}
	}
	
	while ((c = mypath[i++]))
	{
		
		if (c == ':')
		{
			sprintf(filename,"%s/%s", filename, command->name);
			if (access(filename,F_OK) == 0) 
				{
					/* printf("FOUND IN PATH VAR\n"); */
					return 1;
				}
				else
				{	
					int i;
					for (i = 0; filename[i]; ++i)
						filename[i] = '\0'; /* reset */
					j = 0;
				}

		}
		else
		{
			filename[j++] = c;	
		}

	}

	printf("COMMAND NOT FOUND\n");
	return 0;
}

