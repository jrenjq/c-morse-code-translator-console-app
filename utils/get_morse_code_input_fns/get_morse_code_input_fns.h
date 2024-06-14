#ifndef GET_MORSE_CODE_INPUT_FNS
#define GET_MORSE_CODE_INPUT_FNS

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "../file_utils/file_utils.h"
#include "../str_utils/str_utils.h"

/*
** parameter: 
**    - const char* FILE_INPUT_PATH: file path string.
**    - const bool DEBUG_MODE: reveals print statements useful for debugging.
** action:
**    - reads a file and converts text into a single string malloced onto the heap.
** returns:
**    - malloc_str*: pointer to malloced struct which contains pointer to string and its length.
*/
malloc_str* file_into_malloc_str(const char* FILE_INPUT_PATH, const bool DEBUG_MODE);

#endif