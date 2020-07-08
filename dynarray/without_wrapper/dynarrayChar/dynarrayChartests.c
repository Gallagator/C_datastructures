#include <stdbool.h>
#include "test_utils.h"
#include "dynarrayChar.h"

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
    DynarrayChar dynarr = DynarrayChar_create(5);
    DynarrayChar_set(dynarr, 0, 'a');
    DynarrayChar_set(dynarr, 1, 'b');
    DynarrayChar_set(dynarr, 2, 'c');
    DynarrayChar_set(dynarr, 3, 'd');
    DynarrayChar_set(dynarr, 4, 'e');
    
    testbool(arr_equals(DynarrayChar_arr(dynarr), "abcde", DynarrayChar_size(dynarr), 5), "Set and creat work");
    testbool(DynarrayChar_get(dynarr, 2) == 'c', "dynarray_get works");
    
    DynarrayChar_insert(&dynarr, 'f', 5);
    testbool(arr_equals(DynarrayChar_arr(dynarr), "abcdef", DynarrayChar_length(dynarr), 6), "insert at end");

    size_t size = DynarrayChar_size(dynarr);
    
    DynarrayChar_insert(&dynarr, 'z', 3);
    testbool(size == DynarrayChar_size(dynarr) && arr_equals(DynarrayChar_arr(dynarr), "abczdef", DynarrayChar_length(dynarr), 7), "insert in middle");

    DynarrayChar_insert(&dynarr, 'y', 0);
    testbool(size == DynarrayChar_size(dynarr) && arr_equals(DynarrayChar_arr(dynarr), "yabczdef", DynarrayChar_length(dynarr), 8), "insert at start");

    DynarrayChar_resize(&dynarr, 20);
    testbool(arr_equals(DynarrayChar_arr(dynarr), "yabczdef", DynarrayChar_length(dynarr), 8), "resize to a larger size");

    DynarrayChar_resize(&dynarr, 4);
    testbool(arr_equals(DynarrayChar_arr(dynarr), "yabc", DynarrayChar_length(dynarr), 4), "resize to a smaller size");


    DynarrayChar_adjust_length(&dynarr, 6);
    DynarrayChar_set(dynarr, 4, 'd');
    DynarrayChar_set(dynarr, 5, 'e');
    testbool(arr_equals(DynarrayChar_arr(dynarr), "yabcde", DynarrayChar_length(dynarr), 6), "resize to larger length");

    DynarrayChar_adjust_length(&dynarr, 3);
    testbool(arr_equals(DynarrayChar_arr(dynarr), "yab", DynarrayChar_length(dynarr), 3), "resize to smaller length");

    DynarrayChar_insert_array(&dynarr, 0, "hello", 5); 
    testbool(arr_equals(DynarrayChar_arr(dynarr), "helloyab", DynarrayChar_length(dynarr), 8), "insert hello start");

    DynarrayChar_insert_array(&dynarr, 3, "A", 1); 
    testbool(arr_equals(DynarrayChar_arr(dynarr), "helAloyab", DynarrayChar_length(dynarr), 9), "inserting array of size 1 in the middle");

    DynarrayChar_insert_array(&dynarr, DynarrayChar_length(dynarr), "123", 3); 
    testbool(arr_equals(DynarrayChar_arr(dynarr), "helAloyab123", DynarrayChar_length(dynarr), 12), "adding to the end");

    DynarrayChar other = DynarrayChar_create(4);
    DynarrayChar_set(other, 0, 'z'); 
    DynarrayChar_set(other, 1, 'y'); 
    DynarrayChar_set(other, 2, 'x'); 
    DynarrayChar_set(other, 3, 'w'); 


    DynarrayChar_insert_dynarray(&other, 2, dynarr);
    testbool(arr_equals(DynarrayChar_arr(dynarr), "helAloyab123", DynarrayChar_length(dynarr), 12), "src dynarray unaltered");
    testbool(arr_equals(DynarrayChar_arr(other), "zyhelAloyab123xw", DynarrayChar_length(other), 16), "inserted into dynarray");

    DynarrayChar_append_dynarray(&other, dynarr);
    testbool(arr_equals(DynarrayChar_arr(other), "zyhelAloyab123xwhelAloyab123", DynarrayChar_length(other), 28), "appended to dynarray");

    DynarrayChar_remove(other, 0);
    testbool(arr_equals(DynarrayChar_arr(other), "yhelAloyab123xwhelAloyab123", DynarrayChar_length(other), 27), "removal from start");

    DynarrayChar_remove(other, DynarrayChar_length(other) - 1);
    testbool(arr_equals(DynarrayChar_arr(other), "yhelAloyab123xwhelAloyab12", DynarrayChar_length(other), 26), "removal from end");

    DynarrayChar_remove_slice(other, 1, 4);
    testbool(arr_equals(DynarrayChar_arr(other), "yAloyab123xwhelAloyab12", DynarrayChar_length(other), 23), "removal of small slice");
   
    DynarrayChar_remove_slice(other, 7, DynarrayChar_length(other));
    testbool(arr_equals(DynarrayChar_arr(other), "yAloyab", DynarrayChar_length(other), 7), "removal of end");
   
    DynarrayChar_remove_slice(other, 0, DynarrayChar_length(other));
    testbool(arr_equals(DynarrayChar_arr(other), "", DynarrayChar_length(other), 0), "total removal");
   

    // TODO test dynarray inserting functions    
    DynarrayChar_destroy(other);
    DynarrayChar_destroy(dynarr);
    return 0;
}

