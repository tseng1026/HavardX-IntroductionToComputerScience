#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BUFFER;

#define assert1(){printf("Usage: ./recover image\n"); return 1;}
#define assert2(){printf("Could not open file.\n"); return 1;}

int main(int argc, char *argv[]){
	// return directly if wrong command format
	if (argc != 4) assert1();

	// open files
	FILE *card = fopen(argv[1], "r");
	if (card  == NULL) assert2();

	// read from file and separate to several images
	int index = 0;
	char filename[8] = {'\0'};
	BUFFER buffer[512];
	while (fread(buffer, sizeof(BUFFER), 512, card) == 512){
		if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
			sprintf(filename, "%03i.jpg", index);
			index ++;

			FILE *imageFile = fopen(filename, "w");
			fwrite(buffer, 1, 512, imageFile);
			fclose(imageFile);
		}
		else if (index != 0){
			FILE *imageFile = fopen(filename, "a");
			fwrite(buffer, 1, 512, imageFile);
			fclose(imageFile);
		} 
	}
	return 0;
}