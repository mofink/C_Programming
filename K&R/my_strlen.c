 #include <stdio.h>

int my_strlen(char *str_pointer);
int total;
char *str;


int main(void)
{
    str = "SOME STRING";
    printf("%d\n",my_strlen(str));
    return 0;
}

int my_strlen(char *str_pointer)
{
    
    while(*str_pointer)
    {
        total+=1;
        str_pointer++;
    }
    return total;
}

