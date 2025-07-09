#ifndef LIST_H
#define LIST_H

// Libraries
#include <stddef.h>
#include <stdlib.h>



typedef struct _List  List;

List *list_init(size_t type_size);

void *list_storage(List *list);

size_t list_len(List *list);

void list_push(List *list, void *value);

void list_free(List *lst);




#endif // LIST_H
