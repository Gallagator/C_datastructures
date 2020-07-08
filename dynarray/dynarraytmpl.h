#ifndef <4>_H
#define <4>_H

#ifndef <4>_REALLOC_FACTOR
#define <4>_REALLOC_FACTOR 2
#endif

#include <stdbool.h>
#include <malloc.h>

typedef void *<0>;

// adds val to the end of the arr. true on success
bool <0>_append(<0> *darr, <1> val);
// creates a new dynarray with length and size of length
<0> <0>_create(size_t length);
// deallocates all memory used my dynarray
void <0>_destroy(<0> darr);
// inserts a value into the dynarray. true on success
bool <0>_insert(<0> *darr, <1> val, size_t index);
// gets length of dynarray
size_t <0>_length(<0> darr);
// gets size of dynarray
size_t <0>_size(<0> darr);
// changes the size that the dynarray takes. true on success
bool <0>_resize(<0> *darr, size_t size);
// gets the array data of the dynarray
<1> *<0>_arr(<0> darr);
// gets a value in the array at a particular index
<1> <0>_get(<0> darr, size_t index);
// sets a value in the array at a particular index
void <0>_set(<0> darr, size_t index, <1> val);
// changes length of the array. true on success
bool <0>_adjust_length(<0> *darr, size_t length);
// insert array at an index
bool <0>_insert_array(<0> *darr, size_t start_index, <1> *arr, size_t arr_length);
// appends array. just a wrapper for <0>_insert_array
bool <0>_append_array(<0> *darr, <1> *arr, size_t arr_length); 
// inserts a dynarray into another dynarray
bool <0>_insert_dynarray(<0> *dest, size_t start_index, <0> src);
// appends a dynarray -tests not done
bool <0>_append_dynarray(<0> *dest, <0> src);
// removes an element from dynarray
void <0>_remove(<0> darr, size_t index);
// removes slice of array. it removes elements from start up to but not including end 
void <0>_remove_slice(<0> darr, size_t start, size_t end);

#endif
