#include <stdio.h>
#include "farnarkle.h"

void copyArray(int array1[N_TILES], int array2[N_TILES])
{
	for (int i = 0; i < N_TILES; i++)
	{
		array1[i] = array2[i];
	}
}

int main(void) {
	int hidden_sequence[N_TILES];
    int guess[N_TILES];
    int turn = 1;
   create_random_tiles(hidden_sequence);
	
    int previous_guesses[MAX_TURNS][N_TILES];
    int farnarkles[MAX_TURNS];
    int arkles[MAX_TURNS];
    
    printf("Hidden guess is: "); print_tiles(hidden_sequence);
    int successes = 0;
	int halfSuccess = 0;
    while(successes!= N_TILES && turn <= MAX_TURNS)
    {
        // Make a guess
        farnarkle_player(turn, previous_guesses, farnarkles, arkles, guess);
		// Put guess into list of guesses
		copyArray(previous_guesses[turn - 1], guess);
        // Print player's guess
        printf("Player guess for turn %d: ", turn); print_tiles(guess);
        
        // count farnarkles and arkles then store them into lists
        successes = count_farnarkles(hidden_sequence, guess);
		farnarkles[turn - 1] = successes;
		halfSuccess = count_arkles(hidden_sequence, guess);
		arkles[turn - 1] = halfSuccess;

        // Print farnarkles and arkles
        printf("%d farnarkles ", successes);
        printf("%d arkles\n", halfSuccess);

		turn++;
    }
    
    printf("Player won with %d turns\n", turn);
	scanf("%d", &turn);
    return 0;
}

