#ifndef ARGS_CHECK_FNS
#define ARGS_CHECK_FNS

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

struct enclosing_char_start_end {
    char* start;
    char* end;
};

FILE* read_file_and_return_file_stream(const char* FILE_PATH);

bool read_file_stream_and_copy_found_line(FILE* file_stream, char* save_found_line_to_str, const size_t MAX_CHAR_IN_EACH_LINE, char* needle);

bool get_flags_from_line(struct enclosing_char_start_end* enclosing_char_start_end_struct_array_ptr,
                         int32_t enclosing_char_start_end_struct_array_len,
                         char* line_of_text,
                         int32_t line_of_text_len,
                         char* encasing_char,
                         char (*copy_flags_here_str_array) [line_of_text_len]);

#endif