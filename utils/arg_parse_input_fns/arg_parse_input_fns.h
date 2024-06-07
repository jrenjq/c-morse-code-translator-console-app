#ifndef ARG_PARSE_FNS
#define ARG_PARSE_FNS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

struct flag_and_value {  // pair of flag and value.
    size_t flag_argno;   // indicates which argument number the FLAG is.
    char* flag;          // an argument which starts with '-'.
    size_t value_argno;  // indicates which argument number the VALUE is.
    char* value;         // an argument that follows a flag.
};

/*
** parameter: 
**    - struct flag_and_value* my_flag_and_value_ptr: pointer to a struct flag_and_value.
** action:
**    - prints out a description of the flag and value.
** returns:
**    - void.
*/
void print_flag_and_value(struct flag_and_value* my_flag_and_value_ptr);

/*
** parameter: 
**    - int argc: number of arguments received.
**    - char* argv[]: array of argument strings.
** action:
**    - error-handling based on argument array and size.
**    - intended for return value to tell main function whether to continue or abort.
** returns:
**    - bool: <true> when arguments are all valid. <false> when something isn't right.
*/
bool are_arguments_valid(int argc, char* argv[], size_t current_index);

/*
** parameter: 
**    - struct flag_and_value** flag_and_value_array_ptr: a pointer to the array of struct flag_and_value header.
**    - size_t flag_and_value_array_size: size of the flag_and_value_array (which is lost due to array-pointer decay).
**    - size_t current_index: current index from the calling function.
**    - char* argv[]: array of argument strings.
** action:
**    - creates a struct with the necessary values and places it into the flag_and_value_array via pointer.
** returns:
**    - void.
*/
void populate_flag_and_value_array(struct flag_and_value* flag_and_value_array_ptr, int32_t flag_and_value_array_size, size_t current_index, char* argv[]);

/*
** parameter: 
**    - int argc: number of arguments received.
**    - char* argv[]: array of argument strings.
**    - struct flag_and_value* flag_and_value_array_ptr: pointer to header of flag_and_value array.
**    - size_t flag_and_value_array_ptr_size: size of flag_and_value array.
**    - bool debug: <true> to display debug info on console, <false> to omit.
** action:
**    - does argument error-handling function.
**    - populate arguments into struct flag_and_value array.
**    - (optional) displays debugging information.
** returns:
**    - bool: <true> for successful execution, <false> for error.
*/
bool parse_user_arguments(int argc, char** argv, struct flag_and_value* flag_and_value_array_ptr, int32_t flag_and_value_array_ptr_size, bool debug);

#endif