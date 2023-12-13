#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
// Returns 1 for simple character, 2 for capital character, 
//-1 for non character
int charType(char c);
int substitute(char* string, char *key);
void produceKey(char* key, int sample[], int encrypted[], double probabilities[26][26]);

// letter frequency functions
char toLower(char c);
int letterFrequency(int[], char*);
void printLetterFrequency(int[], int);

void readFile(FILE* file, char* buffer);
int frequencyRanking(int array[26], int size, int ranking[26]);
void insert(int array[], int size, int pos, int value);

void printFile(char*);
void probabilityPrinter(double probs[26][26]);

void apoProb(char*, char*, double[26][26]);

void calcProb(char*, char*, double[26][26], void (*f) (char*, int[]));

void getKeyFromProb(char* key, double[26][26]);

int main(int argc, char* argv[])
{
	double probabilities[26][26];
	int i = 0;
	int j = 0;
	for(; i < 26; i++)
	{
		for(j = 0; j < 26; j++)
		{
			probabilities[i][j] = 0;
		}
	}
	
	
	// get letter frequency of sample text
	
	// Create array to store counts, as well as file
	int sampleFrequency[26] = {0};
	char sampleFile[100000] = {0};
	// open and read sample text file
	FILE* file = fopen(argv[1], "r");
	if(file == NULL)
	{
		fprintf(stderr, "INVALID FILE\n");
		exit(1);
	}
	readFile(file, sampleFile);
	
	// get the letter frequency of sample text
	int totalSampleChars = letterFrequency(sampleFrequency, sampleFile);
	
	// get letter frequency of encrypted text
	int encryptedFrequency[26] = {0};
	char encryptedFile[100000] = {0};
	readFile(stdin, encryptedFile);
	int totalEncryptedChars = letterFrequency(encryptedFrequency, encryptedFile);
	
	// add probability for frequency ranking
	char key[26] = {0};						// Create string to store key
	produceKey(key, sampleFrequency, encryptedFrequency, probabilities);	

	probabilityPrinter(probabilities);
	
	// add 1 probability for matching character before and after apostrophe ("'")	
	apoProb(sampleFile, encryptedFile, probabilities);
	
	probabilityPrinter(probabilities);
	
	// substitute based on key	
	substitute(encryptedFile, key);
	
	// profit ^.^
	printFile(encryptedFile);
	
	return 0;
}

void getKeyFromProb(char* key, double probs[26][26])
{
	
}

void calcProb(char* sam, char* enc, double probs[26][26], void (*f) (char*, int[]))
{
	int fbaSam[26] = {0};
	int fbaEnc[26] = {0};
	(*f)(sam, fbaSam);
	(*f)(enc, fbaEnc);
	int fbaSamRanking[26] = {0};
	int fbaEncRanking[26] = {0};

	frequencyRanking(fbaSam, 26, fbaSamRanking);
	frequencyRanking(fbaEnc, 26, fbaEncRanking);
	
	int i = 0;
	for(; i < 26 && enc[fbaEncRanking[i]] != 0; i++)
	{
		double relativeDifferenceSample = (double)(sam[fbaSamRanking[i]] - sam[fbaSamRanking[i+1]]) / (sam[fbaSamRanking[i+1]] != 0 ? sam[fbaSamRanking[i+1]] : 1 );
		double relativeDifferenceEnc = (double) (enc[fbaEncRanking[i]] - enc[fbaEncRanking[i+1]]) / (enc[fbaEncRanking[i+1]] != 0 ? enc[fbaEncRanking[i+1]] : 1);
		printf("relative differences for %c: %lf %lf\n", fbaEncRanking[i] + 'a', relativeDifferenceSample, relativeDifferenceEnc);
		probs[fbaEncRanking[i]][fbaSamRanking[i]] += 1 - fabs(relativeDifferenceEnc - relativeDifferenceSample);		
	}
}

void freqBeforeApo(char* string, int counts[26])
{
	int i  =0;
	char c = string[0];
	int totalChars = 0;
	while(c != EOF && c != 0)
	{	
		// if c is alphabetical and next char is a apo
		if(charType(c) != -1 && string[i+1] == '\'')
		{
			c = toLower(c);				// convert char to lower
			counts[c-'a']++;			// add to counter of that char	
			totalChars++;
		}
		
		c = string[++i];
	}	
}

