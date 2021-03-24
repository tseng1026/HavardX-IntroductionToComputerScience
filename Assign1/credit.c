#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

int main(void){
	// read in the customized card number
	long number = get_long("Number: ");
	long divide = number;

	// calculated the checksum
	int k = 0, odd = 0, even = 0;
	while (divide != 0){
		if (k % 2 == 0) even += divide % 10;
		if (k % 2 == 1){
			int tmp = (divide % 10) * 2;
			while (tmp != 0){
				odd += tmp % 10;
				tmp /= 10;
			}
		}
		divide /= 10;
		k += 1;
	}

	// output the issued company or invalid
	int sum = even + odd;
	if (sum % 10 != 0) printf("INVALID\n");
	else if (k == 13 && number / (long)pow(10, k - 1) == 4)  printf("VISA\n");
	else if (k == 16 && number / (long)pow(10, k - 1) == 4)  printf("VISA\n");
	else if (k == 15 && number / (long)pow(10, k - 2) == 34) printf("AMEX\n");
	else if (k == 15 && number / (long)pow(10, k - 2) == 37) printf("AMEX\n");
	else if (k == 16 && number / (long)pow(10, k - 2) == 51) printf("MASTERCARD\n");
	else if (k == 16 && number / (long)pow(10, k - 2) == 52) printf("MASTERCARD\n");
	else if (k == 16 && number / (long)pow(10, k - 2) == 53) printf("MASTERCARD\n");
	else if (k == 16 && number / (long)pow(10, k - 2) == 54) printf("MASTERCARD\n");
	else if (k == 16 && number / (long)pow(10, k - 2) == 55) printf("MASTERCARD\n");
	else printf("INVALID\n");

	return 0;
}