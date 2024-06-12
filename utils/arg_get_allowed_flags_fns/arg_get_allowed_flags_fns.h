#ifndef ARGS_GET_ALLOWED_FLAGS_FN
#define ARGS_GET_ALLOWED_FLAGS_FN

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../structs/structs_definitions.h"

/* Parameters:
**   - FILE* file_stream: pointer to the file represented as a stream.
**   - char* save_found_line_to_str: <retrieval> the pointer to a string where the found line will be copied to (if it exists).
**   - const size_t MAX_CHAR_IN_EACH_LINE: the maximum char expected in each line.
**   - char* needle: the keyword that determines if this line is the one we want.
** Action:
**   - accepts a file via its file path, iterates through each line of the file and reads the line.
**   - if the line contains the 'needle', then copy the line onto the argument pointer to string.
** Return:
**   - true: if line is found.
**   - false: line is not found.
*/
bool read_file_stream_and_copy_found_line(FILE* file_stream, char* save_found_line_to_str, const size_t MAX_CHAR_IN_EACH_LINE, char* needle);

/* Parameters:
**   - struct enclosing_char_start_end* enclosing_char_start_end_struct_array_ptr: pointer to array of structs that hold pointers to opening and closing quotes.
**   - int32_t ENCLOSING_CHAR_START_END_STRUCT_ARRAY_LEN: length of the array of structs that hold pointers to opening and closing quotes.
**   - char* line_of_text: line of text where the opening and closing quotes have been extracted from.
**   - const int32_t MAX_LINE_OF_TEXT_LEN: maximum length of the line of text.
**   - char* ENCLOSING_CHAR_STR: the enclosing character e.g. double quote that has been captured by the struct array.
**   - char (*copy_flags_here_str_array) [MAX_LINE_OF_TEXT_LEN]: <retrieval> the array of string as an argument. the flags will be added via this.
** Action:
**   - finds all the occurrences of the enclosing characters e.g. double quotes, and copies their pointers into a struct array.
**   - using these pointers, extract the strings that are enclosed in these enclosing characters.
** Return:
**   - void.
*/
void get_flags_from_line(struct enclosing_char_start_end* enclosing_char_start_end_struct_array_ptr,
                         const int32_t ENCLOSING_CHAR_START_END_STRUCT_ARRAY_LEN,
                         char* line_of_text,
                         const int32_t MAX_LINE_OF_TEXT_LEN,
                         const char* ENCLOSING_CHAR_STR,
                         char (*copy_flags_here_str_array) [MAX_LINE_OF_TEXT_LEN]);

/* Parameters:
**   - const char* CONFIG_ARGUMENTS_PATH: string of the configuration file path to be opened.
**   - const char* KEY_LOOKING_FOR: which key in the configuration file has the desired value.
**   - const char* ENCLOSING_CHAR_STR: what is the enclosing character that encloses the values of the list (e.g. for "value" the enclosing char would be " itself).
**   - const int32_t MAX_CHAR_PER_LINE: the maximum possible number of characters per line.
**   - const int32_t MAX_FLAGS_ALLOWED: the maximum possible number of flags allowed.
**   - char (*retrieve_flags_str_array) [MAX_CHAR_PER_LINE]): <retrieval> array of string as a argument, i.e. pointer to a char array of size MAX_CHAR_PER_LINE.
**   - const bool DEBUG_MODE: true to include debug outputs.
** Action:
**   - reads the configuration file.
**   - extracts the line with the desired key.
**   - determines how many flags there are (based on how many pairs of enclosing characters that surround the flags).
**   - saves the pointers to these enclosing characters in preparation for flag extraction.
**   - extracts the flags into an array of strings.
**   - note: steps are kept separate to ensure O(n) at most.
** Return:
**   - int32_t -1: ERROR: something went wrong.
**   - int32_t 0: ERROR: no flags found.
**   - int32_t required_flags_count: number of flags found.
*/
int32_t get_flags_from_config_file_by_pointer(const char* CONFIG_ARGUMENTS_PATH, 
                                              const char* KEY_LOOKING_FOR, 
                                              const char* ENCLOSING_CHAR_STR, 
                                              const int32_t MAX_CHAR_PER_LINE,
                                              const int32_t MAX_FLAGS_ALLOWED,
                                              char (*retrieve_flags_str_array) [MAX_FLAGS_ALLOWED],
                                              const bool DEBUG_MODE);

#endif