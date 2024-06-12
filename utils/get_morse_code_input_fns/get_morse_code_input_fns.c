#include "./get_morse_code_input_fns.h"

#include <stdlib.h>
#include <string.h>

malloc_str file_into_malloc_str(const char* FILE_INPUT_PATH, const bool DEBUG_MODE) {
    FILE* morse_code_input_fs_ptr = open_file_and_return_file_stream(FILE_INPUT_PATH, "r");
    int32_t char_count = count_characters_in_file(morse_code_input_fs_ptr);
    if (DEBUG_MODE) printf("<in> morse code file has %d characters\n", char_count);
    malloc_str file_as_str = file_to_string(morse_code_input_fs_ptr, char_count, DEBUG_MODE);
    return file_as_str;
}