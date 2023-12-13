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

int main()
{
	char c = getchar();
	int charCounter[26] = {0};
	int totalChars = 0;
	while(c != EOF)
	{
	
		// if c is alphabetical
		if(charType(c) != -1)
		{
			c = toLower(c);					// convert char to lower
			charCounter[c-'a']++;			// add to counter of that char	
			totalChars++;
		}
		
		c = getchar();
	}
	int i = 0;
	for(; i < 26; i++)
	{
		printf("'%c' %lf %d\n", i + 'a',
		(double)charCounter[i]/totalChars, charCounter[i]);
	}		
	
	return 0;
}