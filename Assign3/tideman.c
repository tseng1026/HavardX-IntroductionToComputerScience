#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct{
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

#define assert1(){printf("Usage: tideman [candidate ...]\n"); return 1;}
#define assert2(){printf("Maximum number of candidates is %i\n", MAX); return 2;}

int main(int argc, char **argv){
	// return directly if wrong command format
	if (argc < 2)       assert1();
	if (argc - 1 > MAX) assert2();

	candidate_count = argc - 1;
	for (int k = 0; k < candidate_count; k ++){
		candidates[k] = argv[k + 1];
	}

	// clear graph of locked in pairs
	for (int i = 0; i < candidate_count; i ++){
		for (int j = 0; j < candidate_count; j ++){
			locked[i][j] = false;
		}
	}

	pair_count = 0;
	int voter_count = get_int("Number of voters: ");

	// query for votes
	for (int i = 0; i < voter_count; i++){
		int ranks[candidate_count];

		for (int j = 0; j < candidate_count; j++){
			string name = get_string("Rank %i: ", j + 1);

			if (!vote(j, name, ranks)){
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

// update ranks given a new vote
bool vote(int rank, string name, int ranks[]){
	for (int k = 0; k < candidate_count; k ++){
		if (strcmp(candidates[k], name) == 0){
			ranks[rank] = k;
			return true;
		}
	}
	return false;
}

// update preferences given one voter's ranks
void record_preferences(int ranks[]){
	for (int i = 0; i < candidate_count; i ++){
		for (int j = i + 1; j < candidate_count; j ++){
			preferences[ranks[i]][ranks[j]] += 1;
		}
	}
	return;
}

// record pairs of candidates where one is preferred over the other
void add_pairs(void){
	for (int i = 0; i < candidate_count; i ++){
		for (int j = i + 1; j < candidate_count; j ++){
			if (preferences[i][j] >= preferences[j][i]){
				pairs[pair_count].winner = i;
				pairs[pair_count].loser  = j;
				pair_count += 1;
			}
			if (preferences[i][j] <= preferences[j][i]){
				pairs[pair_count].winner = j;
				pairs[pair_count].loser  = i;
				pair_count += 1;
			}
		}
	}
	return;
}

// sort pairs in decreasing order by strength of victory
int compare(const void *a, const void *b){
	pair *pair1 = (pair *)a;
	pair *pair2 = (pair *)b;
	return (preferences[pair2->winner][pair2->loser] - preferences[pair1->winner][pair1->loser]);
}

void sort_pairs(void){
	qsort(pairs, pair_count, sizeof(pair), compare);
	return;
}

// lock pairs into the candidate graph in order, without creating cycles
bool cycle(int curr, int head){
	if (curr == head) return true;

	for (int k = 0; k < candidate_count; k ++){
		if (locked[curr][k]){
			if (cycle(k, head)) return true;
		}
	}
	return false;
}

void lock_pairs(void){
	for (int k = 0; k < pair_count; k ++){
		if (cycle(pairs[k].loser, pairs[k].winner)) continue;
		locked[pairs[k].winner][pairs[k].loser] = true;
	}
	return;
}

// print the winner of the election
void print_winner(void){
	for (int i = 0; i < candidate_count; i ++){
		int flag = 0;
		for (int j = 0; j < candidate_count; j ++){
			if (!locked[j][i]) flag += 1;
			if (flag == candidate_count) printf("%s\n", candidates[i]);
		}
	}
	return;
}