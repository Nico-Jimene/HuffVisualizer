#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct _Node {
  void *value;
  struct _Node *next;
} Node;

Node *enqueue(Node **head, void *val,
              int (*compareFN)(void const *, void const *));
Node *dequeue(Node **head);
Node *stackPush(Node **head, void *val);
Node *stackPop(Node **head);
void destroyList(Node **head);
void destroyListHUFFMAN(Node **head);

#endif
