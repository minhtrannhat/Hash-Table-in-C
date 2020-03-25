#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"

char * strdup(const char *src) {
    char *dst = malloc(strlen (src) + 1);  // Space for length plus nul
    if (dst == NULL) return NULL;          // No memory
    strcpy(dst, src);                      // Copy the characters
    return dst;                            // Return the new string
}

static ht_items * ht_new_item(const char * k, const char * v)
{
    ht_items * i = malloc(sizeof(ht_items));
    
    i -> key = strdup(k);
    i -> value = strdup(v);

    return i;
}

ht_hash_table * ht_new()
{
    ht_hash_table * ht = malloc(sizeof(ht_hash_table));
    
    ht -> size = 53;
    ht -> count = 0;
    ht -> items = calloc( (size_t) ht -> size, sizeof(ht_items *) );

    return ht;
}

static void ht_del_item(ht_items * i)
{
    free(i -> key);
    free(i -> value);
    free(i);
}

void ht_del_hash_table(ht_hash_table * ht)
{
    for (size_t i = 0; i < ht -> size; i++)
    {
        ht_items * item = ht -> items[i];

        if (item != NULL)
        {
            ht_del_item(item);
        }
    }

    free(ht -> items);
    free(ht);
}

static int ht_hash(const char * s, const int a, const int m)
{
    long hash = 0;
    const int len_s = strlen(s);
    
    for(size_t i = 0; i < len_s; i++)
    {
        hash += (long) pow(a, len_s - (i + 1)) * s[i];
        hash = hash % m;
    }

    return (int) hash;
}

static int ht_get_hash(
        const char * s, const int num_buckets, const int attempt
        )
{
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);

    return ( hash_a + (attempt * (hash_b + 1))) % num_buckets;
}
