#include "./file_utils.h"

#include <string.h>

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
    return file_ptr;  // returns pointer to stream representing the file. SHOULD fclose() when done with the pointer.
}

int32_t count_characters_in_file(FILE* file_stream_ptr) {
    
    return 0;
}