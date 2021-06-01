#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
char lower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
void compute(string word, string cipherkey);
int check(string key);

int main(int argc, string argv[])
{
    // checks if argument present and whether its only 1
    if (argc != 2)
    {
        printf("only 1 argument or no argument present");
        return 1;
    }


    // checks cypher is valid or not
    string cipherkey = argv[1];
    int ret = check(cipherkey);

    if (ret == 1)
    {
        printf("error invalid cypher key");
        return 1;
    }

    // takes user plain text
    string word1 = get_string("plaintext: ");


    // encrypts text with key provided in argument
    printf("ciphertext: ");
    compute(word1, cipherkey);
    printf("\n");

}


int check(string key)
{
    int len = strlen(key);
    if (len != 26)
    {
        printf("error must contain 26 character cypher key");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        char low = tolower(key[i]);
        if (low < 97 || low > 122)
        {
            return 1;
        }
        else if (key[i] == key[i + 1])
        {
            return 1;
        }
    
    }
    return 0;
}





int get_index(char c)
{
    int counter = 0;
    //lower check converts letters
    if (c > 97 && c < 122)
    {
        for (int i = 0; lower[i] != c; i++)
        {
            counter++;
        }
    }

    // upper compares
    else
    {
        char cr = tolower(c);
        for (int j = 0; lower[j] != cr; j++)
        {
            counter++;
        }
    }
    return counter;
}



void compute(string word, string cipherkey)
{
    for (int n = 0; word[n] != '\0'; n++)
    {
        char car = word[n];
        // lowerrrcase
        if (car > 96 && car < 123)
        {
            int index = get_index(car);
            printf("%c", tolower(cipherkey[index]));
        }

        //upper case
        else if (car > 64 && car < 91)
        {
            int index = get_index(car);
            printf("%c", toupper(cipherkey[index]));
        }

        //prints directly without conversion
        else
        {
            printf("%c", car);
        }
    }
}