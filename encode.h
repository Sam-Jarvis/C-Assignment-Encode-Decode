#ifndef ENCODE_H
#define ENCODE_H
#include"includes.h"

void encodeFile();
uint8_t captureMsn(uint8_t inputByte);
uint8_t captureLsn(uint8_t inputByte);
uint8_t setParityBit(uint8_t inputByte, uint8_t maskd1, uint8_t maskd2, uint8_t maskd3, uint8_t parityMask);
uint8_t setParityBits(uint8_t inputByte);

#endif // !ENCODE_H
