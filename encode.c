#include"encode.h"
/*
int main(int argc, char *argv[]) {

	if (argc != 3) {
		printf("Incorrect arguments passed.\n");
		return -1;
	}
	encodeFile(argv[1], argv[2]);
	return 0;
}
*/

/*
void encodeFile(*inFile, *outFile)
{
	FILE *inFile = fopen(inFile, "r");
	FILE *outFile = fopen(outFile, "w");
}
*/

void encodeFile()
{
	FILE *inFile = fopen("D:/Downloads/PRC1/testread.txt", "r");
	FILE *outFile = fopen("D:/Downloads/PRC1/testencode.txt", "w");

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
		printf("Encoding: %C\n", c);
		// split byte into msn and lsn
		uint8_t msn = captureMsn(c);
		uint8_t lsn = captureLsn(c);

		// set parity
		uint8_t msnReady = setParityBits(msn);
		uint8_t lsnReady = setParityBits(lsn);

		result = fread(&c, 1, 1, inFile);

		// write to output file
		fputc(msnReady, outFile);
		fputc(lsnReady, outFile);
		
		// debug 
		/*
		printf("Raw MSN: %d \n", msn);
		printf("Raw LSN: %d \n", lsn);
		printf("Encoded MSN: %d \n", msnReady);
		printf("Encoded LSN: %d \n", lsnReady);
		*/
	}
	printf("\n");
	fclose(inFile);
	fclose(outFile);
}

uint8_t captureMsn(uint8_t inputByte)
{
	uint8_t mask = 0xf0;
	inputByte &= mask;
	inputByte >>= 1;
	return inputByte;
}
// Old method with arrays
	/*
	uint8_t setMask = 0x80;

	for (uint8_t i = 0; i < 4; i++)
	{
		if (inputByte & setMask)
		{
			arrayOfBits[i] = 1;
		}
		setMask >>= 1;
	}
	*/


uint8_t captureLsn(uint8_t inputByte)
{
	// mask to extract lsn -> 0000 1111
	uint8_t mask = 0x0f;
	inputByte &= mask; // will return lsn

	inputByte <<= 3; // makes space for parity
	return inputByte;
}

// old mthod with arrays
	/*
	uint8_t setMask = 0x08;
	for (uint8_t i = 0; i < 4; i++)
	{
		if (inputByte & setMask)
		{
			arrayOfBits[i] = 1;
		}
		setMask >>= 1;
	}
	*/

uint8_t setParityBit(uint8_t inputByte, uint8_t maskd1, uint8_t maskd2, uint8_t maskd3, uint8_t parityMask) // sets parity bit for one circle
{
	int trueCount = 0;
	uint8_t outputByte = 0x00;

	if (inputByte & maskd1)
	{
		trueCount++;
	}

	if (inputByte & maskd2)
	{
		trueCount++;
	}

	if (inputByte & maskd3)
	{
		trueCount++;
	}

	if (trueCount % 2 != 0)
	{
		outputByte |= parityMask;
	}
	return inputByte |= outputByte; 
}



uint8_t setParityBits(uint8_t inputByte) // sets parity bits for all circles
{
/*
mask for parity bit p2 -> 0x04
mask for parity bit p1 -> 0x02
mask for parity bit p0 -> 0x01

mask for data bit d0 -> 0x08
mask for data bit d1 -> 0x10
mask for data bit d2 -> 0x20
mask for data bit d3 -> 0x40
*/
	uint8_t byteUnderConstruction = setParityBit(inputByte, 0x08, 0x10, 0x40, 0x02);
	byteUnderConstruction = setParityBit(byteUnderConstruction, 0x08, 0x10, 0x20, 0x01);
	byteUnderConstruction = setParityBit(byteUnderConstruction, 0x20, 0x10, 0x40, 0x04);
	return byteUnderConstruction;
}

// old method with arrays
/*
uint8_t setParityBits(uint8_t inputByte, uint8_t nibbleArray[4])
{
	uint8_t outputByte = 0x00;
	if ((nibbleArray[1] + nibbleArray[2] + nibbleArray[3]) % 2 != 0) // parity circle p0 is odd
	{
		outputByte |= 0x01;
	}
	if ((nibbleArray[0] + nibbleArray[2] + nibbleArray[3]) % 2 != 0) // parity circle p1 is odd
	{
		outputByte |= 0x02;
	}
	if ((nibbleArray[0] + nibbleArray[1] + nibbleArray[2]) % 2 != 0) // parity circle p2 is odd
	{
		outputByte |= 0x04;
	}
	return outputByte |= inputByte;
}
*/

