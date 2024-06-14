#include "./utils/arg_parse_input_fns/arg_parse_input_fns.h"
#include "./utils/arg_get_allowed_flags_fns/arg_get_allowed_flags_fns.h"
#include "./utils/arg_check_input_is_valid_fns/arg_check_input_is_valid.h"
#include "./utils/get_morse_symbols_from_args/get_morse_symbols_from_args.h"
#include "./utils/get_morse_code_input_fns/get_morse_code_input_fns.h"
#include "./utils/translate_morse_to_char_fns/translate_morse_to_char_fns.h"

#include "./defines/debugging_def.h"
#include "./defines/program_operation_def.h"

int main(int argc, char** argv) {

    // get flags that are allowed as an array of strings.
    char flags_allowed[MAX_FLAGS_ALLOWED][MAX_CHAR_PER_LINE];
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
    hashable_string_struct* flags = NULL;  // MUST free allcoated memory (free both struct itself and its string member!) (NOT IMPLEMENTED YET!!)
    if (!add_string_array_into_hash(&flags, number_of_allowed_flags, MAX_CHAR_PER_LINE, flags_allowed, INNER_FNS_DEBUG_MODE)) return EXIT_FAILURE;

    // get arguments that users entered as an array of structs.
    const int32_t FLAG_AND_VALUE_ARRAY_SIZE = (int32_t)((argc-1)/2);  // 1/2 of total number of flag & value args is enough.
    flag_and_value user_input_arguments_struct_array[FLAG_AND_VALUE_ARRAY_SIZE];  // an array of pointers to structs flag_and_value.
    if (!parse_user_arguments(argc, argv, user_input_arguments_struct_array, FLAG_AND_VALUE_ARRAY_SIZE, INNER_FNS_DEBUG_MODE)) return EXIT_FAILURE;
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
    
    // retrieve morse symbols that the user has defined via the arguments' flags and values & checks all required flags are entered.
    morse_symbols_union morse_symbols;
    if (!get_morse_symbols_from_args(&morse_symbols, user_input_arguments_struct_array, FLAG_AND_VALUE_ARRAY_SIZE, INNER_FNS_DEBUG_MODE)) return EXIT_FAILURE;
    if (TOP_LEVEL_DEBUG_MODE) {
        for (size_t i = 0; i < FLAG_AND_VALUE_ARRAY_SIZE; i++) {
            printf("<main> [%ld] union's array has \" %s \"\n", i, morse_symbols.morse_symbols_members_arr[i]);
            switch (i) {
                case 0: printf("<main> [%ld] union's struct has \" %s \"\n", i, morse_symbols.morse_symbols_struct.LETTER); break;
                case 1: printf("<main> [%ld] union's struct has \" %s \"\n", i, morse_symbols.morse_symbols_struct.WORD); break;
                default: break;
            }
        }
    }

    // converts morse code file into a single string on the heap. // MUST free malloc string pointer. (NOT IMPLEMENTED YET!!)
    malloc_str* file_as_malloc_str_struct_ptr = file_into_malloc_str(MORSE_CODE_INPUT_PATH, INNER_FNS_DEBUG_MODE);
    if (TOP_LEVEL_DEBUG_MODE) printf("<main> malloc str struct has \"%s\" as string, and a string length of %ld.\n", 
                                      file_as_malloc_str_struct_ptr->str_ptr, file_as_malloc_str_struct_ptr->str_len);

    // letter delimiter + 1 <missing from the last letter> = total number of words.
    int32_t letter_count = count_substrings(file_as_malloc_str_struct_ptr->str_ptr, 
                                            morse_symbols.morse_symbols_struct.LETTER, 
                                            strlen(morse_symbols.morse_symbols_struct.LETTER)) + 1;
    // word delimiter + 1 <missing from the last word> = total number of words.
    int32_t word_count = count_substrings(file_as_malloc_str_struct_ptr->str_ptr, 
                                          morse_symbols.morse_symbols_struct.WORD, 
                                          strlen(morse_symbols.morse_symbols_struct.WORD)) + 1;
    if (TOP_LEVEL_DEBUG_MODE) printf("<main> there are %d letters here, based on the %s delimiter.\n", letter_count, morse_symbols.morse_symbols_struct.LETTER);
    if (TOP_LEVEL_DEBUG_MODE) printf("<main> there are %d words here, based on the %s delimiter.\n", word_count, morse_symbols.morse_symbols_struct.WORD);

    // translate morse code string into english string.
    malloc_str* translated_str_ptr = translate_morse_to_english(file_as_malloc_str_struct_ptr, letter_count, word_count, &morse_symbols, INNER_FNS_DEBUG_MODE);
    if (TOP_LEVEL_DEBUG_MODE) printf("<main> translated string is \"%s\"\n", translated_str_ptr->str_ptr);

    // write the translated string into the output text file.
    if (!write_string_to_file(MORSE_CODE_OUTPUT_PATH, translated_str_ptr->str_ptr)) return EXIT_FAILURE;
    if (TOP_LEVEL_DEBUG_MODE) printf("<main> translated string written to file \"%s\"\n", MORSE_CODE_OUTPUT_PATH);

    return EXIT_SUCCESS;
}