#ifndef HASH_UTILS
#define HASH_UTILS

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../../structs/structs_definitions.h"

/*
** parameter: 
**    - hashable_string_struct** head_ptr: pointer to pointer of hash head (dereferences into the actual pointer).
**    - const int32_t STR_ARR_LEN: how many strings there are in the array.
**    - const int32_t PER_STR_LEN: how many chars there are in each char[].
**    - char (*str_arr)[PER_STR_LEN]: to pass char[][] as argument to this function.
**    - const bool DEBUG_MODE: <true> to display debug info on console, <false> to omit.
** action:
**    - turns each string into a hashable string.
**    - adds the hashable string into the hash.
** returns:
**    - bool: <true> for successful execution, <false> for error.
*/
bool add_string_array_into_hash(hashable_string_struct** head_ptr,
                                const int32_t STR_ARR_LEN,
                                const int32_t PER_STR_LEN,
                                char (*str_arr)[PER_STR_LEN],
                                const bool DEBUG_MODE);

/*
** parameter: 
**    - hashable_string_struct** head_ptr: pointer to pointer of hash head (dereferences into the actual pointer).
** action:
**    - frees hash table and its items.
** returns:
**    - void.
*/
void free_hashable_string_in_hash(hashable_string_struct** head_ptr);

#endif