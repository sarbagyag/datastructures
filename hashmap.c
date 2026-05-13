#include "ds.h"
#include <_strings.h>
#include <string.h>

#define BUCKET_COUNT 64

typedef struct Entry {
  char *key;
  void *value;
  struct Entry *next;
} Entry;

typedef struct HashMap {
  Entry **buckets; // Points to the Array of Entry Pointers //Basically we are
                   // storing the head of the linked list in the Buckets.
                   // (Perfect Mental Model)
  int size;
  int count;
} HashMap;

static unsigned int hash(const char *key) {
  unsigned int h = 5381;

  int c;

  while (*key !=
         '\0') { // Dereferencing the key and checking the end of the line
    c = *key;    // Dereferencing the key again and storing in c
    key++;       // Advancing the Key Pointer
    h = ((h << 5) + h) + c;
  }

  // Alternatively we can also write:
  // while ((c = *key++))
  //{
  // h=((h<<5)+h) + c;
  // }

  return h % BUCKET_COUNT;
}

HashMap *map_create(void) {
  HashMap *map = malloc(sizeof(HashMap));

  if (!map)
    return NULL;

  map->buckets = calloc(
      BUCKET_COUNT,
      sizeof(Entry *)); // Note that we are using calloc instead of malloc
  // Why zero initialization? -> Because all Bucket Pointers start as NULL(zero)
  // with calloc. Without calloc, buckets contains garbage and random addresses
  // aka with malloc

  if (!map->buckets) {
    free(map);
    return NULL;
  }

  map->size = BUCKET_COUNT;
  map->count = 0;
  return map;
}

void map_put(HashMap *map, const char *key, void *value) {
  unsigned int index = hash(key);

  Entry *curr = map->buckets[index];

  // check if key already exists

  while (curr) {
    if (strcmp(curr->key, key) == 0) {
      curr->value = value;
      return;
    }
    curr = curr->next;
  }

  Entry *entry = malloc(sizeof(Entry));

  if (!entry)
    return;

  // Ownership difference between the Key and value
  // Both Key and Value comes from the Caller, but their lifetimes differ
  // Value -> Caller knows when to free it, they created it, they will manage
  // it. Key -> We need it to survive indefinitely inside the hashmap for
  // lookups, we cant't control the caller's string lifetime.
  //

  entry->key = malloc(strlen(key) + 1);

  if (!entry->key) {
    free(entry);
    return;
  }

  strcpy(entry->key, key);

  entry->value = value;
  entry->next = map->buckets[index];
  map->buckets[index] = entry;
  map->count++;
}

void *map_get(HashMap *map, const char *key) {
  unsigned int index = hash(key);

  Entry *curr = map->buckets[index];

  while (curr) {
    if (strcmp(curr->key, key) == 0) {
      return curr->value;
    }
    curr = curr->next;
  }
  return NULL;
}

void map_delete(HashMap *map, const char *key) {

  unsigned int index = hash(key);

  Entry *curr = map->buckets[index];
  Entry *prev = NULL;

  while (curr) {
    if (strcmp(curr->key, key) == 0) {
      if (prev) {
        prev->next = curr->next;
      } else {
        map->buckets[index] = curr->next;
      }

      free(curr->key);
      free(curr);
      map->count--;
      return;
    }
    prev = curr;
    curr = curr->next;
  }
}

void map_free(HashMap *map) {
  for (int i = 0; i < map->size; i++) {
    Entry *curr = map->buckets[i];

    while (curr) {
      Entry *next = curr->next;
      free(curr->key);
      free(curr);
      curr = next;
    }
  }
  free(map->buckets);
  free(map);
}

int map_count(HashMap *map) { return map->count; }

// Rule of thumb for Stack and Heap Value
//  USE STACK WHEN:
//   1. Small, fixed size data, 2. Only needed within current function, 3.
//   Temporary and Short Lived.
//
//  USE HEAP WHEN:
//   1. Needs to outlive the current function, 2. Size unknown at compile
//   time, 3. Large Data, 4. Shared between multiple parts of the program.
