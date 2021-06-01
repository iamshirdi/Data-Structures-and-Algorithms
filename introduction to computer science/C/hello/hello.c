#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // greet the user
    // main function returns 0 after succesful execution and since no arguments maybe void or some other reason
    string name = get_string("whats your name\n");
    printf("hello, %s \n", name);
}