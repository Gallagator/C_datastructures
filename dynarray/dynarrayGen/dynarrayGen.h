#ifndef DYNARRAY_H
#define DYNARRAY_H

#ifndef DYNARRAY_REALLOC_FACTOR
#define DYNARRAY_REALLOC_FACTOR 2
#endif

#include <stdbool.h>
#include <malloc.h>

typedef void *DynarrayGen;

// adds val to the end of the arr. true on success
bool DynarrayGen_append(DynarrayGen *darr, void * val);
// creates a new dynarray with length and size of length
DynarrayGen DynarrayGen_create(size_t length);
// deallocates all memory used my dynarray
void DynarrayGen_destroy(DynarrayGen darr);
// inserts a value into the dynarray. true on success
bool DynarrayGen_insert(DynarrayGen *darr, void * val, size_t index);
// gets length of dynarray
size_t DynarrayGen_length(DynarrayGen darr);
// gets size of dynarray
size_t DynarrayGen_size(DynarrayGen darr);
// changes the size that the dynarray takes. true on success
bool DynarrayGen_resize(DynarrayGen *darr, size_t size);
// gets the array data of the dynarray
void * *DynarrayGen_arr(DynarrayGen darr);
// gets a value in the array at a particular index
void * DynarrayGen_get(DynarrayGen darr, size_t index);
// sets a value in the array at a particular index
void DynarrayGen_set(DynarrayGen darr, size_t index, void * val);
// changes length of the array. true on success
bool DynarrayGen_adjust_length(DynarrayGen *darr, size_t length);
// insert array at an index
bool DynarrayGen_insert_array(DynarrayGen *darr, size_t start_index, void * *arr, size_t arr_length);
// appends array. just a wrapper for DynarrayGen_insert_array
bool DynarrayGen_append_array(DynarrayGen *darr, void * *arr, size_t arr_length); 
// inserts a dynarray into another dynarray
bool DynarrayGen_insert_dynarray(DynarrayGen *dest, size_t start_index, DynarrayGen src);
// appends a dynarray -tests not done
bool DynarrayGen_append_dynarray(DynarrayGen *dest, DynarrayGen src);
// removes an element from dynarray
void DynarrayGen_remove(DynarrayGen darr, size_t index);
// removes slice of array. it removes elements from start up to but not including end 
void DynarrayGen_remove_slice(DynarrayGen darr, size_t start, size_t end);

#endif
