#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main()
{
    char str[4097];
    char cleanStr[4097];
    
    printf("Enter a string: ");
    fgets(str, 4097, stdin);
    
    
    int i = 0;
    for(char* c = str; *c != '\n' && *c != '\0'; c++)
    {
        if((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z'))
        {
            cleanStr[i++] = tolower(*c);
        }
    }
    cleanStr[i] = '\0';
    
    int len = strlen(cleanStr);
    for(int j = 0; j < len / 2; j++)
    {
        if(cleanStr[j] != cleanStr[len-j-1])
        {
            printf("String is not a palindrome\n");
            return 0;
        }
    }
    printf("String is a palindrome\n");
    
    return 0;
    
}
