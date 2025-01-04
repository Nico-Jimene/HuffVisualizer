#include "../include/bit_writer.h"
#include <assert.h>
#include <sys/types.h>

BitWriter openBitWriter(const char *path) {
  return (BitWriter){.fp = fopen(path, "w"), .bitsLeft = 8, .currByte = 0};
}

void writeBits(BitWriter *writer, u_int8_t bits, u_int8_t numBitsWrite) {

  /*printf("%d\n", bits);*/
  assert(numBitsWrite >= 0 && numBitsWrite <= 8);
  assert(writer->bitsLeft >= 1 && writer->bitsLeft <= 8);

  if (numBitsWrite > writer->bitsLeft) {
    u_int8_t bitVal = writer->bitsLeft;
    writeBits(writer, bits >> (numBitsWrite - bitVal), bitVal);
    numBitsWrite -= bitVal;
  }

  bits = ((u_int8_t)(bits << (8 - numBitsWrite))) >> (8 - writer->bitsLeft);
  writer->currByte |= bits;
  writer->bitsLeft -= numBitsWrite;

  if (writer->bitsLeft == 0) {
    flushBitWriter(writer);
  }
}

void flushBitWriter(BitWriter *writer) {
  if (writer->bitsLeft != 8) {
    fwrite(&(writer->currByte), sizeof(writer->currByte), 1, writer->fp);
  }
  writer->currByte = 0x00;
  writer->bitsLeft = 8;
}

void closeBitWriter(BitWriter *writer) {
  flushBitWriter(writer);
  fclose(writer->fp);
  writer->fp = NULL;
}
