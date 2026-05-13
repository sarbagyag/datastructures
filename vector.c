#include "ds.h"
#include <_strings.h>
#include <stdlib.h>

typedef struct Vector {
  void **data;
  int size;
  int capacity;
} Vector;

Vector *vec_create(void) {
  Vector *v = malloc(sizeof(Vector));

  if (!v)
    return NULL;

  v->data =
      malloc(8 * sizeof(void *)); // so v->data gets the pointer to equivalent
                                  // to 8 * sizeof(void *) memory space

  if (!v->data) {
    free(v);
    return NULL;
  }

  v->size = 0;
  v->capacity = 8;

  return v;
}

void vec_push(Vector *v, void *data) {

  if (v->size == v->capacity) {
    v->capacity *= 2;
    void **new_data = realloc(v->data, v->capacity * sizeof(void *));

    if (!new_data)
      return;

    v->data = new_data;
  }

  v->data[v->size++] = data;
}

void *vec_get(Vector *v, int index) {
  if (index < 0 || index >= v->size)
    return NULL;
  return v->data[index];
}

int vec_size(Vector *v) { return v->size; }

void vec_free(Vector *v) {
  free(v->data);
  free(v);
}
