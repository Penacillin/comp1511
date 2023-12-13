#include <stdio.h>

int main()
{
	int input = 0;

	printf("Please enter an integer :");
	scanf("%d", &input);

	printf("You entered ");

	switch(input)
	{
	case 1:
		printf("one");
		break;
	case 2:
		printf("two");
		break;
	case 3:
		printf("three");
		break;
	case 4:
		printf("four");
		break;
	case 5:
		printf("five");
		break;
	default:
		if(input > 5)
			printf("a number greater than five");
		else
			printf("a number less than one");
		
	}

	printf(".\n");

	return 0;
	
}
