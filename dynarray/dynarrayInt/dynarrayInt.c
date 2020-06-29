#include "dynarrayInt.h"

#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

struct dynarrayInt
{
    size_t length;
    size_t size;
    int arr[1];
};


bool DynarrayInt_append(DynarrayInt *darr, int val)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) *darr;
    assert(dynarray != NULL);
    return DynarrayInt_insert(darr, val, dynarray->length);
}

DynarrayInt DynarrayInt_create(size_t length)
{
    struct dynarrayInt *dynarray = malloc(sizeof(struct dynarrayInt) + sizeof(int) * (length - 1));
    if(dynarray == NULL)
        return NULL;

    dynarray->length = length;
    dynarray->size   = length;
    return dynarray;
}

void DynarrayInt_destroy(DynarrayInt dynarray)
{
    free(dynarray);
}

bool DynarrayInt_insert(DynarrayInt *darr, int val, size_t index)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) *darr;
    assert(dynarray != NULL && index <= dynarray->length);
    if(dynarray->length + 1 > dynarray->size) 
    {
        struct dynarrayInt *realloced_dynarray = (struct dynarrayInt *) realloc(dynarray, sizeof(struct dynarrayInt) + dynarray->size * DYNARRAY_REALLOC_FACTOR * sizeof(int));
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

size_t DynarrayInt_length(DynarrayInt darr)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) darr;
    assert(dynarray != NULL); 
    return dynarray->length;
}

size_t DynarrayInt_size(DynarrayInt darr)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) darr;
    assert(dynarray != NULL); 
    return dynarray->size;
}


bool DynarrayInt_resize(DynarrayInt *darr, size_t size)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) *darr;
    assert(dynarray != NULL); 
    struct dynarrayInt *realloced_dynarray = (struct dynarrayInt *) realloc(dynarray, sizeof(struct dynarrayInt) + size * sizeof(int));
    if(realloced_dynarray == NULL)
        return false;

    dynarray = realloced_dynarray;
    dynarray->size = size;
    dynarray->length = dynarray->length > dynarray->size ? dynarray->size : dynarray->length;
    *darr = dynarray;
    return true;
}

int *DynarrayInt_arr(DynarrayInt darr)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) darr;
    assert(dynarray != NULL);   
    return dynarray->arr;
}

int DynarrayInt_get(DynarrayInt darr, size_t index)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    return dynarray->arr[index];
}

void DynarrayInt_set(DynarrayInt darr, size_t index, int val)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    dynarray->arr[index] = val;
}

bool DynarrayInt_adjust_length(DynarrayInt *darr, size_t length)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) *darr;
    if(length > dynarray->size)
    {
        if(!DynarrayInt_resize(darr, length))
        {
            return false;
        }
        dynarray = (struct dynarrayInt *) *darr;
    }
    dynarray->length = length;
    return true;
}

bool DynarrayInt_insert_array(DynarrayInt *darr, size_t start_index, int *arr, size_t arr_length)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) *darr;
    assert(dynarray != NULL && start_index <= dynarray->length);
    size_t old_length = dynarray->length; 
    if(!DynarrayInt_adjust_length(darr, dynarray->length + arr_length))
        return false;

    dynarray = (struct dynarrayInt *) *darr;
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

bool DynarrayInt_append_array(DynarrayInt *darr, int *arr, size_t arr_length)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) *darr;
    assert(dynarray != NULL);
    return DynarrayInt_insert_array(darr, dynarray->length, arr, arr_length);     
}

bool DynarrayInt_insert_dynarray(DynarrayInt *dest, size_t start_index, DynarrayInt src)
{
    struct dynarrayInt *dynarray_src = (struct dynarrayInt *) src;
    assert(dynarray_src != NULL);
    return DynarrayInt_insert_array(dest, start_index, dynarray_src->arr, dynarray_src->length); 
}

bool DynarrayInt_append_dynarray(DynarrayInt *dest, DynarrayInt src)
{
    struct dynarrayInt *dynarray_src = (struct dynarrayInt *) src;
    assert(dynarray_src != NULL);
    return DynarrayInt_append_array(dest, dynarray_src->arr, dynarray_src->length); 
}

void DynarrayInt_remove(DynarrayInt darr, size_t index)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) darr;
    assert(dynarray != NULL && index < dynarray->length);
    for(size_t i = index; i < dynarray->length - 1; i++)
        dynarray->arr[i] = dynarray->arr[i + 1];
    dynarray->length--;    
}

void DynarrayInt_remove_slice(DynarrayInt darr, size_t start, size_t end)
{
    struct dynarrayInt *dynarray = (struct dynarrayInt *) darr;
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
