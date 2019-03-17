/* limited implementation of ls UNIX command */
/* Note that getopt.h is a GNU extension 
can also use unistd.h */

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>


void print_help(void);

int main(int argc, char *argv[])
{
	/* http://man7.org/linux/man-pages/man1/ls.1.html for argument options */
	char * short_options = "alrRht";
	struct option long_options[] =  /* list of structs */
	{	/* { long argument name (string constant), has_argument, NULL, short argument (char) } */
		{"all", 0, NULL, 'a'},
		{"long", 0, NULL, 'l'},
		{"reverse", 0, NULL, 'r'},
		{"recursive", 0, NULL, 'R'},
		{"help", 0, NULL, 'h'},
		{"time", 0, NULL, 't'}
		
	};

	int print_all = 0;
	int long_format = 0;
	int reversed = 0;
	int time_format = 0;

	int next_option;

	do
	{
		/* https://linux.die.net/man/3/getopt_long */
		next_option = getopt_long(argc,argv,short_options,long_options,NULL);

		switch(next_option)
		{
			case 'a':
				print_all = 1;

			case 'l':
				long_format = 1;

			case 'r':
				reversed = 1;

			case 'R':
				//implement recursive

			case 'h':
				print_help();

			case 't':
				time_format = 1;

			case '?':
				printf("INVALID ARGUMENT\n");
				next_option = -1;
				break;

			case -1:
				break;

			default:
				printf("YOU SHOULDN'T BE READING THIS MESSAGE\n");
				abort();
		}

	} while ( next_option != -1);

	

	DIR *dir;
	if (argc == 1)
	{
		dir = opendir("./");
	}
	else
	{
		dir = opendir(argv[1]);
	}
	

	struct dirent *file; //https://www.gnu.org/software/libc/manual/html_node/Directory-Entries.html
	while ((file = readdir(dir)) != NULL)
	{
		printf("%s\n",file->d_name);
	}
	
	// need to implement arguments to ls as listed above






	return 0;
}

void print_help()
{
	printf("Placeholder for help text\n");
}
