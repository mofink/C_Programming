#include <stdio.h>


int my_strstr(char *haystack,char *needle);

int main(void)
{
    return 0;
}

int my_strstr(char *haystack,char *needle)
{
    for(;*haystack;haystack++)
    {
        const char *n,*h;
        for(h = haystack,n = needle;*h && *n && (*h == *n);++h,++n)
        {
            ;
        }
        if(*n=='/0')
        {
            return 1;
        }
    }
     return NULL;
}

