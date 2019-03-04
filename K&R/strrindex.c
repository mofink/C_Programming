#include <stdio.h>
#include <string.h>

/* returns position of right most occurence of t in s, else -1 */
int strrindex(char s[], char t[]);

int main()
{
	char s[] = "Ah Love could you and I with Fate conspire To grasp this sorry Scheme of Things entire, Would not we shatter it to bits -- and then Re-mould it nearer to the Heart's Desire";
	char t[] = "ould";
	printf("%d\n",strrindex(s,t));
	
	return 0;
}

int strrindex(char s[], char t[])
{
	int i, j, k, ans;
	ans = -1;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = i, k = 0; t[k] != '\0'  && s[j] == t[k]; j++, k++)
			;
		if (t[k] == '\0' && k > 0)
		{
			ans = i;
		}
	}
	return ans;
}
