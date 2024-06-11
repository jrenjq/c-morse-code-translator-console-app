#ifndef ARG_CHECK_INPUT_IS_VALID
#define ARG_CHECK_INPUT_IS_VALID

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../arg_parse_input_fns/arg_parse_input_fns.h"
#include "../hash_utils/hash_utils.h"
#include "../../structs/structs_definitions.h"

/*
** parameter: 
**    - flag_and_value* user_input_flag_and_value_array: a struct array that represents the user's input flags and values, as parsed from argv.
**    - const int32_t USER_INPUT_FLAG_AND_VALUE_ARRAY_LEN: length of flags and values struct array.
**    - hashable_string_struct** hash_table_head_ptr_ptr: pointer to pointer of hash table head (bc. actual pointer required).
**    - const bool DEBUG_MODE: reveals print statements useful for debugging.
** action:
**    - checks if the flags that user has entered is inside the allowed flags.
** returns:
**    - bool: <true> when arguments are all valid. <false> when there is a flag that's not present in the allowed flags.
*/
bool check_user_flags_to_allowed_flags(flag_and_value* user_input_flag_and_value_array,
                                       const int32_t USER_INPUT_FLAG_AND_VALUE_ARRAY_LEN,
                                       hashable_string_struct** hash_table_head_ptr_ptr,
                                       const bool DEBUG_MODE);

#endif