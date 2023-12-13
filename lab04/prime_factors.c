#include <stdio.h>

int main()
{
    int n = 0;
    printf("Enter number: ");
    scanf("%d", &n);
    
    
    int factors = 0;
    int first = 1;
    int orig = n;
    
    while(n % 2 ==0)
    {
        n /= 2;
        factors++;
    }
    
    for(int i = 3; i < n; i += 2)
    {
        while(n % i == 0)
        {
            factors++;
            n /= i;
            
        }
        
    }
    
    if(factors == 0)
    {
        printf("%d is prime\n", n);
        return 0;
    }
    
    // print factors
    factors = 0;
     first = 1;
     n = orig;
    printf("The prime factorization of %d is:\n", n);
    
     
    
    while(n % 2 ==0)
    {
        if(!first)
            printf(" * 2"), first = 0;
        else
            printf("2"), first = 0;
        n /= 2;
        factors++;
    }
    
    for(int i = 3; i < n; i += 2)
    {
        while(n % i == 0)
        {
            if(first)
                printf("%d", i), first = 0;
            else
                printf(" * %d", i), first = 0;
                
            factors++;
            n /= i;
            
        }
        
    }
    
    if(n > 2)
    {
        printf(" * %d", n);
    }
    printf(" = %d", orig);
    printf("\n");
    
    return 0;
}
