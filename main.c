#include "./utils/arg_parse_input_fns/arg_parse_input_fns.h"
#include "./utils/arg_get_valid_fns/arg_get_valid_fns.h"
#include "./utils/arg_check_input_is_valid_fns/arg_check_input_is_valid.h"
#include "./utils/hash_utils/hash_utils.h"
#include "./utils/get_morse_symbols_from_args/get_morse_symbols_from_args.h"
#include "./defines/debugging_def.h"
#include "./defines/program_operation_def.h"

int main(int argc, char** argv) {

    // get flags that are allowed as an array of strings.
    char flags_allowed [MAX_FLAGS_ALLOWED][MAX_CHAR_PER_LINE];
    int32_t number_of_allowed_flags = get_flags_from_config_file_by_pointer(
        CONFIG_ARGUMENTS_PATH, KEY_LOOKING_FOR, ENCLOSING_CHAR_STR, 
        MAX_CHAR_PER_LINE, MAX_FLAGS_ALLOWED, flags_allowed, INNER_FNS_DEBUG_MODE
    );
    if (number_of_allowed_flags <= 0) return EXIT_FAILURE;
    if (TOP_LEVEL_DEBUG_MODE) {
        for (size_t i = 0; i < number_of_allowed_flags; i++) {
            printf("<main> [%ld] flag allowed is %s\n", i, flags_allowed[i]);
        }
    }

    // adds flags allowed strings into a hash.
    hashable_string_struct* flags = NULL;  // MUST free allcoated memory (struct and string member!) (NOT IMPLEMENTED YET!!)
    if(!add_string_array_into_hash(&flags, number_of_allowed_flags, MAX_CHAR_PER_LINE, flags_allowed, INNER_FNS_DEBUG_MODE)) return EXIT_FAILURE;
    if (TOP_LEVEL_DEBUG_MODE) {
        hashable_string_struct* temp = NULL;
        HASH_FIND_STR(flags, "-word", temp);
        if (temp) printf("flag value is %s\n", temp->string_malloc);
    }

    // get arguments that users entered as an array of structs.
    const int32_t FLAG_AND_VALUE_ARRAY_SIZE = (int32_t)((argc-1)/2);  // 1/2 of total number of flag & value args is enough.
    flag_and_value user_input_arguments_struct_array[FLAG_AND_VALUE_ARRAY_SIZE];  // an array of pointers to structs flag_and_value.
    if(!parse_user_arguments(argc, argv, user_input_arguments_struct_array, FLAG_AND_VALUE_ARRAY_SIZE, INNER_FNS_DEBUG_MODE)) return EXIT_FAILURE;
    if (TOP_LEVEL_DEBUG_MODE) {
        for (size_t i = 0; i < FLAG_AND_VALUE_ARRAY_SIZE; i++) {
            printf("<main> [%ld]: flag at position %ld is %s; value at position %ld is %s\n", 
                    i,
                    user_input_arguments_struct_array[i].flag_argno, user_input_arguments_struct_array[i].flag,
                    user_input_arguments_struct_array[i].value_argno, user_input_arguments_struct_array[i].value);
        }
    }

    // check if user has entered any flags that is not an allowed flag.
    if (!check_user_flags_to_allowed_flags(user_input_arguments_struct_array, FLAG_AND_VALUE_ARRAY_SIZE, &flags, INNER_FNS_DEBUG_MODE)) return EXIT_FAILURE;
    
    // retrieve morse symbols that the user has defined via the arguments' flags and values.
    morse_symbols_union morse_symbols;
    if(!get_morse_symbols_from_args(&morse_symbols, user_input_arguments_struct_array, FLAG_AND_VALUE_ARRAY_SIZE, INNER_FNS_DEBUG_MODE)) return EXIT_FAILURE;
    if (TOP_LEVEL_DEBUG_MODE) {
        for (size_t i = 0; i < FLAG_AND_VALUE_ARRAY_SIZE; i++) {
            printf("<main> [%ld] union's array has \" %s \"\n", i, morse_symbols.morse_symbols_members_arr[i]);
            switch (i) {
                case 0: printf("<main> [%ld] union's struct has \" %s \"\n", i, morse_symbols.morse_symbols_struct.DOT); break;
                case 1: printf("<main> [%ld] union's struct has \" %s \"\n", i, morse_symbols.morse_symbols_struct.DASH); break;
                case 2: printf("<main> [%ld] union's struct has \" %s \"\n", i, morse_symbols.morse_symbols_struct.LETTER); break;
                case 3: printf("<main> [%ld] union's struct has \" %s \"\n", i, morse_symbols.morse_symbols_struct.WORD); break;
                default: break;
            }
        }
    }
    
    return EXIT_SUCCESS;
}