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
            if(col == row || col == n - row - 1)
            {
                printf("*");
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");
    }
    

    return 0;
}
