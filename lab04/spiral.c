#include <stdio.h>

int main()
{
    int n =0;
    printf("Enter size: ");
    scanf("%d", &n);

    int star = 1;
    int left = 0;
    int right = 0;
    
    int startNumber = 0;
    
    for(int i = 2; i < n; i+= 2)
        startNumber += i*2;
    startNumber += n - 1;
    startNumber %= 10;
    
    for(int i = 0; i < n; i++)
    {
      
        int j = 0;
        if(i == 1)
            star = 0;
        else
            star = 1;
        for(; j < left && j < n; j++)
        {
            if(star)
            {
                printf("*");
           
            }
            else
                printf("-");
            star = !star;
        }
       

        for(; j < n - right && j < n; j++)
        {
            if(star)
            {                
                printf("*");
            }
            else
                printf("-");
        }
        star = !star;
        for(; j < n && j < n; j++)
        {
            if(star)
                printf("*");
            else
                printf("-");
            star = !star;
        }
        if(i >= 0 && i < n /2 )
            right++;
        else
            right--;
        
        if(i >= 1 && i < n/2 + 1)
            left++;
        else
            left--;
        //printf("%d %d", left, right);
        printf("\n");
    }
    
    return 0;
}
