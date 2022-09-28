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
#define true 1
#define false 0


char *read_str(void);
int read_int(void);
int is_valid_vote(candidate *, int ,char *);
int initialize_candidates(candidate *candidates , char *candidate_names);
int has_majority(candidate *candidates, int len_c_array, int majority);
int find_min(candidate *candidates, int len_c_array);
int is_tie(candidate *candidates, int len_c_array, int min);
int is_eliminated(candidate c);
void set_votes_to_default(candidate *candidates, int arr_len);
void print_winners(candidate *candidates, int arr_len);
void count_votes(candidate *candidates, int arr_len, int num_of_voters, int preferences[num_of_voters][arr_len]);
void eliminate_c_with_min_votes(candidate *candidates, int len_c_array, int min);


int main(){
    // Read candidate names from the console
    printf("%s","Candidates are:");
    char *candidate_names  = read_str();

    // Initialize candidates array with the date given by the user
    candidate *candidates = malloc(MAX_CANDIDATES * (sizeof(candidate)));
    int len_c_array = initialize_candidates(candidates, candidate_names);

    // How many voters are there?
    int num_of_voters;
    do {
        printf("%s", "The number of the voters is:");
        num_of_voters = read_int();
    } while (num_of_voters == -1);


    // Save preferences of the voters
    int preferences [num_of_voters][len_c_array];
    for (int i = 0; i < num_of_voters; ++i) {
        for (int j = 0; j < len_c_array; ++j) {
            printf("%s %i:", "Rank", j + 1);
            char *vote_by_user = read_str();
            int index_of_candidate =
                       is_valid_vote(candidates, len_c_array, vote_by_user);
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




       // ------------------------------------------------------
        int majority = num_of_voters / 2 + 1;

        int index = -1;
        do{
        // First count votes
        count_votes(candidates, len_c_array, num_of_voters, preferences);

        int min = find_min(candidates, len_c_array);
        // Check if it is a tie. If yes, break
        if(is_tie(candidates, len_c_array, min) == true) break;
        // If it is not a tie, eliminate the candidate(s) with the minimum votes
        else eliminate_c_with_min_votes(candidates, len_c_array, min);

        index = has_majority(candidates, len_c_array, majority);
        set_votes_to_default(candidates, len_c_array);
        } while (index == -1);

        if(index != -1) printf("%s", candidates[index].name);
        else print_winners(candidates, len_c_array);
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

// If the name entered by the user is a valid candidate, return the index of the candidate in the array.
// Otherwise, return -1 to indicate that, the vote is invalid
int is_valid_vote(candidate *candidates, int arr_length, char *user_input){
    for (int i = 0; i < arr_length; ++i) {
       candidate c = candidates[i];
       if(strcmp(c.name, user_input) == 0) return c.index;
    }
    return -1;
}

// returns the length of the array created;
int initialize_candidates(candidate *candidates, char *candidate_names){
    int len_c_array = 0;
    char *name = strtok(candidate_names, " ");
    while(name != NULL){
        candidate c;
        c.name = name;
        c.index = len_c_array;
        c.vote_count = 0;
        c.eliminated = 0;
        candidates[len_c_array] = c;
        len_c_array++;
        name = strtok(NULL, " ");
    }
    return len_c_array;
}

// returns -1, if no one has the majority in the voting. Otherwise, returns the index of the candidate
// with the majority of votes
int has_majority(candidate *candidates, int len_c_array, int majority){
    for (int i = 0; i < len_c_array; ++i) {
        candidate c = candidates[i];
        if(is_eliminated(c) == false){
        if(c.vote_count >= majority) return c.index;
        }
    }
    return -1;
}

// finding minimum number of votes obtained
int find_min(candidate *candidates, int len_c_array){

    int counter = 0;
    while (is_eliminated(candidates[counter]) == true) counter++;
    int min  = candidates[counter].vote_count;
    for (int i = counter + 1; i < len_c_array; ++i) {
        candidate c = candidates[i];
        if(is_eliminated(c) == false) {
            if (c.vote_count < min) min = c.vote_count;
        }
    }
    return min;
}

// does everybody have the same number of votes in the election?
// returns a boolean value of 0(false) or 1(true)
int is_tie(candidate *candidates, int len_c_array, int min){
    for (int i = 0; i < len_c_array; ++i) {
        candidate c = candidates[i];
        if(is_eliminated(c) == false) {
            if (c.vote_count != min) return 0;
        }
    }
    return 1;
}

int is_eliminated(candidate c){
if(c.eliminated == 1) return true;
else return false;
}

void set_votes_to_default(candidate *candidates, int arr_len){
    for (int i = 0; i < arr_len; ++i) {
        candidates[i].vote_count = 0;
    }
}

void count_votes(candidate *candidates, int arr_len, int num_of_voters, int preferences[num_of_voters][arr_len]){
    for (int i = 0; i < num_of_voters; ++i) {
        int counter = 0;
        candidate c;
        do{
            int candidate_index = preferences[i][counter];
            c = candidates[candidate_index];
            counter++;
        }
        while (is_eliminated(c) == true);
        c.vote_count++;
        counter = 0;
    }
}

void print_winners(candidate *candidates, int arr_len){
    for(int i = 0; i < arr_len; i++){
        candidate c = candidates[i];
        if(is_eliminated(c) == false) printf("%s", c.name);
    }
}

void eliminate_c_with_min_votes(candidate *candidates, int len_c_array, int min){
    for (int i = 0; i < len_c_array; ++i) {
        candidate c = candidates[i];
        if(is_eliminated(c) == false){
        if (c.vote_count == min) c.eliminated = 1;
        }
    }
}

