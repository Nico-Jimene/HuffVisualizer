#ifndef __BIT__WRITER_H
#define __BIT__WRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct {
  FILE *fp;
  u_int8_t currByte;
  u_int8_t bitsLeft;
} BitWriter;

BitWriter openBitWriter(const char *path);
void writeBits(BitWriter *writer, u_int8_t bits, u_int8_t numBitsWrite);
void flushBitWriter(BitWriter *writer);
void closeBitWriter(BitWriter *writer);

#endif
