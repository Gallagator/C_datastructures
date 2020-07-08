#ifndef TEXT_H
#define TEXT_H

#ifndef TEXT_REALLOC_FACTOR
#define TEXT_REALLOC_FACTOR 2
#endif

#include <stdbool.h>
#include <malloc.h>

#include "text_line/text_line.h"
#include "../dynarray_generic/dynarray_generic.h"

typedef void *Text;

// adds val to the end of the arr. true on success
bool Text_append(Text *darr, TextLine val);
// creates a new dynarray with length and size of length
Text Text_create(size_t length);
// deallocates all memory used my dynarray
void Text_destroy(Text darr);
// inserts a value into the dynarray. true on success
bool Text_insert(Text *darr, TextLine val, size_t index);
// gets length of dynarray
size_t Text_length(Text darr);
// gets size of dynarray
size_t Text_size(Text darr);
// changes the size that the dynarray takes. true on success
bool Text_resize(Text *darr, size_t size);
// gets the array data of the dynarray
TextLine *Text_arr(Text darr);
// gets a value in the array at a particular index
TextLine Text_get(Text darr, size_t index);
// sets a value in the array at a particular index
void Text_set(Text darr, size_t index, TextLine val);
// changes length of the array. true on success
bool Text_adjust_length(Text *darr, size_t length);
// insert array at an index
bool Text_insert_array(Text *darr, size_t start_index, TextLine *arr, size_t arr_length);
// appends array. just a wrapper for Text_insert_array
bool Text_append_array(Text *darr, TextLine *arr, size_t arr_length); 
// inserts a dynarray into another dynarray
bool Text_insert_dynarray(Text *dest, size_t start_index, Text src);
// appends a dynarray -tests not done
bool Text_append_dynarray(Text *dest, Text src);
// removes an element from dynarray
void Text_remove(Text darr, size_t index);
// removes slice of array. it removes elements from start up to but not including end 
void Text_remove_slice(Text darr, size_t start, size_t end);

#endif
