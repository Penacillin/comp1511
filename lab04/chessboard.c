#include <stdio.h>

int main()
{
    int n = 0;
    printf("Enter size: ");
    scanf("%d", &n);
    
    for(int row = 0; row < n; row++)
    {
        for(int col = 0; col < n; col++)
        {
            if((col + ((row + 1) % 2)) % 2 == 0)
            {
                printf("*");
            }
            else if (1)
            {
                printf("-");
            }
        }
        printf("\n");
    }
    
    return 0;
}
