#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// Libraries
#include <stddef.h>



/// This struct represents a HashTable (or rather a handle to it)
/// which the user can call functions on
typedef struct _HashTable HashTable;



/// This function initializes a `HashTable` and returns a handle to it.
HashTable *htab_init(void);


/// This function insert the address pointed to by `value` into the HashTable.
/// The key is a byte string, where `keylen` is the size of key in bytes.
/// The behavior is undefined, if `keylen` and `key` do not match
void htab_put(HashTable *ht, const char *key, const size_t keylen, void *value);


/// This function returns a pointer to the value that is associated with
/// `key`.
/// The behavior is undefined, if `keylen` and `key` do not match
void *htab_see(const HashTable *ht, const char *key, const size_t keylen);


/// This function cleans up the HashTable that was returned by `htab_init()`
/// and takes the Handle to the HashTable as a parameter
void htab_free(HashTable *ht);




#endif // HASH_TABLE_H
