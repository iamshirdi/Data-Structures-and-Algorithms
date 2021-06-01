#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size population
    int pop_start, pop_end, years;

    do
    {
        pop_start = get_int("Please enter population starting size greater than 9 \n");
        printf("Entered population size is %i \n", pop_start);
    }
    while (pop_start < 9);

    // Prompt for end size
    do
    {
        pop_end = get_int("Please enter population end size greater than starting \n");
        printf("Entered population size is %i \n", pop_end);
    }
    while (pop_start > pop_end);

    // Calculates number of years until we reach threshold

    for (years = 0; pop_start < pop_end; years++)
    {
        //lammas get rounded by computer already and years incremented after exiting loops
        pop_start = pop_start + pop_start / 3 - pop_start / 4;
    }


    // Print number of years

    printf("Years: %i", years);
}
