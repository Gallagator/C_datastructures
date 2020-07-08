#ifndef DYNARRAYCHAR_H
#define DYNARRAYCHAR_H

#ifndef DYNARRAYCHAR_REALLOC_FACTOR
#define DYNARRAYCHAR_REALLOC_FACTOR 2
#endif

#include <stdbool.h>
#include <malloc.h>

typedef void *DynarrayChar;

// adds val to the end of the arr. true on success
bool DynarrayChar_append(DynarrayChar *darr, char val);
// creates a new dynarray with length and size of length
DynarrayChar DynarrayChar_create(size_t length);
// deallocates all memory used my dynarray
void DynarrayChar_destroy(DynarrayChar darr);
// inserts a value into the dynarray. true on success
bool DynarrayChar_insert(DynarrayChar *darr, char val, size_t index);
// gets length of dynarray
size_t DynarrayChar_length(DynarrayChar darr);
// gets size of dynarray
size_t DynarrayChar_size(DynarrayChar darr);
// changes the size that the dynarray takes. true on success
bool DynarrayChar_resize(DynarrayChar *darr, size_t size);
// gets the array data of the dynarray
char *DynarrayChar_arr(DynarrayChar darr);
// gets a value in the array at a particular index
char DynarrayChar_get(DynarrayChar darr, size_t index);
// sets a value in the array at a particular index
void DynarrayChar_set(DynarrayChar darr, size_t index, char val);
// changes length of the array. true on success
bool DynarrayChar_adjust_length(DynarrayChar *darr, size_t length);
// insert array at an index
bool DynarrayChar_insert_array(DynarrayChar *darr, size_t start_index, char *arr, size_t arr_length);
// appends array. just a wrapper for DynarrayChar_insert_array
bool DynarrayChar_append_array(DynarrayChar *darr, char *arr, size_t arr_length); 
// inserts a dynarray into another dynarray
bool DynarrayChar_insert_dynarray(DynarrayChar *dest, size_t start_index, DynarrayChar src);
// appends a dynarray -tests not done
bool DynarrayChar_append_dynarray(DynarrayChar *dest, DynarrayChar src);
// removes an element from dynarray
void DynarrayChar_remove(DynarrayChar darr, size_t index);
// removes slice of array. it removes elements from start up to but not including end 
void DynarrayChar_remove_slice(DynarrayChar darr, size_t start, size_t end);

#endif
