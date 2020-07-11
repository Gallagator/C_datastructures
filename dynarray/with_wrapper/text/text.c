#include "text.h"


bool Text_append(Text **darr, String * val)
{
    return DynarrayGeneric_append( (DynarrayGeneric **) darr, (void *) val);
}
Text *Text_create(size_t length)
{
    return (Text) DynarrayGeneric_create(length);
}
void Text_destroy(Text *darr)
{
    DynarrayGeneric_destroy( (DynarrayGeneric *) darr);
}
bool Text_insert(Text **darr, String * val, size_t index)
{
    return DynarrayGeneric_insert( (DynarrayGeneric **) darr, (void *) val, index);
}
size_t Text_length(Text *darr)
{
    return DynarrayGeneric_length( (DynarrayGeneric *) darr);
}
size_t Text_size(Text *darr)
{
    return DynarrayGeneric_size( (DynarrayGeneric *) darr);
}
bool Text_resize(Text **darr, size_t size)
{
    return DynarrayGeneric_resize( (DynarrayGeneric **) darr, size);
}
String * *Text_arr(Text *darr)
{
    return (String * *) DynarrayGeneric_arr( (DynarrayGeneric *) darr);
}
String * Text_get(Text *darr, size_t index)
{
    return (String *) DynarrayGeneric_get( (DynarrayGeneric *) darr, index);
}
void Text_set(Text *darr, size_t index, String * val)
{
    DynarrayGeneric_set( (DynarrayGeneric *) darr, index, (void *) val);
}
bool Text_adjust_length(Text **darr, size_t length)
{
    return DynarrayGeneric_adjust_length( (DynarrayGeneric **) darr, length);
}
bool Text_insert_array(Text **darr, size_t start_index, String * *arr, size_t arr_length)
{
    return DynarrayGeneric_insert_array( (DynarrayGeneric **) darr, start_index, (void **) arr, arr_length);
}    

bool Text_append_array(Text **darr, String * *arr, size_t arr_length)
{
    return DynarrayGeneric_append_array( (DynarrayGeneric **) darr, (void **) arr, arr_length);
} 
bool Text_insert_dynarray(Text **dest, size_t start_index, Text *src)
{
    return DynarrayGeneric_insert_dynarray( (DynarrayGeneric **) dest, start_index, (DynarrayGeneric *) src);
}
bool Text_append_dynarray(Text **dest, Text *src)
{
    return DynarrayGeneric_append_dynarray( (DynarrayGeneric **) dest, (DynarrayGeneric *) src);
}
void Text_remove(Text *darr, size_t index)
{
    DynarrayGeneric_remove( (DynarrayGeneric *) darr, index);
}
void Text_remove_slice(Text *darr, size_t start, size_t end)
{
    DynarrayGeneric_remove_slice( (DynarrayGeneric *) darr, start, end);
}
void Text_foreach(Text *darr, DynarrayGeneric_foreach_fp fp)
{
    DynarrayGeneric_foreach( (DynarrayGeneric *) darr, fp);
}

