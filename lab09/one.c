#include <stdio.h>

int main()
{
    char str[4097];
    printf("Enter a string: ");
    fgets(str, 4097, stdin);
    
    for(char* c = str; *c != '\n' && *c != '\0'; c++)
    {
        printf("%c\n", *c);
    }

    return 0;
    
}
