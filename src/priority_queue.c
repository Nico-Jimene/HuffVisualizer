#include "../include/priority_queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *enqueue(Node **head, void *value,
              int (*compareFN)(void const *, void const *)) {
  Node *tempNode = malloc(sizeof(*tempNode));
  tempNode->value = value;
  tempNode->next = NULL;

  if (*head == NULL) {
    *head = tempNode;
  } else {
    Node *prev = NULL;
    Node *loopNode = *head;

    while (loopNode != NULL && (compareFN(loopNode->value, value) <= 0)) {
      prev = loopNode;
      loopNode = loopNode->next;
    }

    if (loopNode == *head) {
      tempNode->next = *head;
      *head = tempNode;
    } else {
      prev->next = tempNode;
      tempNode->next = loopNode;
    }
  }
  return tempNode;
}

Node *dequeue(Node **head) {
  if (*head != NULL) {

    Node *temp = *head;
    *head = (*head)->next;
    temp->next = NULL;
    return temp;

  } else {
    return NULL;
  }
}

Node *stackPush(Node **head, void *value) {
  Node *temp = malloc(sizeof(*temp));
  temp->value = value;
  temp->next = *head;
  *head = temp;

  return *head;
}

Node *stackPop(Node **head) { return (dequeue(head)); }

void destroyList(Node **head) {
  Node *loopNode = *head;

  while (loopNode != NULL) {
    Node *temp = loopNode->next;
    free(loopNode);
    loopNode = temp;
  }
  *head = NULL;
}
