#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(void){
	// read in the customized height
	int height = 0;
	while (height < 1 || height > 8){
		height = get_int("Height: ");
	}

	// output the mario pyramids with two space in the middle
	for (int k = 0; k < height; k ++){
		int print = 0;
		while (print <= height + k + 2){
			if (print < height - k - 1 || print == height || print == height + 1) printf(" ");
			else printf("#");
			print += 1;
		}
		printf("\n");
	}
	return 0;
}