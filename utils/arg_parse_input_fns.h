#ifndef ARG_PARSE_FNS
#define ARG_PARSE_FNS

#include <stdio.h>
#include <stdbool.h>

struct flag_and_value {  // pair of flag and value.
    size_t flag_argno;   // indicates which argument number the FLAG is.
    char* flag;          // an argument which starts with '-'.
    size_t value_argno;  // indicates which argument number the VALUE is.
    char* value;         // an argument that follows a flag.
};

void print_flag_and_value(struct flag_and_value* my_flag_and_value_ptr);
bool are_arguments_valid(int argc, char* argv[], char** argument_flags_allowed, size_t current_index);
void populate_flag_and_value_array(struct flag_and_value* flag_and_value_array_ptr, size_t flag_and_value_array_size, size_t current_index, char* argv[]);
bool parse_user_arguments(int argc, char** argv, char** argument_flags_allowed, struct flag_and_value* flag_and_value_array_ptr, size_t flag_and_value_array_ptr_size, bool debug);

#endif