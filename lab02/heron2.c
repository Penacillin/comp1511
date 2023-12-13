//heron.c
//

#include <stdio.h>
#include <math.h>

int main()
{
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

	double shortSide1 = 0, shortSide2 = 0;

	// determine longest side and two short sides
	double longestSide = a > b ? (a > c ? ( shortSide1 = b, shortSide2 = c, a) : ( shortSide1 = a, shortSide2 = b, c)) : (b > c ? ( shortSide1 = a, shortSide2 = c, b) : ( shortSide1 = a, shortSide2 = b, c));
	

	// Check if longest side is less than the two shorter sides summed, if so, it's a legal triangle
	if(longestSide <= shortSide1 + shortSide2)
	{
		double s = (a + b + c) / 2;
		// Apply Heron's formula
		double area = sqrt(s*(s-a)*(s-b)*(s-c));

		printf("Area = %lf\n", area);
	} else { // else we have triangle inequality and print an error
		printf("Error: triangle inequality violated.\n");
	}

	return 0;
}
