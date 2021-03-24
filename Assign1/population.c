#include <stdio.h>
#include <cs50.h>

int main(void){
	// read in the customized start population size
	int start = 0;
	while (start < 9){
		start = get_int("Start size: ");
	}

	// read in the customized end population size
	int end = 0;
	while (end < start){
		end = get_int("End size: ");
	}

	// output the calculated the number of years for the population to reach the end value
	int year = 0;
	while (start < end){
		start += start / 3 - start / 4;
		year  += 1;
	}
	printf("Years: %d\n", year);
	return 0;
}