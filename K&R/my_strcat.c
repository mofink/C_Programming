#include <stdio.h>

char src[] = "goog morning";
char dest[] = "hello world";

char* my_strcat(char *src_p, char *dest_p);

int main(void)
{
    char *src_p = src;
    char *dest_p = dest;
    char *val = my_strcat(src_p,dest_p);
    puts(val);
    return 0;
}

char* my_strcat(char *src_p,char *dest_p)
{
    char *rdest = dest_p;
    while(*dest_p)
    {
        dest_p++; // move dest pointer to null character"
    }
    while(*src_p)
    {
        *dest_p++ = *src_p++;
    }
    return rdest;
}

