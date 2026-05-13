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

// Vector

typedef struct Vector Vector;

Vector *vec_create(void);
void vec_push(Vector *v, void *data);
void *vec_get(Vector *v, int index);
int vec_size(Vector *v);
void vec_free(Vector *v);

// HashMap

typedef struct HashMap HashMap;
HashMap *map_create(void);
void map_put(HashMap *map, const char *key, void *value);
void *map_get(HashMap *map, const char *key);
void map_delete(HashMap *map, const char *key);
void map_free(HashMap *map);
int map_count(HashMap *map);

#endif
