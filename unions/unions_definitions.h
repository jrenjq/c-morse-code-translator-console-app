#ifndef UNION_DEFINITIONS
#define UNION_DEFINITIONS

#include "../defines/program_operation_def.h"

typedef union morse_symbols_union {  // using union so that the struct members can be iterated like an array.
    struct morse_symbols_struct { 
        char DOT[MAX_CHAR_PER_LINE]; 
        char DASH[MAX_CHAR_PER_LINE]; 
        char LETTER[MAX_CHAR_PER_LINE]; 
        char WORD[MAX_CHAR_PER_LINE]; 
    } morse_symbols_struct;  // holds the morse symbols in a struct. rmb to declare its variable.
    
    // required_flags_count is tied to number of struct members = 4.
    char morse_symbols_members_arr[REQUIRED_FLAGS_COUNT][MAX_CHAR_PER_LINE];  // ensure the [m] x [n] = total struct members chars.
} morse_symbols_union;

#endif