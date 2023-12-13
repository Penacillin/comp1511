#include <stdio.h>

int main()
{
	int n = 0;	

	printf("Enter how many cubes: ");
	scanf("%d", &n);

	for(int i = 1; i <= n; i++)
	{
		printf("%d^3 = %d\n", i, i*i*i);
	}

	return 0;
}
