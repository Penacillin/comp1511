#include <stdio.h>

int main()
{
	int age = 0;

	printf("Enter your age:  ");
	scanf("%d", &age);

	if(age <= 12)
	{
		printf("You are too young to be dating.\n");
		return 0;
	}
	
	int lower = age / 2 + 7;
	int upper = (age - 7) * 2;

	printf("Your dating range is %d to %d years old.\n", lower, upper);

	return 0;
}
