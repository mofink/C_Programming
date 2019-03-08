/* NOTE: THIS WAS WRITTEN FOR LINUX SYSTEMS */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAXLEN 1000
#define MAXARGS 10

struct command_struct /*read the cmd line input into here */
{
	char *name;
	char *argv[MAXLEN];
} *command;

int getword(char *s);
void assign_to_struct(struct command_struct *command,char * s, int j);
void copy_word(char *s1, char *s2);
int buildpath(char *s,char *mypath, char *dir);

int main(void)
{	
	printf("Welcome to Mo's Terminal Application\nTo quit use the 'exit' command\n");
	int exit_flag = 0;
	while (!exit_flag)
	{

		command = (struct command_struct *) malloc(sizeof(struct command_struct));
		command->name = (char *) malloc(sizeof(char)*MAXLEN);
		int i;
		for (i = 0; i < MAXARGS; ++i)
		{
			command->argv[i] = (char *) malloc(sizeof(char)*MAXLEN);
		}

		int j = 0, c;
		char *dir = ".";
		
		/* frills for fun. should move buf def to outside of loop for efficiency but I want to keep it all together for now */
		char *buf;
		buf = getlogin();
		char cwd[MAXLEN];
		printf("%s@%s$ ", buf, getcwd(cwd, sizeof(cwd)));

		for (;;) /*infinite loop waiting for input */
		{	
			char word[MAXLEN]; /*have to redefine buffer each iter because of pointer assignment */
			c = getword(word);
			assign_to_struct(command,word,++j);

			if (c == '\n')
				break;
		}
		

		char *filename = (char *) malloc(sizeof(char)*MAXLEN);

		char *mypath=getenv("PATH"); /* cheating */
		if (strcmp(command->name,"exit")) /*skip buildpath if cmd = exit. need to generalize this */
		{
			if (buildpath(filename,mypath,dir))
			{
				printf("The complete file path for %s is %s\n",command->name,filename);
				pid_t pid;
				if ((pid = fork()) < 0)
				{
					printf("Failed to fork.\n");
				}
				else if (pid == 0) /* This is the child process */
				{
					printf("Hello from the child process: calling 'execv' to execute %s\n",filename);
					exit(0);
				}
				else
				{
					printf("Hello from the parent process with pid %d: waiting for child to terminate\n",pid);
					int status;
    				waitpid(pid, &status, 0);
    				printf("Child process returned with exit status %d\n",status);
				}	
			}
		}

		
		if (!strcmp(command->name,"exit"))
		{
			exit_flag = 1;
			printf("So long and thanks for all the fish\nExiting....\n");
		}

		
		{ /* local scope */
			int i = 0;
			while(command->argv[i++])
			{
				free(command->argv[i]);
			}
			free(filename);
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
		copy_word(command->name, s);
	}
	else
	{	
		copy_word(command->argv[j-2], s);
	}
}

void copy_word(char *s1, char *s2)
{
	while(*s1++ = *s2++); /* could use strcpy but I love seeing this on paper */
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
	filename[i] = '\0'; /* reset */

	if (command->name[0] == '/') /* case absolute path */
	{
		if (access(command->name,F_OK) == 0) 
		{
			return 1;
		}
	}
	
	while (c = mypath[i++])
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

