#include <stdio.h>
#include <string.h>

int is_palindrome(char* word);

int main(void)
{
	char word[100] = "racecar";
	printf("%s",is_palindrome(word) ? "YES\n" : "NO\n");
	strcpy(word, "This should return False");
	printf("%s",is_palindrome(word) ? "YES\n" : "NO\n");
	return 0;


}

int is_palindrome(char* word)
{
	char* ptr = word;
	int j = 0;
	while (*ptr)
	{
		++j,++ptr;
	}
	j--;

	int i;
	for (i = 0; i < j; ++i, --j)
	{
		if (word[i] != word[j])
			return 0;
	}
	return 1;
}
