#include "get_morse_symbols_from_args.h"

bool get_morse_symbols_from_args(morse_symbols_union* morse_symbols_union_ptr, 
                                 const flag_and_value* FLAG_AND_VALUE_ARR, 
                                 const int32_t FLAG_AND_VALUE_ARR_LEN,
                                 const bool DEBUG_MODE) {
    // assign user's definition of morse code symbols into the struct for reference later.
    for (size_t i = 0; i < FLAG_AND_VALUE_ARR_LEN; i++) {
        if (DEBUG_MODE) ("comparing %s...\n", FLAG_AND_VALUE_ARR[i].flag);
        // Note: it's quite funny how strcmp returns 0 but it actually makes sense when one reads the documentation.
        if (strcmp(FLAG_AND_VALUE_ARR[i].flag, "-dot") == 0) {  // if the user entered a flag for dot ...
            if (DEBUG_MODE) printf("assigning to dot!\n");
            strcpy(morse_symbols_union_ptr->morse_symbols_struct.DOT, FLAG_AND_VALUE_ARR[i].value);  // ... assign the flag's value to the corr morse code chart.
        } else if (strcmp(FLAG_AND_VALUE_ARR[i].flag, "-dash") == 0) {  // if the user entered a flag for dash ...
            if (DEBUG_MODE) printf("assigning to dash!\n");
            strcpy(morse_symbols_union_ptr->morse_symbols_struct.DASH, FLAG_AND_VALUE_ARR[i].value);  // ... assign the flag's value to the corr morse code chart.
        } else if (strcmp(FLAG_AND_VALUE_ARR[i].flag, "-letter") == 0) {  // if the user entered a flag for letter ...
            if (DEBUG_MODE) printf("assigning to letter!\n");
            strcpy(morse_symbols_union_ptr->morse_symbols_struct.LETTER, FLAG_AND_VALUE_ARR[i].value);  // ... assign the flag's value to the corr morse code chart.
        } else if (strcmp(FLAG_AND_VALUE_ARR[i].flag, "-word") == 0) {  // if the user entered a flag for word ...
            if (DEBUG_MODE) printf("assigning to word!\n");
            strcpy(morse_symbols_union_ptr->morse_symbols_struct.WORD, FLAG_AND_VALUE_ARR[i].value);  // ... assign the flag's value to the corr morse code chart.
        } else {
            return false;  // an unwanted user argument flag. something has gone wrong.
        }
    }

    // ensure that all members of the struct has been filled. else return false to indicate error.
    for (size_t i = 0; i < REQUIRED_FLAGS_COUNT; i++) {
        if (strcmp(morse_symbols_union_ptr->morse_symbols_members_arr[i], "") == 0) {  // missing argument results in "" string for that struct member.
            (void)fprintf(stderr, "ERROR: missing one or more required arguments!\n"
                                  "Please ensure the '-dot', '-dash', '-letter', and '-word' flags (and their values) are present!\n"
                                  "Aborting!\n");
            return false;
        }
    }

    return true;
}