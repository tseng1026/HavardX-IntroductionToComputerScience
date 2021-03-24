#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t HEADER;
typedef int16_t SAMPLE;

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

#define assert1(){printf("Usage: ./volume input.wav output.wav factor\n"); return 1;}
#define assert2(){printf("Could not open file.\n"); return 1;}

int main(int argc, char *argv[]){
	// return directly if wrong command format
	if (argc != 4) assert1();

	// open files and determine scaling factor
	FILE *input  = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");
	if (input  == NULL) assert2();
	if (output == NULL) assert2();

	float factor = atof(argv[3]);

	// copy header from input file to output file
	HEADER header[HEADER_SIZE];
	fread (header, sizeof(HEADER), HEADER_SIZE, input);
	fwrite(header, sizeof(HEADER), HEADER_SIZE, output);

	// read samples from input file and write updated data to output file
	SAMPLE sample;
	while (fread(&sample, sizeof(SAMPLE), 1, input)){
		sample *= factor;
		fwrite(&sample, sizeof(SAMPLE), 1, output);
	}

	// close files
	fclose(input);
	fclose(output);
}
