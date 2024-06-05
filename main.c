#include "./utils/arg_parse_input_fns.h"
#include "./utils/arg_get_valid_fns.h"

// for program operation.
#define CONFIG_ARGUMENTS_PATH "config/arguments.toml"
#define KEY_LOOKING_FOR "required_flags"
#define ENCLOSING_CHAR_STR "\""
#define MAX_CHAR_PER_LINE 256  // MUST ensure this value >= max expected chars of each line in config file! BUT if too big causes seg fault or value truncation.
#define MAX_FLAGS_ALLOWED 256  // MUST ensure this value >= max expected flags possible in the config file! BUT if too big causes seg fault or value truncation.

// for debugging purposes.
#define TOP_LEVEL_DEBUG_MODE true
#define INNER_FNS_DEBUG_MODE false

static char* argument_flags_allowed[4] = {"-dot", "-dash", "-letter", "word"};

int main(int argc, char** argv) {

    // get flags that are allowed as an array of strings.
    char flags_allowed [MAX_FLAGS_ALLOWED][MAX_CHAR_PER_LINE];
    int32_t number_of_flags = get_flags_from_config_file_by_pointer(CONFIG_ARGUMENTS_PATH, KEY_LOOKING_FOR, ENCLOSING_CHAR_STR, 
                                                                    MAX_CHAR_PER_LINE, MAX_FLAGS_ALLOWED, flags_allowed, INNER_FNS_DEBUG_MODE);
    if (number_of_flags <= 0) return EXIT_FAILURE;
    if (TOP_LEVEL_DEBUG_MODE) {
        for (size_t i = 0; i < number_of_flags; i++) {
            printf("flag allowed %ld is %s\n", i, flags_allowed[i]);
        }
    }

    // get arguments that users entered as an array of structs.
    const int32_t FLAG_AND_VALUE_ARRAY_SIZE = (int32_t)((argc-1)/2);  // 1/2 of total number of flag & value args is enough.
    struct flag_and_value required_flags_struct_array[FLAG_AND_VALUE_ARRAY_SIZE];  // an array of pointers to structs flag_and_value.
    if(!parse_user_arguments(argc, argv, argument_flags_allowed, 
                             required_flags_struct_array, FLAG_AND_VALUE_ARRAY_SIZE, INNER_FNS_DEBUG_MODE)) return EXIT_FAILURE;
    if (TOP_LEVEL_DEBUG_MODE) {
        for (size_t i = 0; i < FLAG_AND_VALUE_ARRAY_SIZE; i++) {
            printf("[%ld]: flag at position %ld has value of %s; flag at position %ld has value of %s\n", 
                    i,
                    required_flags_struct_array[i].flag_argno, required_flags_struct_array[i].flag,
                    required_flags_struct_array[i].value_argno, required_flags_struct_array[i].value);
        }
    }

    
    return EXIT_SUCCESS;
}