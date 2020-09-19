#ifndef TEXT_H
#define TEXT_H

#ifndef TEXT_REALLOC_FACTOR
#define TEXT_REALLOC_FACTOR 2
#endif

#include <stdbool.h>
#include <malloc.h>

#include "String/String.h"
#include "dynarray_generic/dynarray_generic.h"

typedef void *Text;

// adds val to the end of the arr. true on success
bool Text_append(Text **darr, String * val);
// creates a new dynarray with length and size of length
Text *Text_create(size_t length);
// deallocates all memory used my dynarray
void Text_destroy(Text *darr);
// inserts a value into the dynarray. true on success
bool Text_insert(Text **darr, String * val, size_t index);
// gets length of dynarray
size_t Text_length(Text *darr);
// gets size of dynarray
size_t Text_size(Text *darr);
// changes the size that the dynarray takes. true on success
bool Text_resize(Text **darr, size_t size);
// gets the array data of the dynarray
String * *Text_arr(Text *darr);
// gets a value in the array at a particular index
String * Text_get(Text *darr, size_t index);
// gets the reference of the array data
String * *Text_get_arr_reference(Text *darr, size_t index);
// sets a value in the array at a particular index
void Text_set(Text *darr, size_t index, String * val);
// changes length of the array. true on success
bool Text_adjust_length(Text **darr, size_t length);
// insert array at an index
bool Text_insert_array(Text **darr, size_t start_index, String * *arr, size_t arr_length);
// appends array. just a wrapper for Text_insert_array
bool Text_append_array(Text **darr, String * *arr, size_t arr_length); 
// inserts a dynarray into another dynarray
bool Text_insert_dynarray(Text **dest, size_t start_index, Text *src);
// appends a dynarray -tests not done
bool Text_append_dynarray(Text **dest, Text *src);
// removes an element from dynarray
void Text_remove(Text *darr, size_t index);
// removes slice of array. it removes elements from start up to but not including end 
void Text_remove_slice(Text *darr, size_t start, size_t end);
// executes fp on each element up to the length of the dynarray
void Text_foreach(Text *darr, DynarrayGeneric_foreach_fp fp);
// runs destroy on the all data being held
void Text_destroy_full(Text *darr);

#endif
