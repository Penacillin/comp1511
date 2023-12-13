#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Returns 1 for simple character, 2 for capital character, 
//-1 for non character
int charType(char);
int posMod(int, int);

//caesar shift characters by shift in char*
int shift(int, char*);
char shiftChar(char, int);

// letter frequency functions
char toLower(char);
int letterFrequency(int[], char*);
void printLetterFrequency(int[], int);

void readFile(FILE* file, char* buffer);
int maxOfArray(int[], int size, int*);

void printFile(char*);


int main(int argc, char* argv[])
{
	// get letter frequency of sample text
	// Create array to store counts, as well as file
	int sampleFrequency[26] = {0};
	char sampleFile[100000];
	// open and read sample text file
	FILE* file = fopen(argv[1], "r");
	if(file == NULL)
	{
		printf("INVALID FILE\n");
		exit(1);
	}
	readFile(file, sampleFile);
	// get the letter frequency
	int totalSampleChars = letterFrequency(sampleFrequency, sampleFile);
	//printLetterFrequency(sampleFrequency, totalSampleChars);
	
	// get letter frequency of encrypted text
	int encryptedFrequency[26] = {0};
	char encryptedFile[100000];
	readFile(stdin, encryptedFile);
	int totalEncryptedChars = letterFrequency(encryptedFrequency, encryptedFile);
	//printLetterFrequency(encryptedFrequency, totalEncryptedChars);
	
	// Calculate shift
	int sampleMaxPos = 0;
	int maxCountSample = maxOfArray(sampleFrequency, 26, &sampleMaxPos);
	int encryptedMaxPos = 0;
	int maxCountEncrypyed = maxOfArray(encryptedFrequency, 26, &encryptedMaxPos);
	
	int offset = (sampleMaxPos - encryptedMaxPos);
	
	//printf("shift: %d\n", offset);
	// shift encrypted text
	shift(offset, encryptedFile);
	
	// profit
	printFile(encryptedFile);
	
	return 0;
}

int maxOfArray(int array[26], int size, int* maxPos)
{
	int i = 0;
	int largest = 0;
	for(; i < size; i++)
	{
		if(array[i] > largest)
		{
			largest = array[i];
			*maxPos = i;
		}
	}
	
	return largest;
}

void readFile(FILE* file, char* buffer)
{
	char c = fgetc(file);
	int i = 0;
	while(c != EOF)
	{
		buffer[i] = c;
		c = fgetc(file);
		i++;
	}
	buffer[i] = '\0';
}

int letterFrequency(int counters[26], char* string)
{
	int i  =0;
	char c = string[0];
	int totalChars = 0;
	while(c != EOF && c != 0)
	{
	
		// if c is alphabetical
		if(charType(c) != -1)
		{
			c = toLower(c);				// convert char to lower
			counters[c-'a']++;			// add to counter of that char	
			totalChars++;
		}
		
		c = string[++i];
	}	
	
	return totalChars;
	
}

char toLower(char c)
{
	if(c >= 'A' && c <= 'Z')
	{
		return c - ('A' - 'a');
	}
	return c;
}


int shift(int offset, char *arg)
{
	int i = 0;
	char c = arg[0];
	while(c != EOF && c != '\0')
	{
		
		c = shiftChar(c, offset);	
		arg[i] = c;
		
		c = arg[++i];
	}
	
	return 0;
}

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

void printLetterFrequency(int counter[26], int totalChars)
{
	int i = 0;
	for(; i < 26; i++)
	{
		printf("'%c' %lf %d\n", i + 'a',
		(double)counter[i]/totalChars, counter[i]);
	}		
	
}

void printFile(char* buffer)
{
	int i = 0;
	char c = buffer[i];
	while(c != '\0' && c != EOF)
	{
		putchar(c);
		c = buffer[++i];
	}
}