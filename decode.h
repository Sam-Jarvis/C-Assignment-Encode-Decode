#ifndef DECODE_H
#define DECODE_H
#include"includes.h"

typedef int bool;
#define true 1
#define false 0

void decodeFile();
uint8_t extractMsn(uint8_t inputByte);
uint8_t extractLsn(uint8_t inputByte);
bool isCorrupt(uint8_t inputByte, uint8_t parityCircle);
uint8_t fixCorrupted(uint8_t inputByte);

#endif // !DECODE_H