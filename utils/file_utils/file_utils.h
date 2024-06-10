#ifndef FILE_UTILS
#define FILE_UTILS

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

FILE* read_file_and_return_file_stream(const char* FILE_PATH);

int32_t count_characters_in_file(FILE* file_stream_ptr);

#endif