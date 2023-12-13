#include <stdio.h>

int main()
{
	int start = 0, finish = 0;
	
	printf("Enter start year: ");
	scanf("%d", &start);

	printf("Enter finish year: ");
	scanf("%d", &finish);
	

	printf("The leap years between %d and %d are: ", start, finish);


	// set start to the next leap year
	if(start % 4 != 0)
		start += 4 - start % 4;

	// while start is less than or equal to the finish year, print the year while adding 4 (for each leap year)
	while(start <= finish){
		
		
		if(start % 4 == 0 && start % 100 != 0)
			printf("%d ", start);
		else if (start % 400 == 0)
			printf("%d ", start);
				
		start += 4;
	}

	printf("\n");

	return 0;
}
