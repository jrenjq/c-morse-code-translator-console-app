#ifndef FILE_UTILS
#define FILE_UTILS

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// useful for returning both pointer to string on heap & its length.
typedef struct malloc_str {
    char* str_ptr;
    int32_t str_len;
} malloc_str;

/* Parameters:
**   - const char* FILE_PATH: string for file path.
**   - const char* READ_MODE: string for read mode.
** Action:
**   - accepts a file via its file path and returns its stream.
**   - DOES NOT close the file stream.
** Return:
**   - NULL: if error when reading specified file.
**   - FILE*: if file exists and can be read.
*/
FILE* open_file_and_return_file_stream(const char* FILE_PATH, const char* READ_MODE);

/* Parameters:
**   - FILE* file_stream_ptr: pointer to file stream pointer.
** Action:
**   - counts the number of characters in the file via the file stream pointer.
**   - count includes newline, does not include EOF.
**   - DOES NOT close the file stream.
** Return:
**   - int32_t: count of the number of characters in the file.
*/
int32_t count_characters_in_file(FILE* file_stream_ptr);

malloc_str file_to_string(FILE* file_stream_ptr, const int32_t CHAR_IN_FILE_COUNT, const bool DEBUG_MODE);

#endif