void apoProb(char* sample, char* enc, double probs[26][26])
{
	int fbaSam[26] = {0};
	int fbaEnc[26] = {0};
	freqBeforeApo(sample, fbaSam);
	freqBeforeApo(enc, fbaEnc);
	int fbaSamRanking[26] = {0};
	int fbaEncRanking[26] = {0};

	frequencyRanking(fbaSam, 26, fbaSamRanking);
	frequencyRanking(fbaEnc, 26, fbaEncRanking);
	
	int i = 0;
	for(; i < 26; i++)
	{
		double relativeDifferenceSample = (double)(sample[fbaSamRanking[i]] - sample[fbaSamRanking[i+1]]) / (sample[fbaSamRanking[i+1]] != 0 ? sample[fbaSamRanking[i+1]] : 1 );
		double relativeDifferenceEnc = (double) (enc[fbaEncRanking[i]] - enc[fbaEncRanking[i+1]]) / (enc[fbaEncRanking[i+1]] != 0 ? enc[fbaEncRanking[i+1]] : 1);
		printf("relative differences for %c: %lf %lf\n", fbaEncRanking[i] + 'a', relativeDifferenceSample, relativeDifferenceEnc);
		probs[fbaEncRanking[i]][fbaSamRanking[i]] += 1 - fabs(relativeDifferenceEnc - relativeDifferenceSample);		
	}
		
}

void produceKey(char* key, int sample[26], int encrypted[26], double probabilities[26][26])
{
	int sampleRanking[26] = {0};
	int encryptedRanking[26] = {0};
	
	frequencyRanking(sample, 26, sampleRanking);
	frequencyRanking(encrypted, 26, encryptedRanking);
	
	printLetterFrequency(sample, 1);
	printLetterFrequency(encrypted, 1);
	
	int i = 0;
	for(; i < 26; i++)
	{
		key[encryptedRanking[i]] = sampleRanking[i];
		double relativeDifferenceSample = (double)(sample[sampleRanking[i]] - sample[sampleRanking[i+1]]) / (sample[sampleRanking[i+1]] != 0 ? sample[sampleRanking[i+1]] : 1 );
		double relativeDifferenceEnc = (double) (encrypted[encryptedRanking[i]] - encrypted[encryptedRanking[i+1]]) / (encrypted[encryptedRanking[i+1]] != 0 ? encrypted[encryptedRanking[i+1]] : 1);
		printf("relative differences for %c: %lf %lf\n", encryptedRanking[i] + 'a', relativeDifferenceSample, relativeDifferenceEnc);
		probabilities[encryptedRanking[i]][sampleRanking[i]] += 1 - fabs(relativeDifferenceEnc - relativeDifferenceSample);
		
	}
	printf("KEY: ");
	for(i = 0; i < 26; i++)
	{
		printf(" %c, " , key[i] + 'a');
	}
	printf("\n");
	
}

int frequencyRanking(int array[26], int size, int ranking[26])
{
	int i = 0;
	for(; i < size; i++)
	{
		int j = 0;
		while(j < i && array[i] < array[ranking[j]])
		{
			j++;
		}
		insert(ranking, 26, j, i);
	}
	
	return 0;
}

void insert(int array[], int size, int pos, int value)
{
	int i = size - 1;
	for(; i > pos; i--)
	{
		array[i] = array[i-1];
	}
	array[i] = value;
	
}


int substitute(char* string, char *key)
{
	int i = 0;
	char c = string[0];
	while(c != EOF && c != '\0')
	{
		if(charType(c) == 1)
		{
			c = key[c -'a'] + 'a';
		}
		else if(charType(c) == 2)
		{
			c = key[c - 'A'] + ('A' - 'a') + 'a';
		}
		
		string[i] = c;
		c = string[++i];
	}
	
	return 0;
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
	buffer[i+1] = '\0';
}

char toLower(char c)
{
	if(c >= 'A' && c <= 'Z')
	{
		return c - ('A' - 'a');
	}
	return c;
}

void probabilityPrinter(double probs[26][26])
{
	int i = 0;
	int j = 0;
	
	for(; i < 26; i++)
	{
		printf("%c ", i + 'a');
		for(j = 0; j < 26;j++)
		{
			printf("%0.4lf " , probs[i][j]);
		}
		printf("\n");
	}
}
