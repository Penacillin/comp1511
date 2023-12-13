#include <stdio.h>

int main()
{
	int n = 0;

	printf("Square size: ");
	scanf("%d", &n);

	int i = 1;
	while(i <= n * n)
	{
		printf("*");
		if(i % n == 0)
			printf("\n");

		i++;
	}

	return 0;
}
