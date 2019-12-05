#include"channel.h"

/*
int main(int argc, char *argv[]) {

	if (argc != 3) {
		printf("Incorrect arguments passed.\n");
		return -1;
	}
	simulateBadTransmision(argv[1], argv[2]);
	return 0;
}
*/

/*
	FILE *inFile = fopen(inFile, "r");
	FILE *outFile = fopen(outFile, "w");
*/

void simulateBadTransmission()
{
	FILE *inFile = fopen("D:/Downloads/PRC1/testencode.txt", "r");
	FILE *outFile = fopen("D:/Downloads/PRC1/testbadtrans.txt", "w");

	if (inFile == NULL)
	{
		printf("%s\n", "Read file couldn't be opened.");
	}
	if (outFile == NULL)
	{
		printf("%s\n", "Write file couldn't be opened.");
	}

	uint8_t c;
	int result;
	result = fread(&c, 1, 1, inFile);
	while (result > 0) {
		printf("Flipping: %C\n", c);

		// screw up transmittion
		uint8_t brokenBit = flipBit(c);

		result = fread(&c, 1, 1, inFile);

		// write broken bit to file
		putc(brokenBit, outFile);
	}
	printf("\n");
	fclose(inFile);
	fclose(outFile);
}

uint8_t flipBit(uint8_t inputByte) {

	uint8_t xorMask = 0x80; // initalize mask 1000 0000
	xorMask >>= randomNumber(); // shift mask by random no.

	uint8_t flippedBit = inputByte ^ xorMask; // use random mask to flip bit
	return flippedBit;
}

int randomNumber() 
{
	return rand() / (RAND_MAX / 8);
}