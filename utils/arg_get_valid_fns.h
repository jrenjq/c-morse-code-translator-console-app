#ifndef ARGS_CHECK_FNS
#define ARGS_CHECK_FNS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

struct enclosing_char_start_end {
    char* start;
    char* end;
};

FILE* read_file_and_return_file_stream(const char* FILE_PATH);

bool read_file_stream_and_copy_found_line(FILE* file_stream, char* save_found_line_to_str, const size_t MAX_CHAR_IN_EACH_LINE, char* needle);

void get_flags_from_line(struct enclosing_char_start_end* enclosing_char_start_end_struct_array_ptr,
                         const int32_t ENCLOSING_CHAR_START_END_STRUCT_ARRAY_LEN,
                         char* line_of_text,
                         const int32_t MAX_LINE_OF_TEXT_LEN,
                         const char* ENCLOSING_CHAR_STR,
                         char (*copy_flags_here_str_array) [MAX_LINE_OF_TEXT_LEN]);

int32_t get_flags_from_config_file_by_pointer(const char* CONFIG_ARGUMENTS_PATH, 
                                              const char* KEY_LOOKING_FOR, 
                                              const char* ENCLOSING_CHAR_STR, 
                                              const int32_t MAX_CHAR_PER_LINE,
                                              const int32_t MAX_FLAGS_ALLOWED,
                                              char (*retrieve_flags_str_array) [MAX_FLAGS_ALLOWED]);

#endif