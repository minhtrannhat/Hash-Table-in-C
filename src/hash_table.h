// key-value pairs stored in a struct
typedef struct
{
    char * key;
    char * value;
}ht_items;

// hash table stores an array of pointers to items, and some details about its size and how full it is 
typedef struct
{
    int size;
    int count;
    ht_items ** items;
} ht_hash_table;


