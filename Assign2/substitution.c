#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

#define assert1(){printf("Usage: ./substitution key\n"); return 1;}
#define assert2(){printf("Key must contain 26 characters.\n"); return 1;}

int main(int argc, char **argv){
	// return directly if wrong command format
	if (argc < 2)              assert1();
	if (strlen(argv[1]) != 26) assert2();

	// check if the characters are distinct
	int arr[30] = {0};
	for (int k = 0; k < 26; k ++){
		int index = 0;
		if (!isalpha(argv[1][k])) {
			assert2();
		}
		else if (islower(argv[1][k])) index = argv[1][k] - 'a';
		else if (isupper(argv[1][k])) index = argv[1][k] - 'A';

		if (arr[index] == 1) assert2();
		arr[index] = 1;
	}

	// output the cipher text
	string plain = get_string("plaintext:  ");
	printf("ciphertext: ");
	for (int k = 0; k < strlen(plain); k ++){
		if (!isalpha(plain[k])) printf("%c", plain[k]);
		else if (islower(plain[k])) printf("%c", tolower(argv[1][plain[k] - 'a']));
		else if (isupper(plain[k])) printf("%c", toupper(argv[1][plain[k] - 'A']));
	}
	printf("\n");
	return 0;
}