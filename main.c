#include "./utils/arg_parse_input_fns.h"
#include "./utils/arg_get_valid_fns.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <limits.h>
#include <string.h>
#include <stdint.h>

#define CONFIG_ARGUMENTS_PATH "config/arguments.toml"
#define KEY_LOOKING_FOR "required_flags"
#define ENCLOSING_CHAR_STR "\""
#define MAX_CHAR_PER_LINE 256  // MUST ensure this value >= max expected chars of each line in config file! BUT if too big causes seg fault or value truncation.
#define MAX_FLAGS_ALLOWED 256  // MUST ensure this value >= max expected flags possible in the config file! BUT if too big causes seg fault or value truncation.

static char* argument_flags_allowed[4] = {"-dot", "-dash", "-letter", "word"};

int main(int argc, char** argv) {

    char flags_allowed [MAX_FLAGS_ALLOWED][MAX_CHAR_PER_LINE];
    int32_t number_of_flags = get_flags_from_config_file_by_pointer(CONFIG_ARGUMENTS_PATH, KEY_LOOKING_FOR, ENCLOSING_CHAR_STR, MAX_CHAR_PER_LINE, MAX_FLAGS_ALLOWED, flags_allowed);
    if (number_of_flags < 0) return EXIT_FAILURE;
    

    // logic to parse user-supplied arguments into an array of argument structs.
    const int32_t FLAG_AND_VALUE_ARRAY_SIZE = (int32_t)((argc-1)/2);  // 1/2 of total number of flag & value args is enough.
    struct flag_and_value required_flags_struct_array[FLAG_AND_VALUE_ARRAY_SIZE];  // an array of pointers to structs flag_and_value.
    if(!parse_user_arguments(argc, argv, argument_flags_allowed, required_flags_struct_array, FLAG_AND_VALUE_ARRAY_SIZE, true)) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}