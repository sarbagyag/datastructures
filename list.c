#include "ds.h"

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

typedef struct List {
  Node *head;
  int size;
} List;

List *list_create(void) {
  List *list = malloc(sizeof(List));

  if (!list)
    return NULL;

  list->head = NULL;
  list->size = 0;

  return list;
}

void list_push(List *list, void *data) {
  Node *node = malloc(sizeof(Node));
  if (!node)
    return;

  node->data = data;
  node->next = list->head;
  list->head = node;
  list->size++;
}

void *list_pop(List *list) {

  if (list->head == NULL) {
    return NULL;
  }

  Node *node = list->head;
  void *data = node->data;

  list->head = node->next;
  free(node);
  list->size--;

  return data;
}

void list_free(List *list) {
  Node *curr = list->head;

  while (curr) {
    Node *next = curr->next;
    free(curr);
    curr = next;
  }
  free(list);
}

int list_size(List *list) { return list->size; }
