#include "hash_utils.h"

bool add_string_array_into_hash(hashable_string_struct** head_ptr,  // ptr to ptr of the hash head, since hash add fn needs actual pointer but C arg is pass-by-value.
                                const int32_t STR_ARR_LEN,
                                const int32_t PER_STR_LEN,
                                char (*str_arr)[PER_STR_LEN],
                                const bool DEBUG_MODE) {
    hashable_string_struct* s = NULL;  // placeholder pointer to a malloc-ed struct.
    for (size_t i = 0; i < STR_ARR_LEN; i++) {
        s = (hashable_string_struct *) malloc(sizeof *s);  // malloc hashable string struct (incl. the char* pointer variable, but not the actual str).
        if (s == NULL) {
            (void)fprintf(stderr, "ERROR: unable to allocate memory via malloc!\nAborting!");
            return false;
        }
        s->string_malloc = str_arr[i];  // point it to the head of the string, which exists in the scope where the function is called.
        HASH_ADD_KEYPTR(hh, *head_ptr, s->string_malloc, strlen(s->string_malloc), s);  // adds the hashable string struct into the hash
        if (DEBUG_MODE) {
            printf("<add_string_array_into_hash> str_arr_len is %d, per_str_len is %d, string is %s\n and it is %s inside struct.\n", STR_ARR_LEN, PER_STR_LEN, str_arr[i], s->string_malloc);
        }
    }
    return true;
}