#include <stdbool.h>
#include "test_utils.h"
#include "<3>.h"

bool arr_equals(<1> *a1, <1> *a2, size_t l1, size_t l2)
{
    if(l1 != l2)
        return false;
    for(size_t i = 0; i < l1; i++)
    {
        if(a1[i] != a2[i])
            return false;
    }
    return true;
}

int main()
{
    <0> dynarr = <0>_create(5);
    <0>_set(dynarr, 0, 'a');
    <0>_set(dynarr, 1, 'b');
    <0>_set(dynarr, 2, 'c');
    <0>_set(dynarr, 3, 'd');
    <0>_set(dynarr, 4, 'e');
    
    testbool(arr_equals(<0>_arr(dynarr), "abcde", <0>_size(dynarr), 5), "Set and creat work");
    testbool(<0>_get(dynarr, 2) == 'c', "dynarray_get works");
    
    <0>_insert(&dynarr, 'f', 5);
    testbool(arr_equals(<0>_arr(dynarr), "abcdef", <0>_length(dynarr), 6), "insert at end");

    size_t size = <0>_size(dynarr);
    
    <0>_insert(&dynarr, 'z', 3);
    testbool(size == <0>_size(dynarr) && arr_equals(<0>_arr(dynarr), "abczdef", DynarrayChar_length(dynarr), 7), "insert in middle");

    <0>_insert(&dynarr, 'y', 0);
    testbool(size == <0>_size(dynarr) && arr_equals(<0>_arr(dynarr), "yabczdef", DynarrayChar_length(dynarr), 8), "insert at start");

    <0>_resize(&dynarr, 20);
    testbool(arr_equals(<0>_arr(dynarr), "yabczdef", <0>_length(dynarr), 8), "resize to a larger size");

    <0>_resize(&dynarr, 4);
    testbool(arr_equals(<0>_arr(dynarr), "yabc", <0>_length(dynarr), 4), "resize to a smaller size");


    <0>_adjust_length(&dynarr, 6);
    <0>_set(dynarr, 4, 'd');
    <0>_set(dynarr, 5, 'e');
    testbool(arr_equals(<0>_arr(dynarr), "yabcde", <0>_length(dynarr), 6), "resize to larger length");

    <0>_adjust_length(&dynarr, 3);
    testbool(arr_equals(<0>_arr(dynarr), "yab", <0>_length(dynarr), 3), "resize to smaller length");

    <0>_insert_array(&dynarr, 0, "hello", 5); 
    testbool(arr_equals(<0>_arr(dynarr), "helloyab", <0>_length(dynarr), 8), "insert hello start");

    <0>_insert_array(&dynarr, 3, "A", 1); 
    testbool(arr_equals(<0>_arr(dynarr), "helAloyab", <0>_length(dynarr), 9), "inserting array of size 1 in the middle");

    <0>_insert_array(&dynarr, <0>_length(dynarr), "123", 3); 
    testbool(arr_equals(<0>_arr(dynarr), "helAloyab123", <0>_length(dynarr), 12), "adding to the end");

    <0> other = <0>_create(4);
    <0>_set(other, 0, 'z'); 
    <0>_set(other, 1, 'y'); 
    <0>_set(other, 2, 'x'); 
    <0>_set(other, 3, 'w'); 


    <0>_insert_dynarray(&other, 2, dynarr);
    testbool(arr_equals(<0>_arr(dynarr), "helAloyab123", <0>_length(dynarr), 12), "src dynarray unaltered");
    testbool(arr_equals(<0>_arr(other), "zyhelAloyab123xw", <0>_length(other), 16), "inserted into dynarray");

    <0>_append_dynarray(&other, dynarr);
    testbool(arr_equals(<0>_arr(other), "zyhelAloyab123xwhelAloyab123", <0>_length(other), 28), "appended to dynarray");

    <0>_remove(other, 0);
    testbool(arr_equals(<0>_arr(other), "yhelAloyab123xwhelAloyab123", <0>_length(other), 27), "removal from start");

    <0>_remove(other, <0>_length(other) - 1);
    testbool(arr_equals(<0>_arr(other), "yhelAloyab123xwhelAloyab12", <0>_length(other), 26), "removal from end");

    <0>_remove_slice(other, 1, 4);
    testbool(arr_equals(<0>_arr(other), "yAloyab123xwhelAloyab12", <0>_length(other), 23), "removal of small slice");
   
    <0>_remove_slice(other, 7, <0>_length(other));
    testbool(arr_equals(<0>_arr(other), "yAloyab", <0>_length(other), 7), "removal of end");
   
    <0>_remove_slice(other, 0, <0>_length(other));
    testbool(arr_equals(<0>_arr(other), "", <0>_length(other), 0), "total removal");
   

    // TODO test dynarray inserting functions    
    <0>_destroy(other);
    <0>_destroy(dynarr);
    return 0;
}

