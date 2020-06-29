#include "dynarrayGen.h"

#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

struct dynarrayGen
{
    size_t length;
    size_t size;
    void * arr[1];
};


bool DynarrayGen_append(DynarrayGen *darr, void * val)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) *darr;
    assert(dynarray != NULL);
    return DynarrayGen_insert(darr, val, dynarray->length);
}

DynarrayGen DynarrayGen_create(size_t length)
{
    struct dynarrayGen *dynarray = malloc(sizeof(struct dynarrayGen) + sizeof(void *) * (length - 1));
    if(dynarray == NULL)
        return NULL;

    dynarray->length = length;
    dynarray->size   = length;
    return dynarray;
}

void DynarrayGen_destroy(DynarrayGen dynarray)
{
    free(dynarray);
}

bool DynarrayGen_insert(DynarrayGen *darr, void * val, size_t index)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) *darr;
    assert(dynarray != NULL && index <= dynarray->length);
    if(dynarray->length + 1 > dynarray->size) 
    {
        struct dynarrayGen *realloced_dynarray = (struct dynarrayGen *) realloc(dynarray, sizeof(struct dynarrayGen) + dynarray->size * DYNARRAY_REALLOC_FACTOR * sizeof(void *));
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

size_t DynarrayGen_length(DynarrayGen darr)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) darr;
    assert(dynarray != NULL); 
    return dynarray->length;
}

size_t DynarrayGen_size(DynarrayGen darr)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) darr;
    assert(dynarray != NULL); 
    return dynarray->size;
}


bool DynarrayGen_resize(DynarrayGen *darr, size_t size)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) *darr;
    assert(dynarray != NULL); 
    struct dynarrayGen *realloced_dynarray = (struct dynarrayGen *) realloc(dynarray, sizeof(struct dynarrayGen) + size * sizeof(void *));
    if(realloced_dynarray == NULL)
        return false;

    dynarray = realloced_dynarray;
    dynarray->size = size;
    dynarray->length = dynarray->length > dynarray->size ? dynarray->size : dynarray->length;
    *darr = dynarray;
    return true;
}

void * *DynarrayGen_arr(DynarrayGen darr)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) darr;
    assert(dynarray != NULL);   
    return dynarray->arr;
}

void * DynarrayGen_get(DynarrayGen darr, size_t index)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    return dynarray->arr[index];
}

void DynarrayGen_set(DynarrayGen darr, size_t index, void * val)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    dynarray->arr[index] = val;
}

bool DynarrayGen_adjust_length(DynarrayGen *darr, size_t length)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) *darr;
    if(length > dynarray->size)
    {
        if(!DynarrayGen_resize(darr, length))
        {
            return false;
        }
        dynarray = (struct dynarrayGen *) *darr;
    }
    dynarray->length = length;
    return true;
}

bool DynarrayGen_insert_array(DynarrayGen *darr, size_t start_index, void * *arr, size_t arr_length)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) *darr;
    assert(dynarray != NULL && start_index <= dynarray->length);
    size_t old_length = dynarray->length; 
    if(!DynarrayGen_adjust_length(darr, dynarray->length + arr_length))
        return false;

    dynarray = (struct dynarrayGen *) *darr;
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

bool DynarrayGen_append_array(DynarrayGen *darr, void * *arr, size_t arr_length)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) *darr;
    assert(dynarray != NULL);
    return DynarrayGen_insert_array(darr, dynarray->length, arr, arr_length);     
}

bool DynarrayGen_insert_dynarray(DynarrayGen *dest, size_t start_index, DynarrayGen src)
{
    struct dynarrayGen *dynarray_src = (struct dynarrayGen *) src;
    assert(dynarray_src != NULL);
    return DynarrayGen_insert_array(dest, start_index, dynarray_src->arr, dynarray_src->length); 
}

bool DynarrayGen_append_dynarray(DynarrayGen *dest, DynarrayGen src)
{
    struct dynarrayGen *dynarray_src = (struct dynarrayGen *) src;
    assert(dynarray_src != NULL);
    return DynarrayGen_append_array(dest, dynarray_src->arr, dynarray_src->length); 
}

void DynarrayGen_remove(DynarrayGen darr, size_t index)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) darr;
    assert(dynarray != NULL && index < dynarray->length);
    for(size_t i = index; i < dynarray->length - 1; i++)
        dynarray->arr[i] = dynarray->arr[i + 1];
    dynarray->length--;    
}

void DynarrayGen_remove_slice(DynarrayGen darr, size_t start, size_t end)
{
    struct dynarrayGen *dynarray = (struct dynarrayGen *) darr;
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
