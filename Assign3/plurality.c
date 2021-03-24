#include <stdio.h>
#include <string.h>
#include <cs50.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct{
	string name;
	int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

#define assert1(){printf("Usage: plurality [candidate ...]\n"); return 1;}
#define assert2(){printf("Maximum number of candidates is %i\n", MAX); return 2;}

int main(int argc, char **argv){
	// return directly if wrong command format
	if (argc < 2)       assert1();
	if (argc - 1 > MAX) assert2();

	candidate_count = argc - 1;
	for (int k = 0; k < candidate_count; k ++){
		candidates[k].name = argv[k + 1];
		candidates[k].votes = 0;
	}

	// loop over all voters
	int voter_count = get_int("Number of voters: ");
	for (int k = 0; k < voter_count; k ++){
		string name = get_string("Vote: ");

		if (!vote(name)) printf("Invalid vote.\n");
	}

	// display winner of election
	print_winner();
}

// update vote totals given a new vote
bool vote(string name){
	for (int k = 0; k < candidate_count; k ++){
		if (strcmp(candidates[k].name, name) == 0){
			candidates[k].votes += 1;
			return true;
		}
	}
	return false;
}

// print the winner (or winners) of the election
void print_winner(void){
	int max_vote = 0;
	int max_name = 0;
	for (int k = 0; k < candidate_count; k ++){
		if (max_vote < candidates[k].votes){
			max_vote = candidates[k].votes;
			max_name = (1 << k);
		}
		else if (max_vote == candidates[k].votes){
			max_name = (1 << k) | max_name;
		}
	}

	for (int k = 0; k < candidate_count; k ++){
		if ((1 << k) & max_name) printf("%s\n", candidates[k].name);
	}
	return;
}

