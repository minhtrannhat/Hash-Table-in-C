typedef struct
{
    char * key;
    char * value;
} ht_items;

typedef struct
{
    int size;
    int count;
    ht_items ** items;
} ht_hash_table;


