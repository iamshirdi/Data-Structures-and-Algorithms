#include <stdio.h>
#include <cs50.h>


void pyramid(int size);

// takes input and prints pyramid
int main(void)
{
    int p_height;

    // Define pyramid height
    do
    {
        p_height = get_int("please enter height of pyramid between 1 to 9 \n");
    }
    while (p_height > 8 || p_height < 1);

    // print # according to height defined by user
    pyramid(p_height);
}


// used to print slash according to number defined in argument
void print_slash(int number)
{
    for (int height = 0; height < number + 1 ; height++)
    {
        printf("#");
    }
}

// used to print space according to arguments
void print_space(int number)
{
    for (int height = number; height > 0 ; height--)
    {
        printf(" ");
    }


}

// pyramid  is printed with slash and # as input
void pyramid(int size)
{
    for (int n = 0; n < size; n++)
    {
        int space_size = size - n - 1;
        print_space(space_size);
        print_slash(n);
        printf("  ");
        print_slash(n);
        printf("\n");
    }
}

