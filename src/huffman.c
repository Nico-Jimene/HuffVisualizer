#include "../include/huffman.h"

static int compareTreeNodes(void const *Tree1, void const *Tree2) {
  TreeNode const *tNode1 = Tree1;
  TreeNode const *tNode2 = Tree2;

  if (tNode1->frequency == tNode2->frequency) {
    return (tNode1->ch - tNode2->ch);
  } else {

    return (tNode1->frequency - tNode2->frequency);
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

    return rootNode;
  }
}

void destroyHuffTree(TreeNode **root) {
  if (*root != NULL) {

    destroyHuffTree(&(*root)->left);
    destroyHuffTree(&(*root)->left);
    free(*root);
  }

  *root = NULL;
}
