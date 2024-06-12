#ifndef GET_MORSE_SYMBOLS_FROM_ARGS
#define GET_MORSE_SYMBOLS_FROM_ARGS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "../arg_parse_input_fns/arg_parse_input_fns.h"
#include "../../structs/structs_definitions.h"
#include "../../unions/unions_definitions.h"

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