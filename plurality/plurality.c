#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9
#define MAX_NAME_LENGTH 30

// Function prototypes
bool vote(char name[]);
void print_winner(void);



// Candidates have name and vote count
typedef struct
{
    char name[MAX_NAME_LENGTH];
    int votes;

} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;


int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        if (strlen(argv[i + 1]) < MAX_NAME_LENGTH) {
            strcpy(candidates[i].name, argv[i + 1]);
            candidates[i].votes = 0;
        } else {
            printf("Some names are too long.");
            return 3;
        }
        
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%i", &voter_count);


    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char name[MAX_NAME_LENGTH];
        printf("Vote: ");
        scanf("%s", &name);

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
    return 0;
}


// Update vote totals given a new vote
bool vote(char name[])
{
    for (int i = 0; i < candidate_count; i++) {
        if (!strcmp(name, candidates[i].name)) {
            candidates[i].votes++;
            return true;
        }
    }
   
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_vote = -1;
    int winners[MAX];
    int counter = 0;

    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > max_vote) {
            max_vote = candidates[i].votes;
        } 
    } 
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == max_vote) {
            winners[counter] = i;
            counter++;
        }
    }
    for (int i = 0, n = sizeof(winners) / sizeof(winners[0]); i < n; i++) {
        printf("%s\n", candidates[winners[i]].name);
    }

    return;
}
