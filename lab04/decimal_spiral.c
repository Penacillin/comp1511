#include <stdio.h>

int calculatePoint(int row, int col, int n)
{
	int edges = 0;
	int value = 0;
	if (col + 1 < n / 2)
	{
		edges = 4 * (col / 2 + 1) - 1;
		value += row - (col + 2);
	}
	else
	{
		edges = 4 * ((n - col - 1) / 2);
		value -= row - (n-col-1);
	}	
	int k = n - edges - 1;
	value += ((k+k%2)/2+1)*(((k+k%2)/2)*4)/2 - (k%2)*(k+k%2);	
	return value % 10;
}

int posMod(int n, int m)
{
	if (n < 0)
	{
		n += m;
		return n;
	}
	else
		return n % m;
}

int main()
{
    int n = 0;
    printf("Enter size: ");
    if(scanf("%d", &n) != 1)
        return 1;

    int star = 1;
    int left = 0;
    int right = 0;
    
    int startNumber =  ((n-1)*(8+((n-3)*2))/4 + n -1) % 10;
    
    for(int i = 0; i < n; i++)
    {      
        int j = 0;
        if(i == 1)
            star = 0;
        else
            star = 1;
        for(; j < left; j++)
        {
            if(star)
            {		
				printf("%d", calculatePoint( i, j, n));
            }
            else
                printf("-");
            star = !star;
        }
		int curr = 0;
		if (i > 0)
			curr = calculatePoint( i, j, n);
		else
			curr = startNumber;
        for(; j < n - right; j++)
        {
            if(star)
            {        
				printf("%d", curr);
				if (i >= n / 2 + 1)
					curr++;
				else
					curr--;
				curr = posMod(curr, 10);
            }
            else
                printf("-");
        }
        star = !star;
        for(; j < n; j++)
        {
            if(star)
            {                
                printf("%d", calculatePoint( i, j, n));
            }
            else
                printf("-");
            star = !star;
        }

		// Increment/decrement partitioners
        if(i >= 0 && i < n /2 )
            right++;
        else
            right--;
        
        if(i >= 1 && i < n/2 + 1)
            left++;
        else
            left--;

        printf("\n");
    } // End row looper
    
    return 0;
}