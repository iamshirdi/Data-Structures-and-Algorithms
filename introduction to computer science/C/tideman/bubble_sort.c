#include <cs50.h>
#include <stdio.h>

void sort( int numbers[], int c);

int main(void)
{
    int array[] = {10,5,4,5,6,7};


    int n = 7; 
    int swap;
    for (int c = 0 ; c < n - 1; c++)
      {
        for (int d = 0 ; d < n - c - 1; d++)
        {
          if (array[d] > array[d+1]) /* For decreasing order use '<' instead of '>' */
          {
            swap       = array[d];
            array[d]   = array[d+1];
            array[d+1] = swap;
          }
        }
      }
    for (int i = 0; i < 7; i++)
    {
        printf("%i   ", array[i]);    
    }
}
