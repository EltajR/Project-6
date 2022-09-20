#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct candidate{
    char *name;
    int index;
    int vote_count;
    int eliminated;
}candidate;

#define MAX_CANDIDATES 9
#define MAX_VOTERS 9


char *read_str(void);
int read_int(void);
int is_valid_vote(candidate [], int ,char *);





int main(){
    int candidate_counter = 0;

    printf("%s","Candidates are:");
    char *candidate_names  = read_str();

    candidate candidates[MAX_CANDIDATES];
    char *name = strtok(candidate_names, " ");
    while(name != NULL){
        candidate c;
        c.name = name;
        c.index = candidate_counter;
        c.vote_count = 0;
        c.eliminated = 0;
        candidates[candidate_counter] = c;
        candidate_counter++;
        name = strtok(NULL, " ");
    }


    int num_of_voters;
    do {
        printf("%s", "The number of the voters is:");
        num_of_voters = read_int();
    } while (num_of_voters == -1);
        int preferences [num_of_voters][candidate_counter];
        for (int i = 0; i < num_of_voters; ++i) {
            for (int j = 0; j < candidate_counter; ++j) {
                printf("%s %i:", "Rank", j + 1);
                char *vote_by_user = read_str();
               int index_of_candidate =
                       is_valid_vote(candidates, candidate_counter, vote_by_user);
               if(index_of_candidate != -1) {
                   preferences [i][j] = index_of_candidate;
               }
               else {
                   printf("%s\n", "Invalid vote");
                   break;
               }
            }
            printf("\n");
        }
       // At this point all the necessary data has been collected from the user
       // It is now time to find the winner


       // To be implemented -->
        int majority_vote_count = num_of_voters / 2 + 1;

        // Add votes for the first round
        for (int i = 0; i < num_of_voters; ++i) {
        int candidate_index = preferences[i][0];
        candidates[candidate_index].vote_count++;
    }

   // Does anyone have majority?

    for (int i = 0; i < candidate_counter; ++i) {
        candidate c = candidates[i];
        if(c.vote_count == majority_vote_count) printf("%s won!", c.name);
    }

    // <--
}


char *read_str(){
    char *candidate_names = malloc(256 * sizeof(char));
    scanf(" %[^\n]", candidate_names);
    return candidate_names;
}

int read_int(){
    int numOfVoters = -1;
    scanf(" %i", &numOfVoters);
    return ((numOfVoters > 0) && (numOfVoters <= MAX_VOTERS)) ? numOfVoters : -1;
}

int is_valid_vote(candidate candidates[], int arr_length, char *user_input){
    for (int i = 0; i < arr_length; ++i) {
       candidate c = candidates[i];
       if(strcmp(c.name, user_input) == 0) return c.index;
    }
    return -1;
}