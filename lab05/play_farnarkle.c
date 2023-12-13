#include <stdio.h>
#include "farnarkle.h"

int main(void) {
    int hidden_sequence[N_TILES];    
    int guess[N_TILES];
    int turn = 1;
    create_random_tiles(hidden_sequence);
    
    //print_tiles(hidden_sequence);
    int farnarkles = 0;
    
    while(farnarkles != N_TILES)
    {
        printf("Enter guess for turn %d: ", turn++);
        read_tiles(guess);
        farnarkles = count_farnarkles(hidden_sequence, guess);
        printf("%d farnarkles ", farnarkles);
        printf("%d arkles\n", count_arkles(hidden_sequence, guess));
    }
    
    printf("You win\n");
    
    return 0;
    // put your code here
}

