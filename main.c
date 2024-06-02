#include "./utils/arg_parse_input_fns.h"
#include "./utils/arg_get_valid_fns.h"
#include "./lib/str_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <limits.h>
#include <string.h>
#include <stdint.h>

#define CONFIG_ARGUMENTS_PATH "config/arguments.toml"
#define MAX_CHAR_PER_LINE 8192  // MUST ensure this value is longer than chars of each line in config file (roughly 8000 words)!!
#define KEY_LOOKING_FOR "required_flags"

static char* argument_flags_allowed[4] = {"-dot", "-dash", "-letter", "word"};

int main(int argc, char** argv) {
    // an array of pointers to structs flag_and_value. 1/2 of total number of flag & value args is enough.
    const size_t FLAG_AND_VALUE_ARRAY_SIZE = (size_t)((argc-1)/2);
    struct flag_and_value required_flags_struct_array[FLAG_AND_VALUE_ARRAY_SIZE];

    // opening the file with the required flags, as a pointer to a file stream.
    FILE* read_file_stream_ptr = read_file_and_return_file_stream(CONFIG_ARGUMENTS_PATH);
    
    // read the file stream, given pointer to line from file. saves line from file to the pointer if found key and returns true. else returns false.
    char line_from_file[MAX_CHAR_PER_LINE];  // avoided malloc() approach as per NASA The Power of 10: Rule 3.
    if (read_file_stream_and_copy_found_line(read_file_stream_ptr, line_from_file, MAX_CHAR_PER_LINE, KEY_LOOKING_FOR)) {
        char* double_quote_str = "\"";
        int32_t double_quotes_count = count_substrings(line_from_file, double_quote_str, strlen(double_quote_str));
        // error-handling when double quotes don't match, there aren't any required flags, etc.
        if(double_quotes_count % 2 != 0) {  // double quotes don't form a pair.
            (void)fprintf(stderr, "ERROR: mismatch in \" in %s.\n"
                                    "Please ensure configuration file is as follows:\n"
                                    "[flags]\n"
                                    "required_flags = [\"-<flag>\", \"-<flag>\", \"-<flag>\", \"-<flag>\"]!\n"
                                    "Aborting!\n", 
                                    CONFIG_ARGUMENTS_PATH);
            return EXIT_FAILURE;
        }
        if(double_quotes_count == 0) {  // there are no double quotes i.e. no required arguments.
            (void)fprintf(stderr, "ERROR: no \"<flag>\" found in %s.\n"
                                    "Please ensure configuration file is as follows:\n"
                                    "[flags]\n"
                                    "required_flags = [\"-<flag>\", \"-<flag>\", \"-<flag>\", \"-<flag>\"]\n"
                                    "Aborting!\n", 
                                    CONFIG_ARGUMENTS_PATH);
            return EXIT_FAILURE;
        }

        int32_t required_flags_count = double_quotes_count / 2;

        printf("required flags count: %d\n", required_flags_count);
        printf("double quotes count: %d\n", double_quotes_count);

        struct enclosing_char_start_end enclosing_char_start_end_struct_array[required_flags_count];
        char flags_from_line[required_flags_count][MAX_CHAR_PER_LINE];
        get_flags_from_line(enclosing_char_start_end_struct_array, required_flags_count, line_from_file, MAX_CHAR_PER_LINE, double_quote_str, flags_from_line);
        for (size_t i = 0; i < required_flags_count; i++) {
            printf("the string at index %ld: %s\n", i, flags_from_line[i]);
        }
    } else {
        (void)fprintf(stderr, "ERROR: key \"%s\" not found in file \"%s\".\n"
                               "Please ensure configuration file is as follows:\n"
                               "[flags]\n"
                               "required_flags = [\"-<flag>\", \"-<flag>\", \"-<flag>\", \"-<flag>\"]!\n"
                               "Aborting!\n", 
                               KEY_LOOKING_FOR,
                               CONFIG_ARGUMENTS_PATH);
        return EXIT_FAILURE;
    }
    // logic to parse user-supplied arguments into an array of argument structs.
    if(!parse_user_arguments(argc, argv, argument_flags_allowed, required_flags_struct_array, FLAG_AND_VALUE_ARRAY_SIZE, true)) {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}