#ifndef TEXT_LINE_H
#define TEXT_LINE_H

#ifndef TEXT_LINE_REALLOC_FACTOR
#define TEXT_LINE_REALLOC_FACTOR 2
#endif

#include <stdbool.h>
#include <malloc.h>

typedef void *TextLine;

// adds val to the end of the arr. true on success
bool TextLine_append(TextLine *darr, char val);
// creates a new dynarray with length and size of length
TextLine TextLine_create(size_t length);
// deallocates all memory used my dynarray
void TextLine_destroy(TextLine darr);
// inserts a value into the dynarray. true on success
bool TextLine_insert(TextLine *darr, char val, size_t index);
// gets length of dynarray
size_t TextLine_length(TextLine darr);
// gets size of dynarray
size_t TextLine_size(TextLine darr);
// changes the size that the dynarray takes. true on success
bool TextLine_resize(TextLine *darr, size_t size);
// gets the array data of the dynarray
char *TextLine_arr(TextLine darr);
// gets a value in the array at a particular index
char TextLine_get(TextLine darr, size_t index);
// sets a value in the array at a particular index
void TextLine_set(TextLine darr, size_t index, char val);
// changes length of the array. true on success
bool TextLine_adjust_length(TextLine *darr, size_t length);
// insert array at an index
bool TextLine_insert_array(TextLine *darr, size_t start_index, char *arr, size_t arr_length);
// appends array. just a wrapper for TextLine_insert_array
bool TextLine_append_array(TextLine *darr, char *arr, size_t arr_length); 
// inserts a dynarray into another dynarray
bool TextLine_insert_dynarray(TextLine *dest, size_t start_index, TextLine src);
// appends a dynarray -tests not done
bool TextLine_append_dynarray(TextLine *dest, TextLine src);
// removes an element from dynarray
void TextLine_remove(TextLine darr, size_t index);
// removes slice of array. it removes elements from start up to but not including end 
void TextLine_remove_slice(TextLine darr, size_t start, size_t end);

#endif
