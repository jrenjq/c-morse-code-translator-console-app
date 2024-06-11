#include "./file_utils.h"

#include <stdlib.h>
#include <string.h>

#include "../str_utils/str_utils.h"

FILE* open_file_and_return_file_stream(const char* FILE_PATH, const char* READ_MODE) {
    // opening the file with the required flags.
    FILE* file_ptr = fopen(FILE_PATH, READ_MODE);  // open file containing required flags as a stream.
    if(file_ptr == NULL) {  // ERROR: the file specified doesn't exist.
        (void)fprintf(stderr, "ERROR: cannot open file in \"%s\" directory.\n"
                              "Please ensure file exists/is named correctly!\n"
                              "Aborting!\n", 
                              FILE_PATH);
        return NULL;
    }
    return file_ptr;  // returns pointer to stream representing the file. SHOULD fclose() when done with the pointer.
}

int32_t count_characters_in_file(FILE* file_stream_ptr) {
    char character; 
    int32_t count = 0;
    while ( (character=fgetc(file_stream_ptr)) != EOF ) {
        count++;
    }
    return count;
}

malloc_str file_to_string(FILE* file_stream_ptr, const int32_t CHAR_IN_FILE_COUNT, const bool DEBUG_MODE) {
    // allocate memory on the heap for the file content as a string.
    char* file_as_str_on_heap = (char*) malloc((CHAR_IN_FILE_COUNT * sizeof(char)) + 1);  // allowing one extra char for null terminator.
    file_as_str_on_heap[(CHAR_IN_FILE_COUNT * sizeof(char))] = '\0';  // append the null terminator to the end.
    
    char character;
    rewind(file_stream_ptr);
    for (size_t i = 0; (character=fgetc(file_stream_ptr)) != EOF ; i++) {  // iterating over the fgetc instead of char_in_file_count to be safe from bad char count.
        file_as_str_on_heap[i] = character;  // write the character read into the heap.
        if (DEBUG_MODE) printf("<in> [%ld] char copied is %c\n", i, file_as_str_on_heap[i]);
    }
    
    malloc_str return_struct = { .str_ptr = file_as_str_on_heap, .str_len = CHAR_IN_FILE_COUNT + 1};  // string length includes null terminator.
    if (DEBUG_MODE) printf("<in> malloc str struct has \"%s\" as string, and a length of %d\n", return_struct.str_ptr, return_struct.str_len);
    return return_struct;
}