#include "./utils/arg_parse_fns.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <limits.h>
#include <string.h>

#define CONFIG_ARGUMENTS_PATH "config/arguments.toml"
#define MAX_CHAR_PER_LINE 8192
#define KEY_LOOKING_FOR "required_flags"

static char* argument_flags_allowed[4] = {"-dot", "-dash", "-letter", "word"};

int main(int argc, char** argv) {
    // an array of pointers to structs flag_and_value. 1/2 of total number of flag & value args is enough.
    const size_t FLAG_AND_VALUE_ARRAY_SIZE = (size_t)((argc-1)/2);
    struct flag_and_value flag_and_value_array[FLAG_AND_VALUE_ARRAY_SIZE];

    // opening the file with the required flags.
    FILE* arguments_file_ptr = fopen(CONFIG_ARGUMENTS_PATH, "r");  // open file containing required flags as a stream.
    if(arguments_file_ptr == NULL) {  // ERROR: the file specified doesn't exist.
        (void)fprintf(stderr, "ERROR: cannot open arguments file in \"%s\" directory.\n"
                              "Please ensure file exists/is named correctly!\n"
                              "Aborting!\n", 
                              CONFIG_ARGUMENTS_PATH);
        return EXIT_FAILURE;
    }
    
    // extracting the required flags from the file stream.
    char line_from_file[MAX_CHAR_PER_LINE];  // this is a string that represents a line read from the file.
    while(fgets(line_from_file, MAX_CHAR_PER_LINE, arguments_file_ptr)) {  // gets a line from the file; next iteration reads next line until no more lines.
        char* equal_sign_needle = strstr(line_from_file, "=");  // strstr() returns null pointer if not found, or a pointer to 1st char of 1st occurrence if found.
        char* desired_key_needle = strstr(line_from_file, KEY_LOOKING_FOR);  // variable written out separately to help with code legibility.
        
        // get the line that has the required flags.
        if(equal_sign_needle != NULL && *desired_key_needle == line_from_file[0]) {  // if '=' exists in this line && the desired key is first in the line.
            const char* cursor = line_from_file;  // make a temporary char* to iterate through the string.
            size_t required_flags_count = 0;  // how many required flags are there from the file.
            size_t double_quotes_count = 0;  // how many double quotes there are.
            
            // find how many required flags there are in the line.
            while(cursor = strstr(cursor, "\"")) {  // move the cursor to wherever the " character is, ends if there are no more ".
                double_quotes_count++;  // increment the number of double quotes encountered.
                cursor++;  // increment the cursor.
                if(double_quotes_count % 2 == 0) {  // if we have enountered a pair of double quotes ...
                    required_flags_count++;  // ... assumption is that we have encountered one required flag.
                }
            }

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

            printf("required flags count: %ld\n", required_flags_count);
            printf("double quotes count: %ld", double_quotes_count);
        } else {
            continue;  // not the line we're looking for.
        }
    }
    puts("\n");

    // logic to parse user-supplied arguments into an array of argument structs.
    if(!parse_user_arguments(argc, argv, argument_flags_allowed, flag_and_value_array, FLAG_AND_VALUE_ARRAY_SIZE, true)) {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}