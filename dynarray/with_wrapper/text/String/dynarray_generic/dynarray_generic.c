#include "dynarray_generic.h"

#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

struct _DynarrayGeneric
{
    size_t length;
    size_t size;
    void * arr[1];
};


bool DynarrayGeneric_append(DynarrayGeneric **darr, void * val)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) *darr;
    assert(dynarray != NULL);
    return DynarrayGeneric_insert(darr, val, dynarray->length);
}

DynarrayGeneric *DynarrayGeneric_create(size_t length)
{
    struct _DynarrayGeneric *dynarray = malloc(sizeof(struct _DynarrayGeneric) + sizeof(void *) * (length - 1));
    if(dynarray == NULL)
        return NULL;

    dynarray->length = length;
    dynarray->size   = length;
    return dynarray;
}

void DynarrayGeneric_destroy(DynarrayGeneric *dynarray)
{
    free(dynarray);
}

bool DynarrayGeneric_insert(DynarrayGeneric **darr, void * val, size_t index)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) *darr;
    assert(dynarray != NULL && index <= dynarray->length);
    if(dynarray->length + 1 > dynarray->size) 
    {
        struct _DynarrayGeneric *realloced_dynarray = (struct _DynarrayGeneric *) realloc(dynarray, sizeof(struct _DynarrayGeneric) + dynarray->size * DYNARRAY_GENERIC_REALLOC_FACTOR * sizeof(void *));
        if(realloced_dynarray == NULL)
            return false;

        dynarray = realloced_dynarray;
        dynarray->size *= DYNARRAY_GENERIC_REALLOC_FACTOR;
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

size_t DynarrayGeneric_length(DynarrayGeneric *darr)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) darr;
    assert(dynarray != NULL); 
    return dynarray->length;
}

size_t DynarrayGeneric_size(DynarrayGeneric *darr)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) darr;
    assert(dynarray != NULL); 
    return dynarray->size;
}


bool DynarrayGeneric_resize(DynarrayGeneric **darr, size_t size)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) *darr;
    assert(dynarray != NULL); 
    struct _DynarrayGeneric *realloced_dynarray = (struct _DynarrayGeneric *) realloc(dynarray, sizeof(struct _DynarrayGeneric) + size * sizeof(void *));
    if(realloced_dynarray == NULL)
        return false;

    dynarray = realloced_dynarray;
    dynarray->size = size;
    dynarray->length = dynarray->length > dynarray->size ? dynarray->size : dynarray->length;
    *darr = dynarray;
    return true;
}

void * *DynarrayGeneric_arr(DynarrayGeneric *darr)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) darr;
    assert(dynarray != NULL);   
    return dynarray->arr;
}

void * DynarrayGeneric_get(DynarrayGeneric *darr, size_t index)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    return dynarray->arr[index];
}

void DynarrayGeneric_set(DynarrayGeneric *darr, size_t index, void * val)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    dynarray->arr[index] = val;
}

bool DynarrayGeneric_adjust_length(DynarrayGeneric **darr, size_t length)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) *darr;
    if(length > dynarray->size)
    {
        if(!DynarrayGeneric_resize(darr, length))
        {
            return false;
        }
        dynarray = (struct _DynarrayGeneric *) *darr;
    }
    dynarray->length = length;
    return true;
}

bool DynarrayGeneric_insert_array(DynarrayGeneric **darr, size_t start_index, void * *arr, size_t arr_length)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) *darr;
    assert(dynarray != NULL && start_index <= dynarray->length);
    size_t old_length = dynarray->length; 
    if(!DynarrayGeneric_adjust_length(darr, dynarray->length + arr_length))
        return false;

    dynarray = (struct _DynarrayGeneric *) *darr;
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

bool DynarrayGeneric_append_array(DynarrayGeneric **darr, void * *arr, size_t arr_length)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) *darr;
    assert(dynarray != NULL);
    return DynarrayGeneric_insert_array(darr, dynarray->length, arr, arr_length);     
}

bool DynarrayGeneric_insert_dynarray(DynarrayGeneric **dest, size_t start_index, DynarrayGeneric *src)
{
    struct _DynarrayGeneric *dynarray_src = (struct _DynarrayGeneric *) src;
    assert(dynarray_src != NULL);
    return DynarrayGeneric_insert_array(dest, start_index, dynarray_src->arr, dynarray_src->length); 
}

bool DynarrayGeneric_append_dynarray(DynarrayGeneric **dest, DynarrayGeneric *src)
{
    struct _DynarrayGeneric *dynarray_src = (struct _DynarrayGeneric *) src;
    assert(dynarray_src != NULL);
    return DynarrayGeneric_append_array(dest, dynarray_src->arr, dynarray_src->length); 
}

void DynarrayGeneric_remove(DynarrayGeneric *darr, size_t index)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) darr;
    assert(dynarray != NULL && index < dynarray->length);
    for(size_t i = index; i < dynarray->length - 1; i++)
        dynarray->arr[i] = dynarray->arr[i + 1];
    dynarray->length--;    
}

void DynarrayGeneric_remove_slice(DynarrayGeneric *darr, size_t start, size_t end)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) darr;
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

void DynarrayGeneric_foreach(DynarrayGeneric *darr, DynarrayGeneric_foreach_fp fp)
{
    struct _DynarrayGeneric *dynarray = (struct _DynarrayGeneric *) darr;
    assert(dynarray != NULL);  
    void * *arr = dynarray->arr;
    for(size_t i = 0; i < dynarray->length; i++)
    {
        fp(arr[i]);
    }
}
