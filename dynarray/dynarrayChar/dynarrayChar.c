#include "dynarrayChar.h"

#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

struct dynarrayChar
{
    size_t length;
    size_t size;
    char arr[1];
};


bool DynarrayChar_append(DynarrayChar *darr, char val)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) *darr;
    assert(dynarray != NULL);
    return DynarrayChar_insert(darr, val, dynarray->length);
}

DynarrayChar DynarrayChar_create(size_t length)
{
    struct dynarrayChar *dynarray = malloc(sizeof(struct dynarrayChar) + sizeof(char) * (length - 1));
    if(dynarray == NULL)
        return NULL;

    dynarray->length = length;
    dynarray->size   = length;
    return dynarray;
}

void DynarrayChar_destroy(DynarrayChar dynarray)
{
    free(dynarray);
}

bool DynarrayChar_insert(DynarrayChar *darr, char val, size_t index)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) *darr;
    assert(dynarray != NULL && index <= dynarray->length);
    if(dynarray->length + 1 > dynarray->size) 
    {
        struct dynarrayChar *realloced_dynarray = (struct dynarrayChar *) realloc(dynarray, sizeof(struct dynarrayChar) + dynarray->size * DYNARRAY_REALLOC_FACTOR * sizeof(char));
        if(realloced_dynarray == NULL)
            return false;

        dynarray = realloced_dynarray;
        dynarray->size *= DYNARRAY_REALLOC_FACTOR;
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

size_t DynarrayChar_length(DynarrayChar darr)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) darr;
    assert(dynarray != NULL); 
    return dynarray->length;
}

size_t DynarrayChar_size(DynarrayChar darr)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) darr;
    assert(dynarray != NULL); 
    return dynarray->size;
}


bool DynarrayChar_resize(DynarrayChar *darr, size_t size)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) *darr;
    assert(dynarray != NULL); 
    struct dynarrayChar *realloced_dynarray = (struct dynarrayChar *) realloc(dynarray, sizeof(struct dynarrayChar) + size * sizeof(char));
    if(realloced_dynarray == NULL)
        return false;

    dynarray = realloced_dynarray;
    dynarray->size = size;
    dynarray->length = dynarray->length > dynarray->size ? dynarray->size : dynarray->length;
    *darr = dynarray;
    return true;
}

char *DynarrayChar_arr(DynarrayChar darr)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) darr;
    assert(dynarray != NULL);   
    return dynarray->arr;
}

char DynarrayChar_get(DynarrayChar darr, size_t index)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    return dynarray->arr[index];
}

void DynarrayChar_set(DynarrayChar darr, size_t index, char val)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    dynarray->arr[index] = val;
}

bool DynarrayChar_adjust_length(DynarrayChar *darr, size_t length)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) *darr;
    if(length > dynarray->size)
    {
        if(!DynarrayChar_resize(darr, length))
        {
            return false;
        }
        dynarray = (struct dynarrayChar *) *darr;
    }
    dynarray->length = length;
    return true;
}

bool DynarrayChar_insert_array(DynarrayChar *darr, size_t start_index, char *arr, size_t arr_length)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) *darr;
    assert(dynarray != NULL && start_index <= dynarray->length);
    size_t old_length = dynarray->length; 
    if(!DynarrayChar_adjust_length(darr, dynarray->length + arr_length))
        return false;

    dynarray = (struct dynarrayChar *) *darr;
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

bool DynarrayChar_append_array(DynarrayChar *darr, char *arr, size_t arr_length)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) *darr;
    assert(dynarray != NULL);
    return DynarrayChar_insert_array(darr, dynarray->length, arr, arr_length);     
}

bool DynarrayChar_insert_dynarray(DynarrayChar *dest, size_t start_index, DynarrayChar src)
{
    struct dynarrayChar *dynarray_src = (struct dynarrayChar *) src;
    assert(dynarray_src != NULL);
    return DynarrayChar_insert_array(dest, start_index, dynarray_src->arr, dynarray_src->length); 
}

bool DynarrayChar_append_dynarray(DynarrayChar *dest, DynarrayChar src)
{
    struct dynarrayChar *dynarray_src = (struct dynarrayChar *) src;
    assert(dynarray_src != NULL);
    return DynarrayChar_append_array(dest, dynarray_src->arr, dynarray_src->length); 
}

void DynarrayChar_remove(DynarrayChar darr, size_t index)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) darr;
    assert(dynarray != NULL && index < dynarray->length);
    for(size_t i = index; i < dynarray->length - 1; i++)
        dynarray->arr[i] = dynarray->arr[i + 1];
    dynarray->length--;    
}

void DynarrayChar_remove_slice(DynarrayChar darr, size_t start, size_t end)
{
    struct dynarrayChar *dynarray = (struct dynarrayChar *) darr;
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
