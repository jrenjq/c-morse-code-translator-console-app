#ifndef STRUCTS_DEFINITIONS
#define STRUCTS_DEFINITIONS

#include <stdio.h>
#include <stdlib.h>

#include "../lib/hash_map_lib/src/uthash.h"

// for saving user argument's flag and value pair.
typedef struct flag_and_value {
    size_t flag_argno;   // indicates which argument number the FLAG is.
    char* flag;          // an argument which starts with '-'.
    size_t value_argno;  // indicates which argument number the VALUE is.
    char* value;         // an argument that follows a flag.
} flag_and_value;

// for hashing string inside a hash table.
typedef struct hashable_string_struct {
    char* string_malloc;    // the malloc-ed string (length unnecessary).
    UT_hash_handle hh;      // required by hash library.
} hashable_string_struct;

// for returning both pointer to string on heap & its length.
typedef struct malloc_str {
    char* str_ptr;      // the malloc-ed string.
    int32_t str_len;    // length of the malloc-ed string.
} malloc_str;

// for parsing user arguments from argv.
struct enclosing_char_start_end {
    char* start;
    char* end;
};

#endif