#ifndef STR_UTILS
#define STR_UTILS

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../structs/structs_definitions.h"

/*
** parameter: 
**    - char* haystack: the string where the search takes place.
**    - const char* NEEDLE: the string to be found within the haystack.
**    - int32_t needle_length: length of the string to be found.
** action:
**    - finds the number of times needle has been found in the haystack.
** returns:
**    - int32_t: number of times needle has been found in the haystack.
*/
int32_t count_substrings(char* haystack, const char* NEEDLE, int32_t needle_length);

/*
** parameter: 
**    - malloc_str* malloc_str_ptr: pointer to malloced string struct on the heap.
** action:
**    - frees the string member in the malloc_str struct.
**    - frees the malloc_str stuct itself.
** returns:
**    - malloc_str*: returns NULL.
*/
malloc_str* free_malloced_str(malloc_str* malloc_str_ptr);

#endif