#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"
#include "tdd.h"

static int stackPushTest() {
  test_start();

  Node *head = NULL;
  int val = 15;
  head = stackPush(&head, &val);
  test_check(head->value == &val);

  test_end();
}

int main() {
  test_run(stackPushTest);

  return EXIT_SUCCESS;
}
