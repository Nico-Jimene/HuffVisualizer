#include "priority_queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*int compareFN(void *val1, void *val2) {*/
/**/
/*  int value1 = *(int *)val1;*/
/*  int value2 = *(int *)val2;*/
/*}*/

Node *stackPush(Node **head, void *value) {
  Node *temp = malloc(sizeof(*temp));
  temp->value = value;
  temp->next = *head;
  *head = temp;

  return *head;
}

// Node *enqueu(Node **head, void *value) {}
