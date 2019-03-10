#include <stdio.h>
#include <stdlib.h>

char * reverse_str(char *str);

int main(void)
{
    char str[] = "hello this is a string";
    puts(str);
    puts(reverse_str(str));
    return 0;
}

char * reverse_str(char *str)
{
    char *begin = str;
    char *reversed_str = str; //moves from the beginning, str moves backwards
    char tmp;
    
    while(*str)
    {
        str++; // run until points to '/0' element
    }
    str--; //point to last element in array
    
    while(reversed_str < str)
    {
        tmp = *reversed_str;
        *reversed_str = *str;
        *str = tmp;
        
        reversed_str++;
        str--;
    }
    
    return begin;
}
