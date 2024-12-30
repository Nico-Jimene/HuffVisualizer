#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/frequencies.h"
#include "../include/huffman.h"
#include "../include/priority_queue.h"
#include "../include/tdd.h"

static int compareFN(void const *val1, void const *val2) {
  return (*(int const *)val1 - *(int const *)val2);
}

static int compareFNSTR(void const *val1, void const *val2) {
  return strcmp(val1, val2);
}

static int stackPushTest() {
  test_start();

  Node *head = NULL;
  int val = 15;
  head = stackPush(&head, &val);
  test_check(head->value == &val);

  destroyList(&head);

  test_end();
}

static int stackPopTest() {
  test_start();
  Node *head = NULL;

  int val1 = 1;
  int val2 = 2;
  int val3 = 3;
  int val4 = 4;

  stackPush(&head, &val1);
  stackPush(&head, &val2);
  stackPush(&head, &val3);
  stackPush(&head, &val4);

  Node *popHead = NULL;
  popHead = stackPop(&head);

  test_check(*(int *)(popHead)->value == 4); // Dereference INT to compare value
  test_check((popHead)->value == &val4); // Checks to see if the address is the
                                         // same, meaning no copies were made
  test_check(*(int *)(head)->value == 3);
  test_check(head->value == &val3);

  destroyList(&head);
  destroyList(&popHead);

  test_end();
}

static int linkedListPQ_ENQ() {
  test_start();

  Node *head = NULL;

  int val1 = 1;
  int val2 = 5;
  int val3 = 10;
  int val4 = 15;
  int val5 = 8;

  enqueue(&head, &val1, compareFN);
  enqueue(&head, &val2, compareFN);
  enqueue(&head, &val3, compareFN);
  enqueue(&head, &val4, compareFN);
  enqueue(&head, &val5, compareFN);

  test_check(*(int *)(head)->value == 1);
  test_check(*(int *)(head)->next->value == 5);
  test_check(*(int *)(head)->next->next->value == 8);
  test_check(*(int *)(head)->next->next->next->value == 10);
  test_check(*(int *)(head)->next->next->next->next->value == 15);

  destroyList(&head);

  test_end();
}

static int linkedListPQ_DEQSTR() {
  test_start();

  Node *head = NULL;

  char *str1 = "New";
  char *str2 = "York";
  char *str3 = "Knicks";

  enqueue(&head, str1, compareFNSTR);
  enqueue(&head, str2, compareFNSTR);
  enqueue(&head, str3, compareFNSTR);

  test_string_equal(head->value, "Knicks");
  test_string_equal(head->next->value, "New");
  test_string_equal(head->next->next->value, "York");

  Node *popHead = dequeue(&head);

  test_string_equal(popHead->value, "Knicks");

  destroyList(&head);
  destroyList(&popHead);

  test_end();
}

static int testFrequenciesEMPTY() {
  test_start();

  Freqs f = {0};
  const char *path = "../text.txt"; // Wrong Path
  test_check(totalFrequncies(f, path) == false);

  test_end();
}

static int testFrequencies() {
  test_start();

  Freqs f = {0};
  const char *path = "text.txt";

  test_check(totalFrequncies(f, path) == true);

  // Print Frequencies
  /*for (int i = 0; i < 256; i++) {*/
  /*  if (f[i] != 0 && (i >= 32 && i <= 120)) {*/
  /*    printf("%c : %d\n", (char)i, (int)f[i]);*/
  /*  }*/
  /*}*/
  /**/
  test_check(f['!'] == 1);
  test_check(f['='] == 1);
  test_check(f['D'] == 1);
  test_check(f['G'] == 1);
  test_check(f['T'] == 1);
  test_check(f['a'] == 2);
  test_check(f['c'] == 1);
  test_check(f['n'] == 2);
  test_check(f['o'] == 1);
  test_check(f['t'] == 1);
  test_check(f['u'] == 1);

  test_end();
}

static int testHuffmanPQ() {
  test_start();

  Freqs f = {0};
  const char *path = "test.txt";
  test_check(totalFrequncies(f, path));

  Node *test = huffmanLinkedList(f);

  /*Node *head = test;*/
  /**/
  /*while (head != NULL) {*/
  /*  printf("%zu %c\n", ((TreeNode *)(head->value))->frequency,*/
  /*         ((TreeNode *)(head->value))->ch);*/
  /**/
  /*  head = head->next;*/
  /*}*/
  /**/
  /*printf("%zu %c\n", ((TreeNode *)(test->next->next->value))->frequency,*/
  /*       ((TreeNode *)(test->next->next->value))->ch);*/
  /**/

  test_check(((TreeNode *)(test->value))->frequency == 1);
  test_check(((TreeNode *)(test->value))->ch == 'e');

  test_check(((TreeNode *)(test->next->value))->frequency == 1);
  test_check(((TreeNode *)(test->next->value))->ch == 'l');

  test_check(((TreeNode *)(test->next->next->value))->frequency == 2);
  test_check(((TreeNode *)(test->next->next->value))->ch == 'a');

  test_check(((TreeNode *)(test->next->next->next->value))->frequency == 2);
  test_check(((TreeNode *)(test->next->next->next->value))->ch == 'p');

  destroyListHUFFMAN(&test);
  /*destroyListHUFFMAN(&head);*/
  test_end();
}

static int testEmptyTree() {
  test_start();

  Freqs f = {0};
  const char *path = "empty.txt";
  test_check(totalFrequncies(f, path));

  Node *head = huffmanLinkedList(f);

  int k = 0;

  while (k != 256) {
    test_check(f[k] == 0);
    k += 1;
  }

  TreeNode *root = buildHuffmanTree(head);
  test_check(root == NULL);

  destroyHuffTree(&root);

  test_end();
}

static int testHuffmanTree() {
  test_start();

  Freqs f = {0};
  const char *path = "test.txt";
  test_check(totalFrequncies(f, path));

  Node *head = huffmanLinkedList(f);

  TreeNode *root = buildHuffmanTree(head);

  test_check(root->frequency == 6);
  test_check(root->left->frequency == 2);

  test_check(root->left->ch == 'p');
  test_check(root->right->frequency == 4);

  test_check(root->right->left->frequency == 2);

  test_check(root->right->right->frequency == 2);
  test_check(root->right->right->ch == 'a');

  test_check(root->right->left->left->frequency == 1);
  test_check(root->right->left->left->ch == 'e');

  test_check(root->right->left->right->frequency == 1);
  test_check(root->right->left->right->ch == 'l');

  destroyHuffTree(&root);

  test_end();
}

int main() {
  test_run(stackPushTest);
  test_run(stackPopTest);
  test_run(linkedListPQ_ENQ);
  test_run(linkedListPQ_DEQSTR);
  test_run(testFrequenciesEMPTY);
  test_run(testFrequencies);
  test_run(testHuffmanPQ);
  test_run(testEmptyTree);
  test_run(testHuffmanTree);
  return EXIT_SUCCESS;
}
