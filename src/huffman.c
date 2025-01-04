#include "../include/huffman.h"
#include <sys/types.h>

static int compareTreeNodes(void const *Tree1, void const *Tree2) {
  TreeNode const *tNode1 = Tree1;
  TreeNode const *tNode2 = Tree2;

  if (tNode1->frequency != tNode2->frequency) {
    return (tNode1->frequency - tNode2->frequency);
  } else if (tNode2->ch == '\0') {
    return (-1);
  }

  return (tNode1->ch - tNode2->ch);
}

void storeCompressedCharacter(TreeNode *root, BitCode *charToCode,
                              u_int8_t bits, u_int8_t bitAmount) {
  if (root != NULL) {
    if ((root->left) == NULL && (root->right) == NULL) {
      charToCode[root->ch].bits = bits;
      charToCode[root->ch].bitAmount = bitAmount;
    }
    bits = bits << 1;
    bitAmount += 1;

    storeCompressedCharacter(root->left, charToCode, bits, bitAmount);
    bits |= 1;
    storeCompressedCharacter(root->right, charToCode, bits, bitAmount);
  }
}

Node *huffmanLinkedList(Freqs f) {

  Node *head = NULL; // Linked List head
  TreeNode *frequencyValue = NULL;
  for (int i = 0; i < 256; i++) {
    if (f[i] != 0) {
      frequencyValue = malloc(sizeof(*frequencyValue));
      frequencyValue->left = NULL;
      frequencyValue->right = NULL;
      frequencyValue->ch = i;
      frequencyValue->frequency = f[i];
      enqueue(&head, frequencyValue, compareTreeNodes);
    }
  }
  return head;
}

TreeNode *buildHuffmanTree(Node *head) {
  TreeNode *rootNode = NULL;

  if (head == NULL) {
    return NULL;
  } else {
    while (head->next != NULL) {
      rootNode = malloc(sizeof(*rootNode));
      rootNode->ch = '\0';
      rootNode->left = head->value;
      rootNode->right = head->next->value;
      rootNode->frequency =
          rootNode->left->frequency + rootNode->right->frequency;

      free(dequeue(&head));
      free(dequeue(&head));

      enqueue(&head, rootNode, compareTreeNodes);
    }

    rootNode = (TreeNode *)(head->value);
    free(head);
    return rootNode;
  }
}

void destroyHuffTree(TreeNode **root) {
  if (*root != NULL) {

    destroyHuffTree(&(*root)->left);
    destroyHuffTree(&(*root)->right);
    free(*root);
  }

  *root = NULL;
}

void encodingTreeTable(TreeNode *root, BitWriter *writer) {
  if (root != NULL) {

    encodingTreeTable(root->left, writer);
    encodingTreeTable(root->right, writer);

    if ((root->left) == NULL && (root->right) == NULL) {
      writeBits(writer, 1, 1);
      writeBits(writer, root->ch, 8);
    } else {
      writeBits(writer, 0, 1);
    }
  }
}

void writeCompressedChar(TreeNode *root, BitWriter *writer,
                         u_int8_t *uncompressedByte) {
  BitCode charToCode[256] = {{.bits = 0, .bitAmount = 0}};
  storeCompressedCharacter(root, charToCode, 0, 0);
  int i = 0;

  while (uncompressedByte[i] != '\0') {
    writeBits(writer, charToCode[uncompressedByte[i]].bits,
              charToCode[uncompressedByte[i]].bitAmount);
    i++;
  }
}
