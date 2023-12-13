#include <stdio.h>
char toLower(char c)
{
	if(c >= 'A' && c <= 'Z')
	{
		return c - ('A' - 'a');
	}
	return c;
}
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

int main(int argc, char *argv[])
{
	char c = getchar();
	int i = 0;
	while(c != EOF)
	{
		if(charType(c) == 1)
		{
			for(i = 0; i < 26 && argv[1][i] != c; i++)
			{		
			}
			c = i + 'a';
		}
		else if(charType(c) == 2)
		{
			c -= 'A' - 'a';
			for(i = 0; i < 26 && argv[1][i] != c; i++)
			{		
			}
			c = i + 'A';
		}
		putchar(c);
		c = getchar();
	}
	
	return 0;
}