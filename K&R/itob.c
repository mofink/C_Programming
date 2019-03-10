/* converts int to base b representation */

#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse_str(char s[]);

int main() 
{
	char s[1000];
	int n = 100;
	int b = 2;
	itob(n,s,b);

	printf("%s\n", s);
	return 0;
}

void itob(int n, char s[], int b)
{
	int sign, i;
	
	i = 0;

	do
	{
		s[i++] = n % b + '0';
	} while ((n /= b) > 0);


	reverse_str(s);
	
	i = 0;
	while(s[i])
		i++;
	s[++i] = '\0';

}

void reverse_str(char s[])
{
	int i,j;
	char c;
	for (i = 0, j = strlen(s) - 1; i < j; s++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

