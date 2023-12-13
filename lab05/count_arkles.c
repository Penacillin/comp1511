#include <stdio.h>
#include "farnarkle.h"

// return number of arkles
int count_arkles(int sequence1[N_TILES], int sequence2[N_TILES]) {

		// array to hold count of each number
        int counter[MAX_TILE+2] = {0};
        
        // tally up how many of each number
        for(int i = 0; i < N_TILES; i++)
        {
            if(sequence1[i] != sequence2[i])
            {
                counter[sequence1[i]]++;
            }
        }
        int arkles = 0;
        
        // count the arkles
        for(int i = 0; i < N_TILES ; i++)
        {
            if(counter[sequence2[i]] > 0 && sequence1[i] != sequence2[i])
            {
                arkles++;
                counter[sequence2[i]]--;
            }
        }
        
        return arkles; 
}

