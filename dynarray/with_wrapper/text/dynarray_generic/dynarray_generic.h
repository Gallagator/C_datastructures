#ifndef DYNARRAY_GENERIC_H
#define DYNARRAY_GENERIC_H

#ifndef DYNARRAY_GENERIC_REALLOC_FACTOR
#define DYNARRAY_GENERIC_REALLOC_FACTOR 2
#endif

#include <stdbool.h>
#include <malloc.h>

typedef void DynarrayGeneric;

// adds val to the end of the arr. true on success
bool DynarrayGeneric_append(DynarrayGeneric **darr, void * val);
// creates a new dynarray with length and size of length
DynarrayGeneric *DynarrayGeneric_create(size_t length);
// deallocates all memory used my dynarray
void DynarrayGeneric_destroy(DynarrayGeneric *darr);
// inserts a value into the dynarray. true on success
bool DynarrayGeneric_insert(DynarrayGeneric **darr, void * val, size_t index);
// gets length of dynarray
size_t DynarrayGeneric_length(DynarrayGeneric *darr);
// gets size of dynarray
size_t DynarrayGeneric_size(DynarrayGeneric *darr);
// changes the size that the dynarray takes. true on success
bool DynarrayGeneric_resize(DynarrayGeneric **darr, size_t size);
// gets the array data of the dynarray
void * *DynarrayGeneric_arr(DynarrayGeneric *darr);
// gets a value in the array at a particular index
void * DynarrayGeneric_get(DynarrayGeneric *darr, size_t index);
// sets a value in the array at a particular index
void DynarrayGeneric_set(DynarrayGeneric *darr, size_t index, void * val);
// changes length of the array. true on success
bool DynarrayGeneric_adjust_length(DynarrayGeneric **darr, size_t length);
// insert array at an index
bool DynarrayGeneric_insert_array(DynarrayGeneric **darr, size_t start_index, void * *arr, size_t arr_length);
// appends array. just a wrapper for DynarrayGeneric_insert_array
bool DynarrayGeneric_append_array(DynarrayGeneric **darr, void * *arr, size_t arr_length); 
// inserts a dynarray into another dynarray
bool DynarrayGeneric_insert_dynarray(DynarrayGeneric **dest, size_t start_index, DynarrayGeneric *src);
// appends a dynarray -tests not done
bool DynarrayGeneric_append_dynarray(DynarrayGeneric **dest, DynarrayGeneric *src);
// removes an element from dynarray
void DynarrayGeneric_remove(DynarrayGeneric *darr, size_t index);
// removes slice of array. it removes elements from start up to but not including end 
void DynarrayGeneric_remove_slice(DynarrayGeneric *darr, size_t start, size_t end);
// executes fp on each element up to the length of the dynarray
typedef void (*DynarrayGeneric_foreach_fp)(void * element);
void DynarrayGeneric_foreach(DynarrayGeneric *darr, DynarrayGeneric_foreach_fp fp);

#endif
