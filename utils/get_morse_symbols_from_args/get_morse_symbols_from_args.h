#ifndef GET_MORSE_SYMBOLS_FROM_ARGS
#define GET_MORSE_SYMBOLS_FROM_ARGS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "../arg_parse_input_fns/arg_parse_input_fns.h"
#include "../../defines/program_operation_def.h"

typedef union morse_symbols_union {  // using union so that the struct members can be iterated like an array.
    struct morse_symbols_struct { 
        char DOT[MAX_CHAR_PER_LINE]; 
        char DASH[MAX_CHAR_PER_LINE]; 
        char LETTER[MAX_CHAR_PER_LINE]; 
        char WORD[MAX_CHAR_PER_LINE]; 
    } morse_symbols_struct;  // holds the morse symbols in a struct. rmb to declare its variable.
    
    // required_flags_count is tied to number of struct members = 4.
    char morse_symbols_members_arr[REQUIRED_FLAGS_COUNT][MAX_CHAR_PER_LINE];  // ensure the [m] x [n] = total struct members chars.
} morse_symbols_union;

/*
** parameter: 
**    - morse_symbols_union* morse_symbols_union_ptr: pointer to a morse_symbol_union.
**    - const flag_and_value* FLAG_AND_VALUE_ARR: pointer to array of structs that contain flag and value arguments from user.
**    - const int32_t FLAG_AND_VALUE_ARR_LEN: size pf the array of structs that contain flag and value arguments from user.
**    - const bool DEBUG_MODE: reveals print statements useful for debugging.
** action:
**    - populates the required flags' values from user arguments into a union variable.
**    - if any required flags and/or their values are missing, indicate error.
** returns:
**    - bool: <true> for all required flags' values noted. <false> otherwise.
*/
bool get_morse_symbols_from_args(morse_symbols_union* morse_symbols_union_ptr, 
                                 const flag_and_value* FLAG_AND_VALUE_ARR, 
                                 const int32_t FLAG_AND_VALUE_ARR_LEN,
                                 const bool DEBUG_MODE);

#endif