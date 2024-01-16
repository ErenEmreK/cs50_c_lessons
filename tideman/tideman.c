#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Max number of candidates
#define MAX 9
#define MAX_LENGTH 50

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int margin;
} pair;

// Array of candidates
char candidates[MAX][MAX_LENGTH];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int current_winner = -10;

// Function prototypes
bool vote(int rank, char name[], int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(pair pairs[], int low, int high);
void lock_pairs(void);
void print_winner(void);
bool check_circle(int number);
bool is_winner(int number);

int main(int argc, char* argv[])
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
        //candidates[i][MAX_LENGTH] = argv[i + 1];
        strcpy(candidates[i], argv[i + 1]);
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            //Initialize preferences
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count;
    printf("Number of voters: ");
    scanf("%i", &voter_count);
    // Query for votes
   
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[MAX];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[MAX_LENGTH];
            printf("Rank %i:", j + 1);
            scanf("%s", &name);

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
    sort_pairs(pairs, 0, pair_count - 1);
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, char name[], int ranks[])
{   
    for (int i = 0; i < candidate_count; i++) {
        if (!strcmp(name, candidates[i])) {
            ranks[rank] = i; 
            return true;
        }
    }
    
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; ++i) {
        for (int j = i+1; j < candidate_count; ++j) {
            ++preferences[ranks[i]][ranks[j]];        
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO

    int count = 0;
    int length = sizeof(preferences) / sizeof(preferences[0]);

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (i != j) {
                if (preferences[i][j] > preferences[j][i]) {
                    pairs[count].winner = i;
                    pairs[count].loser = j;
                    pairs[count].margin = preferences[i][j] - preferences[j][i];
                    ++count;
                }
            }
        }
    }
    pair_count =  sizeof(pairs) / sizeof(pairs[0]);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(pair pairs[], int low, int high)
{
    int pivot, value1, value2, temp_margin, temp_winner, temp_loser;

    if (low < high) {
        pivot = low;
        value1 = low;
        value2 = high;

        while (value1 < value2) {
            while (pairs[value1].margin >= pairs[pivot].margin && value1 <= high) {
                value1++;
            }
            while (pairs[value2].margin < pairs[pivot].margin && value2 >= low) {
                value2--;
            }
            if (value1 < value2) {
                temp_margin = pairs[value1].margin;
                pairs[value1].margin = pairs[value2].margin;
                pairs[value2].margin = temp_margin;

                temp_winner = pairs[value1].winner;
                pairs[value1].winner = pairs[value2].winner;
                pairs[value2].winner = temp_winner;

                temp_loser = pairs[value1].loser;
                pairs[value1].loser = pairs[value2].loser;
                pairs[value2].loser = temp_loser;
            }
        }
        temp_margin = pairs[value2].margin;
        pairs[value2].margin = pairs[pivot].margin;
        pairs[pivot].margin = temp_margin;

        temp_winner = pairs[value2].winner;
        pairs[value2].winner = pairs[pivot].winner;
        pairs[pivot].winner = temp_winner;

        temp_loser = pairs[value2].loser;
        pairs[value2].loser = pairs[pivot].loser;
        pairs[pivot].loser = temp_loser;

        sort_pairs(pairs, low, value2 - 1);
        sort_pairs(pairs, value2 + 1, high);
    
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; ++i) {

        int w = pairs[i].winner;
        int l = pairs[i].loser;
        current_winner = w;

        if (!check_circle(l)) {
            locked[w][l] = true;
        }
        
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; ++i) {
        if (is_winner(i)) {
            printf("%s is the winner!", candidates[i]);
        }
    }
    return;
}


bool check_circle(int number) {
    if (number == current_winner) {
        return true;
    }
    for (int i = 0; i < candidate_count; ++i) {
        if (locked[number][i]) {
            check_circle(i);
        }
    } 
    return false;
}



bool is_winner(int number) {
    for (int i = 0; i < candidate_count; ++i) {
        if (locked[i][number]) {
            return false;
        }
    }
    return true;
}