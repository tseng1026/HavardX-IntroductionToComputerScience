#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void){
	string text = get_string("Text: ");

	int letter = 0, word = 1, sentence = 0;
	for (int k = 0; k < strlen(text); k ++){
		// update number of letters
		if (isalpha(text[k])) letter ++;

		// update number of words
		if (isspace(text[k])) word ++;

		// update number of senetences
		if (text[k] == '.' || text[k] == '!' || text[k] == '?') sentence ++;
	}

	float index = 0.0588 * letter / word * 100 - 0.296 * sentence / word * 100 - 15.8;
	if (index >= 1 && index < 16) printf("Grade %d\n", (int)round(index));
	else if (index <  1 ) printf("Before Grade 1\n");
	else if (index >= 16) printf("Grade 16+\n");
	return 0;
}