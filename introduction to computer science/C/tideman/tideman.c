#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");
    
    // initialize preferences to zero based on number of candidates
    

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // name match with candidates[candidate_count]
    // array passed by reference directly
    for (int i=0; i< candidate_count; i++)
    {
        if (strcmp(candidates[i], name ) == 0)
        {
            // i is index of candidate stored according to rank,j preference 
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // int preferences[MAX][MAX];
    // 1st voter
    for (int j = 0; j < candidate_count; j++)
    {
        if (j == ranks[0])
        {
            preferences[ranks[0]][j] += 0;
            //rnks [0] will give index of candidate directly
        }
        else
        {
            preferences[ranks[0]][j] += 1;
        }
    }
    //2nd voter shouldnt preceed itself or first voter
    for (int j = 0; j < candidate_count; j++)
    {
        if (j == ranks[1] || j == ranks[0])
        {
            preferences[ranks[1]][j] += 0;
        }
        else
        {
            preferences[ranks[1]][j] += 1;
        }
    }
    
    
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO pair pairs[MAX * (MAX - 1) / 2];
    for(int c = 0; c < candidate_count; c++ )
    {
        for(int p = c+1; p < candidate_count; p++)
        {
            printf("%i %i paircount is %i\n",preferences[c][p],preferences[p][c],pair_count);
            if (preferences[c][p] > preferences[p][c])
            {   
                printf("yes");
                pairs[pair_count].winner = c; 
                pairs[pair_count].loser = p;
                pair_count+=1;
            }
            else if ((preferences[c][p] < preferences[p][c]))
            {
                printf("no");
                pairs[pair_count].winner = p; 
                pairs[pair_count].loser = c;
                pair_count+=1;                    
            }
        }
    }
    
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = pair_count - 1; i >= 0 ; i--)
    {
        for (int j = 0; j <= i - 1; j++)
        {
            if ((preferences[pairs[j].winner][pairs[j].loser]) < (preferences[pairs[j + 1].winner][pairs[j + 1].loser]))
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
return;
}

// Test for cycle by checking arrow coming into each candidate
bool cycle(int end, int cycle_start)
{
    // Return true if there is a cycle created (Recursion base case)
    if (end == cycle_start)
    {
        return true;
    }
    // Loop through candidates (Recursive case)
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (cycle(i, cycle_start))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loop through pairs
    for (int i = 0; i < pair_count; i++)
    {
        // If cycle function returns false, lock the pair
        if (!cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election FALSE ALL COLUMNS
void print_winner(void)
{
    // Winner is the candidate with no arrows pointing to them
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}

