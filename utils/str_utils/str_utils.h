#ifndef STR_UTILS
#define STR_UTILS

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

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

#endif