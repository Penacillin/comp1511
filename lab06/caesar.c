#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Returns 1 for simple character, 2 for capital character, 
//-1 for non character
int charType(char c)
{
	if(c >= 'a' && c <= 'z')
		return 1;
	
	if(c >= 'A' && c <= 'Z')
		return 2;
	
	return -1;
}

int posMod(int a, int mod)
{
	while(a < 0)
	{
		a += mod;
	}
	return a % mod;
}
char shiftChar(char c, int shift)
{
	shift %= 26;
	if(charType(c) == -1)
	{
		return c;
	}
	if(charType(c) == 1)
	{
		c -= 'a';
		c += shift;
		c = posMod(c,26);
		c += 'a';
		return c;
	}
	if(charType(c) == 2)
	{
		c -= 'A';
		c += shift;
		c = posMod(c,26);
		c += 'A';
		return c;
	}
	
	return -2;
}

int main(int argc, char *argv[])
{
	int shift = atoi(argv[1]);
	
	char c = getchar();
	while(c != EOF)
	{
		
		c = shiftChar(c, shift);	
		putchar(c);
		
		c = getchar();
	}
	
	return 0;
}