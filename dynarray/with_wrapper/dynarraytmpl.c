#include "<3>.h"


bool <0>_append(<0> **darr, <1> val)
{
    return <2>_append( (<2> **) darr, (void *) val);
}
<0> *<0>_create(size_t length)
{
    return (<0>) <2>_create(length);
}
void <0>_destroy(<0> *darr)
{
    <2>_destroy( (<2> *) darr);
}
bool <0>_insert(<0> **darr, <1> val, size_t index)
{
    return <2>_insert( (<2> **) darr, (void *) val, index);
}
size_t <0>_length(<0> *darr)
{
    return <2>_length( (<2> *) darr);
}
size_t <0>_size(<0> *darr)
{
    return <2>_size( (<2> *) darr);
}
bool <0>_resize(<0> **darr, size_t size)
{
    return <2>_resize( (<2> **) darr, size);
}
<1> *<0>_arr(<0> *darr)
{
    return (<1> *) <2>_arr( (<2> *) darr);
}
<1> <0>_get(<0> *darr, size_t index)
{
    return (<1>) <2>_get( (<2> *) darr, index);
}

<1> *<0>_get_arr_reference(<0> *darr, size_t index)
{
    return (<1> *) <2>_get_arr_reference((<2> *) darr, index);
}

void <0>_set(<0> *darr, size_t index, <1> val)
{
    <2>_set( (<2> *) darr, index, (void *) val);
}
bool <0>_adjust_length(<0> **darr, size_t length)
{
    return <2>_adjust_length( (<2> **) darr, length);
}
bool <0>_insert_array(<0> **darr, size_t start_index, <1> *arr, size_t arr_length)
{
    return <2>_insert_array( (<2> **) darr, start_index, (void **) arr, arr_length);
}    

bool <0>_append_array(<0> **darr, <1> *arr, size_t arr_length)
{
    return <2>_append_array( (<2> **) darr, (void **) arr, arr_length);
} 
bool <0>_insert_dynarray(<0> **dest, size_t start_index, <0> *src)
{
    return <2>_insert_dynarray( (<2> **) dest, start_index, (<2> *) src);
}
bool <0>_append_dynarray(<0> **dest, <0> *src)
{
    return <2>_append_dynarray( (<2> **) dest, (<2> *) src);
}
<1> <0>_remove(<0> *darr, size_t index)
{
    return <2>_remove( (<2> *) darr, index);
}
void <0>_remove_slice(<0> *darr, size_t start, size_t end)
{
    <2>_remove_slice( (<2> *) darr, start, end);
}
void <0>_foreach(<0> *darr, <2>_foreach_fp fp)
{
    <2>_foreach( (<2> *) darr, fp);
}

void <0>_destroy_full(<0> *darr)
{
    <0>_foreach( (<2> *) darr, <1>_destroy);
    <0>_destroy(darr);
}

