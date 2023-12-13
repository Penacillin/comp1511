#include <stdio.h>

int main()
{
    int n = 0;
    printf("Enter number: ");
    scanf("%d", &n);
    int sum = 0;
    printf("The factors of %d are:\n", n);
    for(int i = 1; i <= n; i++)
    {
        if(n % i == 0)
        {
            sum += i;
            printf("%d\n", i);
        }
    }
    
    printf("Sum of factors = %d\n", sum);
    
    if(n == sum - n)
    {
        printf("%d is a perfect number\n", n);
    }
    else
    {
        printf("%d is not a perfect number\n", n);
    }
    
    return 0;
}
