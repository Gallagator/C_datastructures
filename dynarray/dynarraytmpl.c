#include "<3>.h"

#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

struct <2>
{
    size_t length;
    size_t size;
    <1> arr[1];
};


bool <0>_append(<0> *darr, <1> val)
{
    struct <2> *dynarray = (struct <2> *) *darr;
    assert(dynarray != NULL);
    return <0>_insert(darr, val, dynarray->length);
}

<0> <0>_create(size_t length)
{
    struct <2> *dynarray = malloc(sizeof(struct <2>) + sizeof(<1>) * (length - 1));
    if(dynarray == NULL)
        return NULL;

    dynarray->length = length;
    dynarray->size   = length;
    return dynarray;
}

void <0>_destroy(<0> dynarray)
{
    free(dynarray);
}

bool <0>_insert(<0> *darr, <1> val, size_t index)
{
    struct <2> *dynarray = (struct <2> *) *darr;
    assert(dynarray != NULL && index <= dynarray->length);
    if(dynarray->length + 1 > dynarray->size) 
    {
        struct <2> *realloced_dynarray = (struct <2> *) realloc(dynarray, sizeof(struct <2>) + dynarray->size * DYNARRAY_REALLOC_FACTOR * sizeof(<1>));
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

size_t <0>_length(<0> darr)
{
    struct <2> *dynarray = (struct <2> *) darr;
    assert(dynarray != NULL); 
    return dynarray->length;
}

size_t <0>_size(<0> darr)
{
    struct <2> *dynarray = (struct <2> *) darr;
    assert(dynarray != NULL); 
    return dynarray->size;
}


bool <0>_resize(<0> *darr, size_t size)
{
    struct <2> *dynarray = (struct <2> *) *darr;
    assert(dynarray != NULL); 
    struct <2> *realloced_dynarray = (struct <2> *) realloc(dynarray, sizeof(struct <2>) + size * sizeof(<1>));
    if(realloced_dynarray == NULL)
        return false;

    dynarray = realloced_dynarray;
    dynarray->size = size;
    dynarray->length = dynarray->length > dynarray->size ? dynarray->size : dynarray->length;
    *darr = dynarray;
    return true;
}

<1> *<0>_arr(<0> darr)
{
    struct <2> *dynarray = (struct <2> *) darr;
    assert(dynarray != NULL);   
    return dynarray->arr;
}

<1> <0>_get(<0> darr, size_t index)
{
    struct <2> *dynarray = (struct <2> *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    return dynarray->arr[index];
}

void <0>_set(<0> darr, size_t index, <1> val)
{
    struct <2> *dynarray = (struct <2> *) darr;
    assert(dynarray != NULL && index < dynarray->length);   
    dynarray->arr[index] = val;
}

bool <0>_adjust_length(<0> *darr, size_t length)
{
    struct <2> *dynarray = (struct <2> *) *darr;
    if(length > dynarray->size)
    {
        if(!<0>_resize(darr, length))
        {
            return false;
        }
        dynarray = (struct <2> *) *darr;
    }
    dynarray->length = length;
    return true;
}

bool <0>_insert_array(<0> *darr, size_t start_index, <1> *arr, size_t arr_length)
{
    struct <2> *dynarray = (struct <2> *) *darr;
    assert(dynarray != NULL && start_index <= dynarray->length);
    size_t old_length = dynarray->length; 
    if(!<0>_adjust_length(darr, dynarray->length + arr_length))
        return false;

    dynarray = (struct <2> *) *darr;
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

bool <0>_append_array(<0> *darr, <1> *arr, size_t arr_length)
{
    struct <2> *dynarray = (struct <2> *) *darr;
    assert(dynarray != NULL);
    return <0>_insert_array(darr, dynarray->length, arr, arr_length);     
}

bool <0>_insert_dynarray(<0> *dest, size_t start_index, <0> src)
{
    struct <2> *dynarray_src = (struct <2> *) src;
    assert(dynarray_src != NULL);
    return <0>_insert_array(dest, start_index, dynarray_src->arr, dynarray_src->length); 
}

bool <0>_append_dynarray(<0> *dest, <0> src)
{
    struct <2> *dynarray_src = (struct <2> *) src;
    assert(dynarray_src != NULL);
    return <0>_append_array(dest, dynarray_src->arr, dynarray_src->length); 
}

void <0>_remove(<0> darr, size_t index)
{
    struct <2> *dynarray = (struct <2> *) darr;
    assert(dynarray != NULL && index < dynarray->length);
    for(size_t i = index; i < dynarray->length - 1; i++)
        dynarray->arr[i] = dynarray->arr[i + 1];
    dynarray->length--;    
}

void <0>_remove_slice(<0> darr, size_t start, size_t end)
{
    struct <2> *dynarray = (struct <2> *) darr;
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
