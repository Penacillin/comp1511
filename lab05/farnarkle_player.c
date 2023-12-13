#include <stdio.h>
#include <math.h>
#include "farnarkle.h"

// an automated farnarkle_player
// given all previous guesses and their farnarkles and arkle counts
// make a new guess
//
// inputs:
// turn - which turn this is
// previous_guesses contains the turn - 1 previous_guesses
// farnarkles[i] contains the number of farnarkles for previous_guess[i]
// arkles[i] contains the number of arkles for previous_guess[i]
//
// output:
// guess - the next guess

int poss[99999999][N_TILES];

void populate_poss()
{
    
}
// convert a multi digit integer to array (split each digit into an element of array)
void intToArray(int arr[N_TILES], int num)
{
	for (int i = 0; i < N_TILES ; i++)
	{
		arr[i] = (int)((int)num / pow(10, N_TILES - 1 -i)) % (10);
	}
}
// check if two arrays are the same
int equalArrays(int arr1[N_TILES], int arr2[N_TILES])
{
	for (int i = 0; i < N_TILES; i++)
	{
		if (arr1[i] != arr2[i])
			return 0;
	}
	return 1;
}

// Find next permutation of possible guess sequence
int nextPerm(int currentPerm)
{
	currentPerm++;

	for (int i = 0; i < N_TILES; i++)
	{
		if ((int)((int)currentPerm / pow(10, N_TILES - 1 - i)) % (10) == 0)
		{
			currentPerm += pow(10, N_TILES - 1 - i);
		}
	}
	return currentPerm;
}

int lowestGuess = 0;
int initialized = 0;

void farnarkle_player(int turn, int previous_guesses[MAX_TURNS][N_TILES], int farnarkles[MAX_TURNS], int arkles[MAX_TURNS], int guess[N_TILES]) {

	if (!initialized)
	{
		for (int i = 0; i < N_TILES; i++)
		{
			lowestGuess = lowestGuess * 10 + 1;
		}
		//lowestGuess += 11;
		initialized = 1;
	}

    // if its just the first turn, print first N numbers
    if(turn == 1)
    {
        for(int i = 0; i < N_TILES; i++)
        {
            guess[i] = i+1;
        }
    }
    
    // permutate	
	int foundGuess = 1;	
	for (int i = lowestGuess; i <= lowestGuess * MAX_TILE; i = nextPerm(i))
	{
		intToArray(guess, i);
		foundGuess = 1;
		// For each permutation, check if its equivalent to all previous guess
		for (int j = 0; j < turn - 1 ; j++)
		{

			if (equalArrays(guess, previous_guesses[j])
				|| count_arkles(guess, previous_guesses[j]) != arkles[j]
				|| count_farnarkles(guess, previous_guesses[j]) != farnarkles[j])
			{
				// if either arkles or farnakles are off, or it's the same guess, set as bad guess
				foundGuess = 0;
				// end loop
				j = 200;
			}
		}
		// If you get through the loop checking tentative to all previous guesses, and if it's still found, use the guess
	
		if (foundGuess)
		{
			return;
		}
	}
    

}

