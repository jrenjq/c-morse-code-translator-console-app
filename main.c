#include "./utils/arg_parse_fns.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <limits.h>
#include <string.h>
#include <stdint.h>

#define CONFIG_ARGUMENTS_PATH "config/arguments.toml"
#define MAX_CHAR_PER_LINE 32768  // MUST ensure this value is longer than chars of each line in config file (roughly 8000 words)!!
#define KEY_LOOKING_FOR "required_flags"

struct double_quotes_start_end {
    char* start;
    char* end;
};

static char* argument_flags_allowed[4] = {"-dot", "-dash", "-letter", "word"};

int main(int argc, char** argv) {
    // an array of pointers to structs flag_and_value. 1/2 of total number of flag & value args is enough.
    const size_t FLAG_AND_VALUE_ARRAY_SIZE = (size_t)((argc-1)/2);
    struct flag_and_value required_flags_struct_array[FLAG_AND_VALUE_ARRAY_SIZE];

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
            char* cursor = line_from_file;  // make a temporary char* to iterate through the string.
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
            printf("double quotes count: %ld\n", double_quotes_count);

            // save the start and end index for each double quote in the line.
            struct double_quotes_start_end required_flags_struct_array[required_flags_count];  // array of required flag's double quote's index (size based on double quote count).
            cursor = line_from_file;  // reset the start position of the cursor to start of the line.
            double_quotes_count = 0;  // reset the double quotes count.
            required_flags_count = 0;  // reset the required flags count.
            while(cursor = strstr(cursor, "\"")) {  // move the cursor to wherever the " character is, ends if there are no more ".
                if (++double_quotes_count % 2 == 1) {  // odd number of double quotes. must be a starting ".
                    required_flags_struct_array[required_flags_count].start = cursor;  // make a copy of the start cursor.
                } else {
                    required_flags_struct_array[required_flags_count].end = cursor;
                    required_flags_count++;  // increment counter so we can fill in next required flag struct.
                }
                cursor++;  // increment the cursor so we won't find the same " character.
            }

            // extract string from line via structs of start and end pointers to their double quotes.
            char required_flags_str_array[required_flags_count][MAX_CHAR_PER_LINE];  // an array of strings with just enough elements to hold the required flags.
            for (size_t i = 0; i < required_flags_count; i++) {
                // iterate through the structs of start and end pointers to chars on the text line.
                // ( (end pointer - start pointer) - 1 ) gives the number of chars for each required flag, this is because ...
                // " A B C D E " 
                // 1 2 3 4 5 6 7  ->  5 letters and 2 quotes. 7 - 1 = 6 spaces between. 6 - 1 = 5 chars total. like counting train stations.
                // then strncpy the header to each string into the required_flags_str_array.

                size_t required_flag_str_no_quotes_length = (int32_t)(required_flags_struct_array[i].end - required_flags_struct_array[i].start) - 1;  // len(required flag - quotes).
                char required_flag_str_no_quotes[required_flag_str_no_quotes_length + 1];  // make space at the end for 1 null terminator char.
                strncpy(required_flag_str_no_quotes, required_flags_struct_array[i].start + 1, required_flag_str_no_quotes_length);  // start at 1 char after the starting ".
                required_flag_str_no_quotes[required_flag_str_no_quotes_length] = '\0';  // add the null terminator to demarcate the end of the string.
                printf("count: %ld, start: %p, end: %p\n", i, (required_flags_struct_array[i].start), (required_flags_struct_array[i].end));
                printf("difference: %d\n", (int32_t)(required_flags_struct_array[i].end - required_flags_struct_array[i].start) - 1);
                printf("the string: %s\n", required_flag_str_no_quotes);
                strcpy(required_flags_str_array[i],required_flag_str_no_quotes);
                printf("the string in array: %s\n", required_flags_str_array[i]);
            }
            for (size_t i = 0; i < required_flags_count; i++) {
                printf("the string at index %ld: %s\n", i, required_flags_str_array[i]);
            }
        } else {
            continue;  // not the line we're looking for.
        }
    }
    puts("\n");

    // logic to parse user-supplied arguments into an array of argument structs.
    if(!parse_user_arguments(argc, argv, argument_flags_allowed, required_flags_struct_array, FLAG_AND_VALUE_ARRAY_SIZE, true)) {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}