#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int lo, int hi)
{
    int p = arr[(lo+hi)/2];

    int i = lo - 1;
    int j = hi + 1;

    while(1)
    {
        do {
            i++;
        } while(arr[i] < p);

        do {
            j--;
        } while(arr[j] > p);

        // if finished swapping
        if (i >= j)
        {
            printf("p = %d, j = %d\n", p, j);
            for(int i = 0; i < 11; i++)
            {
                printf("%d ", arr[i]);
            }
            printf("\n");
            return j;
        }

        // Swap elements
        int t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}

void quicksort(int arr[], int lo, int hi)
{
    if (lo < hi)
    {
        int p = partition(arr, lo, hi);
        quicksort(arr, lo, p);
        quicksort(arr, p + 1, hi);

    }
}


int main()
{
    int a[] = {5,8,3,5,1,9,7,5,7,4,9,2};
    quicksort(a, 0, 11);

    for(int i = 0; i < 11; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
