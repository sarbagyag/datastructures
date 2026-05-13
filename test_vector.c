#include "ds.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  Vector *v = vec_create();

  int nums[20];

  for (int i = 0; i < 20; i++) {
    nums[i] = i * 10;
    vec_push(v, &nums[i]);
  }

  printf("size: %d\n", vec_size(v));

  for (int i = 0; i < vec_size(v); i++) {
    int *val = (int *)vec_get(v, i);
    printf("v[%d]=%d\n", i, *val);
  }

  vec_free(v);

  // realloc test

  printf("\nrealloc test:\n");

  Vector *v2 = vec_create();

  int big[100];

  for (int i = 0; i < 100; i++) {
    big[i] = i;
    vec_push(v2, &big[i]);
  }

  printf("size: %d\n", vec_size(v2));
  printf("first: %d\n", *(int *)vec_get(v2, 0));
  printf("last: %d\n", *(int *)vec_get(v2, 99));
  printf("mid: %d\n", *(int *)vec_get(v2, 50));

  vec_free(v2);

  return 0;
}
