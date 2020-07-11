#include "String.h"

#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

struct _String
{
    size_t length;
    size_t size;
    char arr[1];
};


bool String_append(String **darr, char val)
{
    struct _String *dynarray = (struct _String *) *darr;
    assert(dynarray != NULL);
    return String_insert(darr, val, dynarray->length);
}

String *String_create(size_t length)
{
    struct _String *dynarray = malloc(sizeof(struct _String) + sizeof(char) * (length - 1));
    if(dynarray == NULL)
        return NULL;

    dynarray->length = length;
    dynarray->size   = length;
    return dynarray;
}

void String_destroy(String *dynarray)
{
    free(dynarray);
}

bool String_insert(String **darr, char val, size_t index)
{
    struct _String *dynarray = (struct _String *) *darr;
    assert(dynarray != NULL && index <= dynarray->length);
    if(dynarray->length + 1 > dynarray->size) 
    {
        struct _String *realloced_dynarray = (struct _String *) realloc(dynarray, sizeof(struct _String) + dynarray->size * STRING_REALLOC_FACTOR * sizeof(char));
        if(realloced_dynarray == NULL)
            return false;

        dynarray = realloced_dynarray;
        dynarray->size *= STRING_REALLOC_FACTOR;
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

size_t String_length(String *darr)
{
    struct _String *dynarray = (struct _String *) darr;
    assert(dynarray != NULL); 
    return dynarray->length;
}

size_t String_size(String *darr)
{
    struct _String *dynarray = (struct _String *) darr;
    assert(dynarray != NULL); 
    return dynarray->size;
}


bool String_resize(String **darr, size_t size)
{
    struct _String *dynarray = (struct _String *) *darr;
    assert(dynarray != NULL); 
    struct _String *realloced_dynarray = (struct _String *) realloc(dynarray, sizeof(struct _String) + size * sizeof(char));
    if(realloced_dynarray == NULL)
        return false;

    dynarray = realloced_dynarray;
    dynarray->size = size;
    dynarray->length = dynarray->length > dynarray->size ? dynarray->size : dynarray->length;
    *darr = dynarray;
    return true;
}

char *String_arr(String *darr)
{
    struct _String *dynarray = (struct _String *) darr;
    assert(dynarray != NULL);   
    return dynarray->arr;
}

char String_get(String *darr, size_t index)
{
    struct _String *dynarray = (struct _String *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    return dynarray->arr[index];
}

void String_set(String *darr, size_t index, char val)
{
    struct _String *dynarray = (struct _String *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    dynarray->arr[index] = val;
}

bool String_adjust_length(String **darr, size_t length)
{
    struct _String *dynarray = (struct _String *) *darr;
    if(length > dynarray->size)
    {
        if(!String_resize(darr, length))
        {
            return false;
        }
        dynarray = (struct _String *) *darr;
    }
    dynarray->length = length;
    return true;
}

bool String_insert_array(String **darr, size_t start_index, char *arr, size_t arr_length)
{
    struct _String *dynarray = (struct _String *) *darr;
    assert(dynarray != NULL && start_index <= dynarray->length);
    size_t old_length = dynarray->length; 
    if(!String_adjust_length(darr, dynarray->length + arr_length))
        return false;

    dynarray = (struct _String *) *darr;
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

bool String_append_array(String **darr, char *arr, size_t arr_length)
{
    struct _String *dynarray = (struct _String *) *darr;
    assert(dynarray != NULL);
    return String_insert_array(darr, dynarray->length, arr, arr_length);     
}

bool String_insert_dynarray(String **dest, size_t start_index, String *src)
{
    struct _String *dynarray_src = (struct _String *) src;
    assert(dynarray_src != NULL);
    return String_insert_array(dest, start_index, dynarray_src->arr, dynarray_src->length); 
}

bool String_append_dynarray(String **dest, String *src)
{
    struct _String *dynarray_src = (struct _String *) src;
    assert(dynarray_src != NULL);
    return String_append_array(dest, dynarray_src->arr, dynarray_src->length); 
}

void String_remove(String *darr, size_t index)
{
    struct _String *dynarray = (struct _String *) darr;
    assert(dynarray != NULL && index < dynarray->length);
    for(size_t i = index; i < dynarray->length - 1; i++)
        dynarray->arr[i] = dynarray->arr[i + 1];
    dynarray->length--;    
}

void String_remove_slice(String *darr, size_t start, size_t end)
{
    struct _String *dynarray = (struct _String *) darr;
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

void String_foreach(String *darr, String_foreach_fp fp)
{
    struct _String *dynarray = (struct _String *) darr;
    assert(dynarray != NULL);  
    char *arr = dynarray->arr;
    for(size_t i = 0; i < dynarray->length; i++)
    {
        fp(arr[i]);
    }
}
