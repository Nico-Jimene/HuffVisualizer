#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "frequencies.h"
#include "priority_queue.h"
typedef struct _TreeNode {
  unsigned char ch;
  size_t frequency;
  struct _TreeNode *left;
  struct _TreeNode *right;

} TreeNode;

Node *huffmanLinkedList(Freqs f);

#endif
