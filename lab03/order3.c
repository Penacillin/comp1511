#include <stdio.h>

int main()
{
	int a = 0, b = 0, c= 0;

	printf("Enter integer: ");
	scanf("%d", &a);

	printf("Enter integer: ");
	scanf("%d", &b);

	printf("Enter integer: ");
	scanf("%d", &c);

	printf("The integers in order are: ");

	if(a > b)
	{
		if(b > c)
		{
			printf("%d %d %d", c, b, a);
		}
		else if(c > a)
		{
			printf("%d %d %d", b, a, c);
		}
		else
		{
			printf("%d %d %d", b, c, a);
		}
	}
	else // (b > a)
	{
		if(a > c)
		{
			printf("%d %d %d", c, a, b);
		}
		else if(c > b)
		{
			printf("%d %d %d", a, b, c);
		}
		else
		{
			printf("%d %d %d", a, c, b);
		}
	}

	printf("\n");

	return 0;
	
}
