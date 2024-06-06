#include "./utils/arg_parse_input_fns/arg_parse_input_fns.h"
#include "./utils/arg_get_valid_fns/arg_get_valid_fns.h"
#include "./utils/hash_utils/hash_utils.h"
#include "./defines/debugging_def.h"
#include "./defines/program_operation_def.h"

static char* argument_flags_allowed[4] = {"-dot", "-dash", "-letter", "word"};

int main(int argc, char** argv) {

    // get flags that are allowed as an array of strings.
    char flags_allowed [MAX_FLAGS_ALLOWED][MAX_CHAR_PER_LINE];
    int32_t number_of_allowed_flags = get_flags_from_config_file_by_pointer(CONFIG_ARGUMENTS_PATH, KEY_LOOKING_FOR, ENCLOSING_CHAR_STR, 
                                                                    MAX_CHAR_PER_LINE, MAX_FLAGS_ALLOWED, flags_allowed, INNER_FNS_DEBUG_MODE);
    if (number_of_allowed_flags <= 0) return EXIT_FAILURE;
    if (TOP_LEVEL_DEBUG_MODE) {
        for (size_t i = 0; i < number_of_allowed_flags; i++) {
            printf("<main> [%ld] flag allowed is %s\n", i, flags_allowed[i]);
        }
    }

    // refactor this later into a test
    // hashable_string_struct* h_str_struct_malloc_ptr = string_to_hashable_string_struct_ptr("testing", strlen("testing"));
    // printf("<main> string in struct is: %s\n", h_str_struct_malloc_ptr->string_malloc);
    // h_str_struct_malloc_ptr = free_hashable_string_struct(h_str_struct_malloc_ptr);

    // adds flags allowed strings into a hash.
    hashable_string_struct* flags = NULL;
    if(!add_string_array_into_hash(&flags, number_of_allowed_flags, MAX_CHAR_PER_LINE, flags_allowed, INNER_FNS_DEBUG_MODE)) return EXIT_FAILURE;
    
    hashable_string_struct* temp = NULL;
    HASH_FIND_STR(flags, "-word", temp);
    if (temp) printf("flag value is %s\n", temp->string_malloc);


    // get arguments that users entered as an array of structs.
    const int32_t FLAG_AND_VALUE_ARRAY_SIZE = (int32_t)((argc-1)/2);  // 1/2 of total number of flag & value args is enough.
    struct flag_and_value required_flags_struct_array[FLAG_AND_VALUE_ARRAY_SIZE];  // an array of pointers to structs flag_and_value.
    if(!parse_user_arguments(argc, argv, argument_flags_allowed, 
                             required_flags_struct_array, FLAG_AND_VALUE_ARRAY_SIZE, INNER_FNS_DEBUG_MODE)) return EXIT_FAILURE;
    if (TOP_LEVEL_DEBUG_MODE) {
        for (size_t i = 0; i < FLAG_AND_VALUE_ARRAY_SIZE; i++) {
            printf("<main> [%ld]: flag at position %ld is %s; value at position %ld is %s\n", 
                    i,
                    required_flags_struct_array[i].flag_argno, required_flags_struct_array[i].flag,
                    required_flags_struct_array[i].value_argno, required_flags_struct_array[i].value);
        }
    }
    
    return EXIT_SUCCESS;
}