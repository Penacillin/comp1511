//heron.c
//

#include <stdio.h>
#include <math.h>

int main()
{
	printf("%d %d", sizeof(float), sizeof(double));

	double a = 0, b = 0, c = 0;

	printf("Enter side 1: ");
	scanf("%lf", &a);

	printf("Enter side 2: ");
	scanf("%lf", &b);

	printf("Enter side 3: ");
	scanf("%lf", &c);	

	double s = (a + b + c) / 2;
	// Apply Heron's formula
	double area = sqrt(s*(s-a)*(s-b)*(s-c));
	if(!(area>0))
		printf("Error: triangle inequality violated.\n");
	else
		printf("Area = %lf\n", area);

	return 0;
}
