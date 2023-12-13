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

	// order 3 numbers
	(a > b && (a = b + a, b = a - b, a = a - b)), (c > a && c < b && (b = c + b, c = b - c, b = b - c)), (c < a && c < a && (b = c + b, c = b - c, b = b - c) && (a = b + a, b = a - b, a = a - b));	

	printf("The integers in order are: %d %d %d\n", a , b ,c);

	return 0;
	
}	
