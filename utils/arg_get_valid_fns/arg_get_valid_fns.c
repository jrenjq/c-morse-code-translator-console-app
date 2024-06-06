#include "arg_get_valid_fns.h"
#include "../str_utils/str_utils.h"

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

void get_flags_from_line(struct enclosing_char_start_end* enclosing_char_start_end_struct_array_ptr,
                         const int32_t ENCLOSING_CHAR_START_END_STRUCT_ARRAY_LEN,
                         char* line_of_text,
                         const int32_t MAX_LINE_OF_TEXT_LEN,
                         const char* ENCLOSING_CHAR_STR,
                         char (*copy_flags_here_str_array) [MAX_LINE_OF_TEXT_LEN]) {  // char (*p) [100] -> p is pointer to a 100 char array (anticlock spiral).
    int32_t char_count = 0;  // keep track of how many ENCLOSING_CHAR_STR encountered.
    int32_t pair_count = 0;  // keep track of how many pairs of the ENCLOSING_CHAR_STR we have encountered.
    while(line_of_text = strstr(line_of_text, ENCLOSING_CHAR_STR)) {  // move the cursor to wherever the needle character is, ends if there are no more needles.
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
    char required_flags_str_array[ENCLOSING_CHAR_START_END_STRUCT_ARRAY_LEN][MAX_LINE_OF_TEXT_LEN];  // an array of strings with just enough elements to hold the required flags.
    for (size_t i = 0; i < ENCLOSING_CHAR_START_END_STRUCT_ARRAY_LEN; i++) {
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
    }
    return;
}

int32_t get_flags_from_config_file_by_pointer(const char* CONFIG_ARGUMENTS_PATH, 
                                              const char* KEY_LOOKING_FOR, 
                                              const char* ENCLOSING_CHAR_STR, 
                                              const int32_t MAX_CHAR_PER_LINE,
                                              const int32_t MAX_FLAGS_ALLOWED,
                                              char (*retrieve_flags_str_array) [MAX_CHAR_PER_LINE],
                                              const bool DEBUG_MODE) {
    // opening the file with the required flags, as a pointer to a file stream.
    FILE* read_file_stream_ptr = read_file_and_return_file_stream(CONFIG_ARGUMENTS_PATH);
    
    // read the file stream, given pointer to line from file. saves line from file to the pointer if found key and returns true. else returns false.
    char line_from_file[MAX_CHAR_PER_LINE];  // avoided malloc() approach as per NASA The Power of 10: Rule 3.
    if (read_file_stream_and_copy_found_line(read_file_stream_ptr, line_from_file, MAX_CHAR_PER_LINE, (char*)KEY_LOOKING_FOR)) {
        int32_t enclosing_char_count = count_substrings(line_from_file, ENCLOSING_CHAR_STR, strlen(ENCLOSING_CHAR_STR));
        // error-handling when double quotes don't match, there aren't any required flags, etc.
        if(enclosing_char_count % 2 != 0) {  // double quotes don't form a pair.
            (void)fprintf(stderr, "ERROR: mismatch in %s in %s.\n"
                                    "Please ensure configuration file is as follows:\n"
                                    "[flags]\n"
                                    "required_flags = [%s-<flag>%s, %s-<flag>%s, %s-<flag>%s, %s-<flag>%s]!\n"
                                    "Aborting!\n",
                                    ENCLOSING_CHAR_STR,
                                    CONFIG_ARGUMENTS_PATH,
                                    ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, 
                                    ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR);
            return -1;
        }
        if(enclosing_char_count == 0) {  // there are no double quotes i.e. no required arguments.
            (void)fprintf(stderr, "ERROR: no %s<flag>%s found in %s.\n"
                                    "Please ensure configuration file is as follows:\n"
                                    "[flags]\n"
                                    "required_flags = [%s-<flag>%s, %s-<flag>%s, %s-<flag>%s, %s-<flag>%s]\n"
                                    "Aborting!\n",
                                    ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR,
                                    CONFIG_ARGUMENTS_PATH,
                                    ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, 
                                    ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR);
            return 0;
        }

        int32_t required_flags_count = enclosing_char_count / 2;

        if(DEBUG_MODE) {
            printf("required flags count: %d\n", required_flags_count);
            printf("enclosing chars count: %d\n", enclosing_char_count);
        }

        struct enclosing_char_start_end enclosing_char_start_end_struct_array[required_flags_count];
        char flags_from_line[required_flags_count][MAX_CHAR_PER_LINE];
        get_flags_from_line(enclosing_char_start_end_struct_array, required_flags_count, line_from_file, MAX_CHAR_PER_LINE, ENCLOSING_CHAR_STR, flags_from_line);
        for (size_t i = 0; i < required_flags_count; i++) {
            strcpy(retrieve_flags_str_array[i], flags_from_line[i]);
        }
        if(DEBUG_MODE) {
            for (size_t i = 0; i < required_flags_count; i++) {
                printf("%ld has %s\n", i, retrieve_flags_str_array[i]);
            }
        }
        return required_flags_count;
    } else {
        (void)fprintf(stderr, "ERROR: key \"%s\" not found in file \"%s\".\n"
                               "Please ensure configuration file is as follows:\n"
                               "[flags]\n"
                               "required_flags = [%s-<flag>%s, %s-<flag>%s, %s-<flag>%s, %s-<flag>%s]\n"
                               "Aborting!\n", 
                               KEY_LOOKING_FOR,
                               CONFIG_ARGUMENTS_PATH,
                               ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, 
                               ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR, ENCLOSING_CHAR_STR);
        return -1;
    }
}