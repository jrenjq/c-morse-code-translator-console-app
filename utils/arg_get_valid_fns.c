#include "arg_get_valid_fns.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

#define CONFIG_ARGUMENTS_PATH "config/arguments.toml"
#define KEY_LOOKING_FOR "required_flags"

FILE* read_file_and_return_file_stream(const char* FILE_PATH);

/* Parameters:
**   - const char* FILE_PATH: string for file path.
** Action:
**   - accepts a file via its file path and returns its stream.
** Return:
**   - NULL: if error when reading specified file.
**   - FILE*: if file exists and can be read.
*/
FILE* read_file_and_return_file_stream(const char* FILE_PATH) {
    // opening the file with the required flags.
    FILE* file_ptr = fopen(FILE_PATH, "r");  // open file containing required flags as a stream.
    if(file_ptr == NULL) {  // ERROR: the file specified doesn't exist.
        (void)fprintf(stderr, "ERROR: cannot open file in \"%s\" directory.\n"
                              "Please ensure file exists/is named correctly!\n"
                              "Aborting!\n", 
                              FILE_PATH);
        return NULL;
    }
    return file_ptr;  // returns pointer to stream representing the file.
}

/* Parameters:
**   - FILE* file_stream: pointer to the file represented as a stream.
**   - char* save_found_line_to_str: the pointer to a string where the found line will be copied to (if it exists).
**   - const size_t MAX_CHAR_IN_EACH_LINE: the maximum char expected in each line.
**   - char* needle: the keyword that determines if this line is the one we want.
** Action:
**   - accepts a file via its file path, iterates through each line of the file and reads the line.
**   - if the line contains the 'needle', then copy the line onto the argument pointer to string.
** Return:
**   - true: if line is found.
**   - false: line is not found.
*/
bool read_file_stream_and_copy_found_line(FILE* file_stream, char* save_found_line_to_str, const size_t MAX_CHAR_IN_EACH_LINE, char* needle) {
    // extracting the required flags from the file stream.
    char line_from_file[MAX_CHAR_IN_EACH_LINE];  // this is a string that represents a line read from the file.
    while(fgets(line_from_file, MAX_CHAR_IN_EACH_LINE, file_stream)) {  // gets a line from the file; next iteration reads next line until no more lines.
        char* desired_key_needle = strstr(line_from_file, needle);  // note: strstr could return NULL!
        if(desired_key_needle != NULL && *desired_key_needle == line_from_file[0]) {  // if the first char of desired key is also the first char in the line.
            strncpy(save_found_line_to_str, line_from_file, MAX_CHAR_IN_EACH_LINE);
            return true;
        }
    }
    return false;
}

bool get_flags_from_line(struct enclosing_char_start_end* enclosing_char_start_end_struct_array_ptr,
                         int32_t enclosing_char_start_end_struct_array_len,
                         char* line_of_text,
                         int32_t line_of_text_len,
                         char* encasing_char,
                         char (*copy_flags_here_str_array) [line_of_text_len]) {  // char (*p) [100] -> p is pointer to a 100 char array (anticlock spiral). for string array arguments.
    int32_t char_count = 0;  // keep track of how many encasing_char encountered.
    int32_t pair_count = 0;  // keep track of how many pairs of the encasing_char we have encountered.
    while(line_of_text = strstr(line_of_text, encasing_char)) {  // move the cursor to wherever the needle character is, ends if there are no more needles.
        if (++char_count % 2 == 1) {  // odd number of double quotes. must be a starting ".
            (enclosing_char_start_end_struct_array_ptr + (pair_count))->start = line_of_text;  // make a copy of the start cursor.
            // printf("%s\n", (enclosing_char_start_end_struct_array_ptr + (pair_count))->start);
        } else {
            (enclosing_char_start_end_struct_array_ptr + (pair_count))->end = line_of_text;  // make a copy of the end cursor.
            // printf("%s\n", (enclosing_char_start_end_struct_array_ptr + (pair_count))->end);
            pair_count++;  // after the latter half of the pair is encountered, one pair has been encountered.
        }
        line_of_text++;  // increment the cursor so we won't find the same character.
    }

    // // extract string from line via structs of start and end pointers to their double quotes.
    char required_flags_str_array[enclosing_char_start_end_struct_array_len][line_of_text_len];  // an array of strings with just enough elements to hold the required flags.
    for (size_t i = 0; i < enclosing_char_start_end_struct_array_len; i++) {
        // iterate through the structs of start and end pointers to chars on the text line.
        // ( (end pointer - start pointer) - 1 ) gives the number of chars for each required flag, this is because ...
        // " A B C D E " 
        // 1 2 3 4 5 6 7  ->  5 letters and 2 quotes. 7 - 1 = 6 spaces between. 6 - 1 = 5 chars total. like counting train stations.
        // then strncpy the header to each string into the required_flags_str_array.

        size_t required_flag_str_no_quotes_length = (int32_t)(enclosing_char_start_end_struct_array_ptr[i].end - enclosing_char_start_end_struct_array_ptr[i].start) - 1;  // len(required flag - quotes).
        char required_flag_str_no_quotes[required_flag_str_no_quotes_length + 1];  // make space at the end for 1 null terminator char.
        strncpy(required_flag_str_no_quotes, enclosing_char_start_end_struct_array_ptr[i].start + 1, required_flag_str_no_quotes_length);  // start at 1 char after the starting ".
        required_flag_str_no_quotes[required_flag_str_no_quotes_length] = '\0';  // add the null terminator to demarcate the end of the string.

        strcpy(required_flags_str_array[i], required_flag_str_no_quotes);  // to a local char[][].
        strcpy(copy_flags_here_str_array[i], required_flag_str_no_quotes);  // to an argument pointer to a char[].

        // printf("the string at index %ld: %s\n", i, copy_flags_here_str_array[i]);
    }
    for (size_t i = 0; i < enclosing_char_start_end_struct_array_len; i++) {
        printf("the string at index %ld: %s\n", i, copy_flags_here_str_array[i]);
    }
    return true;
}