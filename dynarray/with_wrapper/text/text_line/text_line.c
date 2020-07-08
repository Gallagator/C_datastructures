#include "text_line.h"

#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

struct _TextLine
{
    size_t length;
    size_t size;
    char arr[1];
};


bool TextLine_append(TextLine *darr, char val)
{
    struct _TextLine *dynarray = (struct _TextLine *) *darr;
    assert(dynarray != NULL);
    return TextLine_insert(darr, val, dynarray->length);
}

TextLine TextLine_create(size_t length)
{
    struct _TextLine *dynarray = malloc(sizeof(struct _TextLine) + sizeof(char) * (length - 1));
    if(dynarray == NULL)
        return NULL;

    dynarray->length = length;
    dynarray->size   = length;
    return dynarray;
}

void TextLine_destroy(TextLine dynarray)
{
    free(dynarray);
}

bool TextLine_insert(TextLine *darr, char val, size_t index)
{
    struct _TextLine *dynarray = (struct _TextLine *) *darr;
    assert(dynarray != NULL && index <= dynarray->length);
    if(dynarray->length + 1 > dynarray->size) 
    {
        struct _TextLine *realloced_dynarray = (struct _TextLine *) realloc(dynarray, sizeof(struct _TextLine) + dynarray->size * TEXT_LINE_REALLOC_FACTOR * sizeof(char));
        if(realloced_dynarray == NULL)
            return false;

        dynarray = realloced_dynarray;
        dynarray->size *= TEXT_LINE_REALLOC_FACTOR;
        *darr = (void *) dynarray;
    } 
    size_t curr = dynarray->length;
    while(curr != index)
    {
       dynarray->arr[curr] = dynarray->arr[curr - 1]; 
       curr--;
    } 
    dynarray->arr[curr] = val;
    dynarray->length++;
    return true;
}

size_t TextLine_length(TextLine darr)
{
    struct _TextLine *dynarray = (struct _TextLine *) darr;
    assert(dynarray != NULL); 
    return dynarray->length;
}

size_t TextLine_size(TextLine darr)
{
    struct _TextLine *dynarray = (struct _TextLine *) darr;
    assert(dynarray != NULL); 
    return dynarray->size;
}


bool TextLine_resize(TextLine *darr, size_t size)
{
    struct _TextLine *dynarray = (struct _TextLine *) *darr;
    assert(dynarray != NULL); 
    struct _TextLine *realloced_dynarray = (struct _TextLine *) realloc(dynarray, sizeof(struct _TextLine) + size * sizeof(char));
    if(realloced_dynarray == NULL)
        return false;

    dynarray = realloced_dynarray;
    dynarray->size = size;
    dynarray->length = dynarray->length > dynarray->size ? dynarray->size : dynarray->length;
    *darr = dynarray;
    return true;
}

char *TextLine_arr(TextLine darr)
{
    struct _TextLine *dynarray = (struct _TextLine *) darr;
    assert(dynarray != NULL);   
    return dynarray->arr;
}

char TextLine_get(TextLine darr, size_t index)
{
    struct _TextLine *dynarray = (struct _TextLine *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    return dynarray->arr[index];
}

void TextLine_set(TextLine darr, size_t index, char val)
{
    struct _TextLine *dynarray = (struct _TextLine *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    dynarray->arr[index] = val;
}

bool TextLine_adjust_length(TextLine *darr, size_t length)
{
    struct _TextLine *dynarray = (struct _TextLine *) *darr;
    if(length > dynarray->size)
    {
        if(!TextLine_resize(darr, length))
        {
            return false;
        }
        dynarray = (struct _TextLine *) *darr;
    }
    dynarray->length = length;
    return true;
}

bool TextLine_insert_array(TextLine *darr, size_t start_index, char *arr, size_t arr_length)
{
    struct _TextLine *dynarray = (struct _TextLine *) *darr;
    assert(dynarray != NULL && start_index <= dynarray->length);
    size_t old_length = dynarray->length; 
    if(!TextLine_adjust_length(darr, dynarray->length + arr_length))
        return false;

    dynarray = (struct _TextLine *) *darr;
    size_t i = old_length;
    while(i > start_index)
    {
        i--;
        dynarray->arr[i + arr_length] = dynarray->arr[i];
    }        
    // we know i = start_index
    for(; i < start_index + arr_length; i++)
        dynarray->arr[i] = arr[i - start_index];

    return true;
}

bool TextLine_append_array(TextLine *darr, char *arr, size_t arr_length)
{
    struct _TextLine *dynarray = (struct _TextLine *) *darr;
    assert(dynarray != NULL);
    return TextLine_insert_array(darr, dynarray->length, arr, arr_length);     
}

bool TextLine_insert_dynarray(TextLine *dest, size_t start_index, TextLine src)
{
    struct _TextLine *dynarray_src = (struct _TextLine *) src;
    assert(dynarray_src != NULL);
    return TextLine_insert_array(dest, start_index, dynarray_src->arr, dynarray_src->length); 
}

bool TextLine_append_dynarray(TextLine *dest, TextLine src)
{
    struct _TextLine *dynarray_src = (struct _TextLine *) src;
    assert(dynarray_src != NULL);
    return TextLine_append_array(dest, dynarray_src->arr, dynarray_src->length); 
}

void TextLine_remove(TextLine darr, size_t index)
{
    struct _TextLine *dynarray = (struct _TextLine *) darr;
    assert(dynarray != NULL && index < dynarray->length);
    for(size_t i = index; i < dynarray->length - 1; i++)
        dynarray->arr[i] = dynarray->arr[i + 1];
    dynarray->length--;    
}

void TextLine_remove_slice(TextLine darr, size_t start, size_t end)
{
    struct _TextLine *dynarray = (struct _TextLine *) darr;
    assert(dynarray != NULL && start < dynarray->length &&
            end <= dynarray->length && end > start);
    size_t slice_size = end - start;
    size_t i;
    for(i = start; i < start + (dynarray->length - end); i++)
    {
        dynarray->arr[i] = dynarray->arr[i + slice_size];
    }
    dynarray->length = i;
}
