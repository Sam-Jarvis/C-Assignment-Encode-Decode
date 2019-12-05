#include<time.h>
#include"encode.h"
#include"channel.h"
#include"decode.h"
#include"includes.h"

int main() {
	srand(time(0));

	encodeFile();
	simulateBadTransmission();
	decodeFile();

	return 0;
}