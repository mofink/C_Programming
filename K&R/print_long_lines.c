#include <stdio.h>

int get_line(char line[]); /*returns length of line */

void print(char s[]);



int main()
{
	char line[1000];
	int len;

	while ((len = get_line(line)) > 0)
	{
		if (len > 10)
		{
			print(line);
		}
	}
	return 0;
}

int get_line(char line[])
{
	int i,c;
	for (i = 0;  (c = getchar()) != '\n' && c != EOF; ++i) 
	{
		line[i] = c;
	}
	if (c == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	

	return i;
}

void print(char s[])
{
	int i,c;
	for (i = 0; ( (c = s[i]) != '\0' ); ++i)
		putchar(c);
}






