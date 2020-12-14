typedef struct {
  char* key;
  char* value;
} ht_item;

typedef struct {
  int size;
  int count;
  ht_item** items;
} ht_hash_table;

ht_hash_table *ht_new();
void ht_del_hash_table(ht_hash_table *ht);
static ht_item *ht_new_item(const char *k, const char *v);
static void ht_del_item(ht_item *i);
static ht_item *ht_new_item(const char *k, const char *v);
static int ht_get_hash(const char *s, const int num_buckets, const int attempt);
void ht_insert(ht_hash_table *ht, const char *key, const char *value);
char *ht_search(ht_hash_table *ht, const char *key);
void ht_delete(ht_hash_table *ht, const char *key);
