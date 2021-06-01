#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};


int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else  if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int sum = 0;
    // loops through string array for each character
    for (int i = 0; word[i] != '\0'; i++)
    {
        char c = word[i];
        char cr = tolower(c);

        int t = (int) cr;
        printf("%i", t);
        if (t < 97 || t > 122)
        {
            printf("skipping\n");
            continue;
        }

        printf("%c", c);
        int index = 0;
        //gets index of letters to keep in points
        for (int j = 0; letters[j] != cr; j++)
        {
            index++;
            // printf("%c and %c is ",cr,letters[j]);

        }
        printf("POINTS  are %i\n", POINTS[index]);
        sum += POINTS[index];
    }
    printf("sum is %i\n", sum);
    return sum;

}
