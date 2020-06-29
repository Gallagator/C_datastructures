#include <stdbool.h>
#include "test_utils.h"
#include "dynarray.h"

bool arr_equals(char *a1, char *a2, size_t l1, size_t l2)
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
    DynarrayChar dynarr = dynarrayChar_create(5);
    dynarrayChar_set(dynarr, 0, 'a');
    dynarrayChar_set(dynarr, 1, 'b');
    dynarrayChar_set(dynarr, 2, 'c');
    dynarrayChar_set(dynarr, 3, 'd');
    dynarrayChar_set(dynarr, 4, 'e');
    
    testbool(arr_equals(dynarrayChar_arr(dynarr), "abcde", dynarrayChar_size(dynarr), 5), "Set and creat work");
    testbool(dynarrayChar_get(dynarr, 2) == 'c', "dynarray_get works");
    
    dynarrayChar_insert(&dynarr, 'f', 5);
    testbool(arr_equals(dynarrayChar_arr(dynarr), "abcdef", dynarrayChar_length(dynarr), 6), "insert at end");

    size_t size = dynarrayChar_size(dynarr);
    
    dynarrayChar_insert(&dynarr, 'z', 3);
    testbool(size == dynarrayChar_size(dynarr) && arr_equals(dynarrayChar_arr(dynarr), "abczdef", dynarrayChar_length(dynarr), 7), "insert in middle");

    dynarrayChar_insert(&dynarr, 'y', 0);
    testbool(size == dynarrayChar_size(dynarr) && arr_equals(dynarrayChar_arr(dynarr), "yabczdef", dynarrayChar_length(dynarr), 8), "insert at start");

    dynarrayChar_resize(&dynarr, 20);
    testbool(arr_equals(dynarrayChar_arr(dynarr), "yabczdef", dynarrayChar_length(dynarr), 8), "resize to a larger size");

    dynarrayChar_resize(&dynarr, 4);
    testbool(arr_equals(dynarrayChar_arr(dynarr), "yabc", dynarrayChar_length(dynarr), 4), "resize to a smaller size");


    dynarrayChar_adjust_length(&dynarr, 6);
    dynarrayChar_set(dynarr, 4, 'd');
    dynarrayChar_set(dynarr, 5, 'e');
    testbool(arr_equals(dynarrayChar_arr(dynarr), "yabcde", dynarrayChar_length(dynarr), 6), "resize to larger length");

    dynarrayChar_adjust_length(&dynarr, 3);
    testbool(arr_equals(dynarrayChar_arr(dynarr), "yab", dynarrayChar_length(dynarr), 3), "resize to smaller length");

    dynarrayChar_insert_array(&dynarr, 0, "hello", 5); 
    testbool(arr_equals(dynarrayChar_arr(dynarr), "helloyab", dynarrayChar_length(dynarr), 8), "insert hello start");

    dynarrayChar_insert_array(&dynarr, 3, "A", 1); 
    testbool(arr_equals(dynarrayChar_arr(dynarr), "helAloyab", dynarrayChar_length(dynarr), 9), "inserting array of size 1 in the middle");

    dynarrayChar_insert_array(&dynarr, dynarrayChar_length(dynarr), "123", 3); 
    testbool(arr_equals(dynarrayChar_arr(dynarr), "helAloyab123", dynarrayChar_length(dynarr), 12), "adding to the end");

    DynarrayChar other = dynarrayChar_create(4);
    dynarrayChar_set(other, 0, 'z'); 
    dynarrayChar_set(other, 1, 'y'); 
    dynarrayChar_set(other, 2, 'x'); 
    dynarrayChar_set(other, 3, 'w'); 


    dynarrayChar_insert_dynarray(&other, 2, dynarr);
    testbool(arr_equals(dynarrayChar_arr(dynarr), "helAloyab123", dynarrayChar_length(dynarr), 12), "src dynarray unaltered");
    testbool(arr_equals(dynarrayChar_arr(other), "zyhelAloyab123xw", dynarrayChar_length(other), 16), "inserted into dynarray");

    dynarrayChar_append_dynarray(&other, dynarr);
    testbool(arr_equals(dynarrayChar_arr(other), "zyhelAloyab123xwhelAloyab123", dynarrayChar_length(other), 28), "appended to dynarray");

    dynarrayChar_remove(other, 0);
    testbool(arr_equals(dynarrayChar_arr(other), "yhelAloyab123xwhelAloyab123", dynarrayChar_length(other), 27), "removal from start");

    dynarrayChar_remove(other, dynarrayChar_length(other) - 1);
    testbool(arr_equals(dynarrayChar_arr(other), "yhelAloyab123xwhelAloyab12", dynarrayChar_length(other), 26), "removal from end");

    dynarrayChar_remove_slice(other, 1, 4);
    testbool(arr_equals(dynarrayChar_arr(other), "yAloyab123xwhelAloyab12", dynarrayChar_length(other), 23), "removal of small slice");
   
    dynarrayChar_remove_slice(other, 7, dynarrayChar_length(other));
    testbool(arr_equals(dynarrayChar_arr(other), "yAloyab", dynarrayChar_length(other), 7), "removal of end");
   
    dynarrayChar_remove_slice(other, 0, dynarrayChar_length(other));
    testbool(arr_equals(dynarrayChar_arr(other), "", dynarrayChar_length(other), 0), "total removal");
   

    // TODO test dynarray inserting functions    
    dynarrayChar_destroy(other);
    dynarrayChar_destroy(dynarr);
    return 0;
}

