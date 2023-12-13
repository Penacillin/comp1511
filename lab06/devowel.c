#include <stdio.h>

int main()
{
	char vowels[] = {'a','e','i','o','u'};
	
	char c = getchar();
	int vowel = 0;
	while(c != EOF)
	{
		vowel = 0;
		int i = 0;
		for( i = 0; i < 5; i++)
		{
			if(c == vowels[i])
				vowel = 1;
		}
		if(!vowel)
			putchar(c);
		
		c = getchar();
	}
	
	return 0;
}