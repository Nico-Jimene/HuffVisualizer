#ifndef __BIT__WRITER_H
#define __BIT__WRITER_H

#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct {
  FILE *fp;
  uint8_t currByte;
  uint8_t bitsLeft;
} BitWriter;

BitWriter openBitWriter(const char *path);
void writeBits(BitWriter *writer, uint8_t bits, uint8_t numBitsWrite);
void flushBits()

#endif
