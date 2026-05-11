#include "ds.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  List *list = list_create();

  int a = 10, b = 20, c = 30;

  list_push(list, &a);
  list_push(list, &b);
  list_push(list, &c);

  printf("size: %d\n", list_size(list));

  int *val;

  while ((val = list_pop(list)) != NULL) {
    printf("popped: %d\n", *val);
  }

  printf("size: %d\n", list_size(list));

  list_free(list);

  return 0;
}
