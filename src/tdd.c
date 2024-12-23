#include <stdio.h>
#include <stdlib.h>

#include "../include/priority_queue.h"
#include "../include/tdd.h"

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

  enqueue(&head, &val1);
  enqueue(&head, &val2);
  enqueue(&head, &val3);
  enqueue(&head, &val4);
  enqueue(&head, &val5);

  test_check(*(int *)(head)->value == 1);
  test_check(*(int *)(head)->next->value == 5);
  test_check(*(int *)(head)->next->next->value == 8);
  test_check(*(int *)(head)->next->next->next->value == 10);
  test_check(*(int *)(head)->next->next->next->next->value == 15);

  destroyList(&head);

  test_end();
}

static int linkedListPQ_DEQ() {
  test_start();

  Node *head = NULL;

  int val1 = 1;
  int val2 = 5;
  int val3 = 10;
  int val4 = 15;
  int val5 = 8;

  enqueue(&head, &val1);
  enqueue(&head, &val2);
  enqueue(&head, &val3);
  enqueue(&head, &val4);
  enqueue(&head, &val5);

  Node *popNode = dequeue(&head);

  test_check(*(int *)(head)->value == 5);

  destroyList(&popNode);
  destroyList(&head);

  test_end();
}

int main() {
  test_run(stackPushTest);
  test_run(stackPopTest);
  test_run(linkedListPQ_ENQ);
  test_run(linkedListPQ_DEQ);

  return EXIT_SUCCESS;
}
