#include <stdio.h>
#include "farnarkle.h"

// read N_TILES tiles into array tiles
// return 1 if successful, 0 otherwise
int read_tiles(int tiles[N_TILES]) {

    for(int i = 0; i < N_TILES; i++)
    {
        int res = scanf("%d", tiles + i);
        if(res != 1 || tiles[i] > MAX_TILE)
            return 0;
    }    
    
    return 1; 
}

// print tiles on a single line
void print_tiles(int tiles[N_TILES]) {
    for(int i = 0; i < N_TILES-1; i++)
    {
        printf("%d ", tiles[i]);
    }
    printf("%d\n", tiles[N_TILES-1]);
}
