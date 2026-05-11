#ifndef DS_H
#define DS_H

#include <stdlib.h>

// Linked List

typedef struct List List;

List *list_create(void);
void list_push(List *list, void *data);
void *list_pop(List *list);
void list_free(List *list);
int list_size(List *list);

#endif
