#ifndef DYNARRAY_H
#define DYNARRAY_H

#ifndef DYNARRAY_REALLOC_FACTOR
#define DYNARRAY_REALLOC_FACTOR 2
#endif

#include <stdbool.h>
#include <malloc.h>

typedef void *DynarrayInt;

// adds val to the end of the arr. true on success
bool DynarrayInt_append(DynarrayInt *darr, int val);
// creates a new dynarray with length and size of length
DynarrayInt DynarrayInt_create(size_t length);
// deallocates all memory used my dynarray
void DynarrayInt_destroy(DynarrayInt darr);
// inserts a value into the dynarray. true on success
bool DynarrayInt_insert(DynarrayInt *darr, int val, size_t index);
// gets length of dynarray
size_t DynarrayInt_length(DynarrayInt darr);
// gets size of dynarray
size_t DynarrayInt_size(DynarrayInt darr);
// changes the size that the dynarray takes. true on success
bool DynarrayInt_resize(DynarrayInt *darr, size_t size);
// gets the array data of the dynarray
int *DynarrayInt_arr(DynarrayInt darr);
// gets a value in the array at a particular index
int DynarrayInt_get(DynarrayInt darr, size_t index);
// sets a value in the array at a particular index
void DynarrayInt_set(DynarrayInt darr, size_t index, int val);
// changes length of the array. true on success
bool DynarrayInt_adjust_length(DynarrayInt *darr, size_t length);
// insert array at an index
bool DynarrayInt_insert_array(DynarrayInt *darr, size_t start_index, int *arr, size_t arr_length);
// appends array. just a wrapper for DynarrayInt_insert_array
bool DynarrayInt_append_array(DynarrayInt *darr, int *arr, size_t arr_length); 
// inserts a dynarray into another dynarray
bool DynarrayInt_insert_dynarray(DynarrayInt *dest, size_t start_index, DynarrayInt src);
// appends a dynarray -tests not done
bool DynarrayInt_append_dynarray(DynarrayInt *dest, DynarrayInt src);
// removes an element from dynarray
void DynarrayInt_remove(DynarrayInt darr, size_t index);
// removes slice of array. it removes elements from start up to but not including end 
void DynarrayInt_remove_slice(DynarrayInt darr, size_t start, size_t end);

#endif
