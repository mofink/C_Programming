/* reverse string in place using recursion */

#include <stdio.h>
#include <string.h> /* for strlen method */ 

void reverse(char s[]);


int main(void)
{

	char s[] = "123456";
	reverse(s);

	printf("%s\n", s);
	return 0;
}

void reverse(char s[])
{
	static int i = 0;
	char tmp;

	tmp = s[strlen(s) - i - 1];
	s[strlen(s) - i - 1] = s[i];
	s[i] = tmp;

	if (i++ < (strlen(s)/2) - 1)
	{
		reverse(s);
	}

}
