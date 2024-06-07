#include "arg_check_input_is_valid.h"

bool check_user_flags_to_allowed_flags(struct flag_and_value* user_input_flag_and_value_array,
                                       const int32_t USER_INPUT_FLAG_AND_VALUE_ARRAY_LEN,
                                       hashable_string_struct** hash_table_head_ptr_ptr,
                                       const bool DEBUG_MODE) {
    for (size_t i = 0; i < USER_INPUT_FLAG_AND_VALUE_ARRAY_LEN; i++) {
        hashable_string_struct* temp = NULL;  // pointer for the return value struct.
        if (DEBUG_MODE) printf("<IN> [%ld] checking if %s exists in hash...\n", i, user_input_flag_and_value_array[i].flag);
        HASH_FIND_STR(*hash_table_head_ptr_ptr, user_input_flag_and_value_array[i].flag, temp);  // checks if the flag str exists in the hash table.
        if (temp == NULL) {  // no hit in the hash table, hence pointer remains NULL.
            (void)fprintf(stderr, "ERROR: invalid flag \"%s\" found in arguments.\n"
                                  "Please ensure that flags used exists in the allowed arguments file (config/arguments.toml)!\n"
                                  "Aborting!\n", 
                                  user_input_flag_and_value_array[i].flag);
            return false;
        } else {
            if (DEBUG_MODE) printf("<IN> [%ld] %s found!\n", i, temp->string_malloc);
        }
    }
    if (DEBUG_MODE) printf("All flags are valid!\n");
    return true;  // all flags that user has entered can be found in the allowed flags hash.
}