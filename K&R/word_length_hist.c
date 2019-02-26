/* prints histogram to show frequency of word lengths
    remember to terminate inputs with ctrl+D on Unix systems  */

#include <stdio.h>

#define IN 1
#define OUT 0 

int main()
{
	int c, i, j, numc;
	int freq[10];
	
	numc = 0;
	for (i = 0; i < 10; ++i)
		freq[i] = 0;


	while ((c = getchar()) != EOF)
	{
			if (c == ' ' || c == '\t' || c == '\n')
			{
				++freq[numc];
				numc = 0;
			}
			else
				++numc;
	}

	for (i = 0; i < 10; ++i)
	{
		for (j = 0; j < freq[i]; ++j)
		{
			putchar(' ');
		}
		putchar('|');
		putchar('\n');
	}
}

