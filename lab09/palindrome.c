#include <stdio.h>
#include <string.h>

int main()
{
    char str[4097];
    int len = 0;
    
    printf("Enter a string: ");
    fgets(str, 4097, stdin);
    
    len = strlen(str);
    
    
    for(int i = 0; i < len / 2; i++)
    {
        if(str[i] != str[len-i-2])
        {
            printf("String is not a palindrome\n");
            return 0;
        }
    }
    printf("String is a palindrome\n");
    
    return 0;
    
}
