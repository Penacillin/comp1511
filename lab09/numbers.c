#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    
    FILE* f = fopen(argv[3], "w+");
   // iterate over variables
    for(int i = start; i <= end; i++)
        fprintf(f, "%d\n", i);
    
    fclose(f);
   
    return 0;
    
}
