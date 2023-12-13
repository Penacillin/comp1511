#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int desired_lines = 10;
    if(argc != 2)
    {     
        printf("Incorrect arguments, usage: <program> filename\n");
        exit(1);
    }
    
    FILE* f;
    f = fopen(argv[1], "r");
        
    if(!f)
    {
        printf("File could not be opened, exiting\n");
        exit(1);        
    }
    
    char lastTen[10][1025];
    int line = 0;
    int lines = 0;
    int pos = 0;
    
    char c = fgetc(f);
    for(int i = 0; i < desired_lines && c != EOF; c = fgetc(f))
    {
        if(c == '\n')
        {
            lastTen[line][pos] = c;    
            lastTen[line++][pos+1] = '\0';   
            pos = 0;
            lines++;
            if(line == 10)
            {
                line = 0;
            }
        }
        else
            lastTen[line][pos++] = c;
    }    
    fclose(f);
    int start = 0;
    if(lines < 10)
        start = 0;
    else
        start = lines;
        
    for(int i = 0; i < 10 && i < lines; i++)
    {
       
        printf("%s", lastTen[start++ % 10]);
    }
    
    return 0;
    
}
