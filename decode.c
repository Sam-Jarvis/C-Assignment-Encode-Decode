#include"decode.h"
/*
int main(int argc, char *argv[]) {

	if (argc != 3) {
		printf("Incorrect arguments passed.\n");
		return -1;
	}
	decodeFile(argv[1], argv[2]);
	return 0;
}
*/

/*
void decodeFile(*inFile, *outFile)
{
	FILE *inFile = fopen(inFile, "r");
	FILE *outFile = fopen(outFile, "w");
}
*/

void decodeFile()
{
	FILE *inFile = fopen("D:/Downloads/PRC1/testbadtrans.txt", "r");
	FILE *outFile = fopen("D:/Downloads/PRC1/testdecode.txt", "w");

	if (inFile == NULL)
	{
		printf("%s\n", "Read file couldn't be opened.");
	}
	if (outFile == NULL)
	{
		printf("%s\n", "Write file couldn't be opened.");
	}

	fseek(inFile, 0, SEEK_END);
	int sizeOfFile = ftell(inFile);
	fseek(inFile, 0, SEEK_SET);

	char a = 0x00;
	for (size_t i = 0; i < sizeOfFile / 2; i++)
	{
		a = extractMsn(fixCorrupted(fgetc(inFile)));
		a |= extractLsn(fixCorrupted(fgetc(inFile)));

		fputc(a, outFile);
		printf("Decoded: %C\n", a);
	}
	fclose(inFile);
	fclose(outFile);
	printf("\n");
}


uint8_t extractMsn(uint8_t inputByte)
{
	uint8_t outputByte = inputByte & 0x78;
	outputByte <<= 1;
	return outputByte;
}

uint8_t extractLsn(uint8_t inputByte)
{
	uint8_t outputByte = inputByte & 0x78;
	outputByte >>= 3;
	return outputByte;
}

bool isCorrupt(uint8_t inputByte, uint8_t parityCircleMask)
{
	uint8_t mask = 0x80; 
	uint8_t byteToTest = inputByte & parityCircleMask;
	uint8_t counter = 0;

	for (size_t i = 0; i < 8; i++)
	{
		if (byteToTest & mask)
		{
			counter++;
		}
		mask >>= 1;
	}

	if ((counter % 2) != 0)
	{
		return true; // error
	}
	return false; // no error
}

uint8_t fixCorrupted(uint8_t inputByte)
{
	uint8_t p0 = 0x39;
	uint8_t p1 = 0x5A;
	uint8_t p2 = 0x74;

	uint8_t outputByte = inputByte;

	if (isCorrupt(inputByte, p0)) // if p0 is corrupt
	{
		if (isCorrupt(inputByte, p1)) // if p1 is corrupt
		{
			if (isCorrupt(inputByte, p2)) // if p2 is corrupt
			{
				outputByte = inputByte ^ 0x10; // flip d1
			}
			else 
			{
				outputByte = inputByte ^ 0x08; // flip d0
			}
		}
		else
		{
			if (isCorrupt(inputByte, p2))
			{
				outputByte = inputByte ^ 0x20; // flip d2
			}
			else
			{
				outputByte = inputByte ^ 0x01; // flip p0
			}
		}
	}
	else
	{
		if (isCorrupt(inputByte, p1))
		{
			if (isCorrupt(inputByte, p2))
			{
				outputByte = inputByte ^ 0x40; // flip d3
			}
			else
			{
				outputByte = inputByte ^ 0x02; // flip p1
			}
		}
		else
		{
			if (isCorrupt(inputByte, p2))
			{
				outputByte = inputByte ^ 0x04;// flip p2
			}
		}
	}
	return outputByte;
}