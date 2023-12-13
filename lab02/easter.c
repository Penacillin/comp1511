#include <stdio.h>

int main()
{
	int year = 0;
	
	printf("Enter Year:  ");
	scanf("%d", &year);

	int a, b, c, d, e, f, g, h, i, k, l, m, eM, p, eD;

	a=year%19;
	b=year/100;
	c=year%100;
	d=b/4;
	e=b%4;
	f=(b+8)/25;
	g=(b-f+1)/3;
	h=(19*a+b-d-g+15)%30;
	i=c/4;
	k=c%4;
	l=(32+2*e+2*i-h-k)%7;
	m=(a+11*h+22*l)/451;
	eM =(h+l-7*m+114)/31;//  [3=March, 4=April]
	p=(h+l-7*m+114)%31;
	eD =p+1;

	char* month = "";

	switch(eM)
	{
	case 3:
		month = "March";
		break;
	case 4:
		month = "April";
		break;
	default:
		printf("OH NO WHAT HAPPENED AYE LMAO ROFL????\n\n");
		return 0;
	
	}	

	printf("Easter is %s %d in %d.\n", month, eD, year);
}
