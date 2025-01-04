#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "bit_writer.h"
#include "frequencies.h"
#include "priority_queue.h"
#include <sys/types.h>
typedef struct _TreeNode {
  unsigned char ch;
  size_t frequency;
  struct _TreeNode *left;
  struct _TreeNode *right;

} TreeNode;

typedef struct _BitCode {
  u_int8_t bits;
  int bitAmount;
} BitCode;

Node *huffmanLinkedList(Freqs f);
TreeNode *buildHuffmanTree(Node *head);
void destroyHuffTree(TreeNode **root);
void encodingTreeTable(TreeNode *root, BitWriter *writer);
void storeCompressedCharacter(TreeNode *root, BitCode *charToCode,
                              u_int8_t bits, u_int8_t bitAmount);
void writeCompressedChar(TreeNode *root, BitWriter *writer,
                         u_int8_t *uncompressedByte);
#endif
