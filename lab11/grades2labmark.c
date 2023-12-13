#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double grades2labmark(char grades[])
{
    int len = strlen(grades);
    double score = 0;
    for(int i = 0; i < len; i++)
    {
        if(grades[i] == '.')
        {
            score += 0;
        }
        else if(grades[i] == 'C')
        {
            score += 0.5;
        }
        else if(grades[i] == 'B')
        {
            score += 0.8;
        }
        else if(grades[i] == 'A')
        {
            if(grades[i+1] == '+')
            {
                score += 1.2;
                i++;
            }
            else
                score += 1.0;
        }
    }
    
    return score > 10 ? 10 : score;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Incorrent arguments\n");
        exit(1);
    }
    
    double score = grades2labmark(argv[1]);
    printf("%.1lf\n", score );
    
    return 0;    
}
