#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int desired_lines = 10;
    if(argc != 2 && argc != 4)
    {     
        printf("Incorrect arguments, usage: <program> filename\n");
        exit(1);
    }
    
    
    if(argc == 4 && !strcmp(argv[1], "-n"))
    {
        desired_lines = atoi(argv[2]);
    }
    
    
    FILE* f;
    if(argc == 4)
        f = fopen(argv[3], "r");
    else
        f = fopen(argv[1], "r");
        
    if(!f)
    {
        printf("File could not be opened, exiting\n");
        exit(1);        
    }
    
    char c = fgetc(f);
    for(int i = 0; i < desired_lines && c != EOF; c = fgetc(f))
    {
        if(c == '\n')
            i++;
        fputc(c, stdout); 
    }
    
    fclose(f);
    return 0;
    
}
