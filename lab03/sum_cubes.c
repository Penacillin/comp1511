#include <stdio.h>

int main()
{
	int n = 0;
	
	printf("Sum how many cubes? ");
	scanf("%d" , &n);
	
	int sum = 0;

	for(int i = 1; i <= n ; i++)
	{
		sum += i * i * i;
		if(i != n)
			printf("%d^3 + ", i);
		else
			printf("%d^3", i);
	}

	printf(" = %d\n", sum);
	
	return 0;
}
