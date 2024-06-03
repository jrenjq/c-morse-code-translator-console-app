#include "arg_parse_input_fns.h"

/*
** parameter: 
**    - struct flag_and_value* my_flag_and_value_ptr: pointer to a struct flag_and_value.
** action:
**    - prints out a description of the flag and value.
** returns:
**    - void.
*/
void print_flag_and_value(struct flag_and_value* my_flag_and_value_ptr) {
    (void)printf("** flag_argno: %ld, flag: %s, value_argno: %ld, value: %s **\n", 
                    my_flag_and_value_ptr->flag_argno, 
                    my_flag_and_value_ptr->flag, 
                    my_flag_and_value_ptr->value_argno, 
                    my_flag_and_value_ptr->value
                );
    return;
}

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
bool are_arguments_valid(int argc, char* argv[], char** argument_flags_allowed, size_t current_index) {
    // argument syntax validation.
    if (current_index + 2 > argc) {  // this is an error where in the next pair, there is a flag without a value or a value without a flag etc.
        (void)fprintf(stderr, "ERROR: missing arguments before/after argument \"%s\" at argument number %ld.\n"
                              "Please ensure arguments are given in the form: \"<file name> <flag> <value> <flag> <value>...\" OR \"<file name> <flag> <value>\" OR \"<file name>\".\n"
                              "Aborting!\n", 
                              argv[current_index], current_index);
        return false;
    }
    if (argv[current_index][0] != '-') {  // if the <flag> does not have '-' as first character in the string, it is not valid and should throw an error.
        (void)fprintf(stderr, "ERROR: invalid flag syntax in \"%s\" at argument number %ld.\n"
                              "Please ensure that when using \"<file name> <flag> <value>...\", the <flag> should start with \'-\'.\n"
                              "Aborting!\n", 
                              argv[current_index], current_index);
        return false;
    }
    if (strlen(argv[current_index]) <= 1) {  // if the <flag> does not have characters after the '-', it is not valid and should throw an error.
        (void)fprintf(stderr, "ERROR: invalid flag syntax in \"%s\" at argument number %ld.\n"
                              "Please ensure that when using \"<file name> <flag> <value>...\", the <flag> should contain characters after the \'-\'.\n"
                              "Aborting!\n", 
                              argv[current_index], current_index);
        return false;
    }
    // argument content validation.
    return true;
}

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
void populate_flag_and_value_array(struct flag_and_value* flag_and_value_array_ptr, int32_t flag_and_value_array_size, size_t current_index, char* argv[]) {
    struct flag_and_value this_flag_and_value = {   // create a struct for flag and value pair.
                                                    .flag_argno = current_index, 
                                                    .flag = argv[current_index], 
                                                    .value_argno = current_index+1, 
                                                    .value = argv[current_index+1] 
                                                };
    flag_and_value_array_ptr[(current_index-1)/2] = this_flag_and_value;  // saves this pair into the flag and value array via deferencing its pointer.
    return;
}

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
bool parse_user_arguments(int argc, char** argv, char** argument_flags_allowed, struct flag_and_value* flag_and_value_array_ptr, int32_t flag_and_value_array_ptr_size, bool debug) {
    if (argc >= INT_MAX) {  // ERROR: too many user-supplied arguments.
        (void)fprintf(stderr, "ERROR: too many arguments!\n"
                              "Please ensure there are less than %d number of arguments.\n"
                              "Aborting!\n", 
                              INT_MAX);
        return false;
    }
    if (argc > 1) {  // only do so if there are user-supplied arguments (1st arg is file name) AND not more than INT_MAX.
        for (size_t i = 1; i < argc; i += 2) {  // argv is either { <file name> <flag> <value> <flag> <value> ... } or { <file name> }. start from [1] and look at 2 at a time.
            if (!are_arguments_valid(argc, argv, argument_flags_allowed, i)) {  // argument error-handling function.
                return false;
            }
            populate_flag_and_value_array(flag_and_value_array_ptr, flag_and_value_array_ptr_size, i, argv); // save arguments into struct array function.
        }
        if (debug) {
            for (size_t i = 0; i < (size_t)((argc-1)/2); ++i) {  // for debugging purposes.
                print_flag_and_value(&flag_and_value_array_ptr[i]);
            }
        }
    }
    return true;
}