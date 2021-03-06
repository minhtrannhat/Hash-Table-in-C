#include "./hash_table.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int HT_PRIME_1 = 151;
static const int HT_PRIME_2 = 163;

void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);

// HT_DELETED_ITEM is used to mark a bucket containing a deleted item
static ht_item HT_DELETED_ITEM = {NULL, NULL};

char *strdup(const char *src) {
  char *dst = malloc(strlen(src) + 1);  // Space for length plus nul
  if (dst == NULL) return NULL;         // No memory
  strcpy(dst, src);                     // Copy the characters
  return dst;                           // Return the new string
}

// Initialises a new hash table item containing a key and value
static ht_item *ht_new_item(const char *k, const char *v) {
  ht_item *i = malloc(sizeof(ht_item));

  i->key = strdup(k);
  i->value = strdup(v);

  return i;
}

// create a new hash table size of 100000
ht_hash_table *ht_new() {
  ht_hash_table *ht = malloc(sizeof(ht_hash_table));

  ht->size = 100000;
  ht->count = 0;
  ht->items = calloc((size_t)ht->size, sizeof(ht_item *));

  printf("New hash table created!\n");

  return ht;
}

// Deletes the ht_item i
static void ht_del_item(ht_item *i) {
  free(i->key);
  free(i->value);
  free(i);
}

// Deletes the hash table
void ht_del_hash_table(ht_hash_table *ht) {
  for (size_t i = 0; i < ht->size; i++) {
    ht_item *item = ht->items[i];

    if (item != NULL) {
      ht_del_item(item);
    }
  }

  free(ht->items);
  free(ht);

  printf("Hash table deleted!\n");
}

// Hash function
//
// Returns tha hash of 's', an int between 0 and 'm'
static unsigned int ht_hash(const char *s, const int a, const int m) {
  long hash = 0;
  const unsigned int len_s = strlen(s);

  for (size_t i = 0; i < len_s; i++) {
    hash += (long)pow(a, (double)len_s - (double)(i + 1)) * s[i];
    hash = hash % m;
  }

  return (int)hash;
}

static int ht_get_hash(const char *s, const int num_buckets,
                       const int attempt) {
  const unsigned int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
  const unsigned int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);

  return (int)(hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void ht_insert(ht_hash_table *ht, const char *key, const char *value) {
  ht_item *item = ht_new_item(key, value);

  int index = ht_get_hash(item->key, ht->size, 0);

  ht_item *cur_item = ht->items[index];

  int i = 1;

  while (cur_item != NULL) {
    if (cur_item != &HT_DELETED_ITEM) {
      if (strcmp(cur_item->key, key) == 0) {
        ht_del_item(cur_item);
        ht->items[index] = item;
        return;
      }
    }
    index = ht_get_hash(item->key, ht->size, i);
    cur_item = ht->items[index];
    i++;
  }

  ht->items[index] = item;
  ht->count++;
}

char *ht_search(ht_hash_table *ht, const char *key) {
  int index = ht_get_hash(key, ht->size, 0);

  ht_item *item = ht->items[index];

  int i = 1;

  while (item != NULL) {
    if (item != &HT_DELETED_ITEM) {
      if (strcmp(item->key, key) == 0) {
        return item->value;
      }
    }

    index = ht_get_hash(key, ht->size, i);
    item = ht->items[index];
    i++;
  }

  return NULL;
}

void ht_delete(ht_hash_table *ht, const char *key) {
  int index = ht_get_hash(key, ht->size, 0);
  ht_item *item = ht->items[index];

  int i = 1;
  while (item != NULL) {
    if (item != &HT_DELETED_ITEM) {
      if (strcmp(item->key, key) == 0) {
        ht_del_item(item);
        ht->items[index] = &HT_DELETED_ITEM;
      }
    }

    index = ht_get_hash(key, ht->size, i);
    item = ht->items[index];
    i++;
  }

  ht->count--;
}
