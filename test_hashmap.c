#include "ds.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  HashMap *map = map_create();

  int scores[4];

  scores[0] = 95;
  scores[1] = 87;
  scores[2] = 92;
  scores[3] = 78;

  map_put(map, "alice", &scores[0]);
  map_put(map, "bob", &scores[1]);
  map_put(map, "carol", &scores[2]);
  map_put(map, "dave", &scores[3]);

  printf("count: %d\n", map_count(map));

  printf("alice: %d\n", *(int *)map_get(map, "alice"));
  printf("bob:   %d\n", *(int *)map_get(map, "bob"));
  printf("carol: %d\n", *(int *)map_get(map, "carol"));
  printf("dave:  %d\n", *(int *)map_get(map, "dave"));

  // test update
  int new_score = 100;
  map_put(map, "alice", &new_score);
  printf("alice updated: %d\n", *(int *)map_get(map, "alice"));

  // test delete
  map_delete(map, "bob");
  printf("count after delete: %d\n", map_count(map));
  printf("bob after delete: %p\n", map_get(map, "bob"));

  // test missing key
  printf("missing: %p\n", map_get(map, "nobody"));

  map_free(map);
  return 0;
}
