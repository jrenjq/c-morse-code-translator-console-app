#ifndef CUSTOM_DICT
#define CUSTOM_DICT

#include <stddef.h>

// fixed size implementation via arrays = O(1) search via index. good for dicts that don't change.
typedef struct string_dict_fixed_size {
    char** key;              // array of string, malloced on the heap.
    char** value;            // array of string, malloced on the heap.
    size_t max_length;       // length of each array of strings = maximum entries dict can have.
    size_t next_free_index;  // increment after each new entry. when next_free_index == max_length, fixed-size dict is full.
} string_dict_fixed_size;

// array of string is allocated on the heap.
#define new_fs_str_dict(string_dict_fs_ptr, string_dict_fs_max_length) do {                 \
    string_dict_fs_ptr = (string_dict_fixed_size*) malloc(sizeof(string_dict_fixed_size));  \
    string_dict_fs_ptr->key = (char**) malloc(sizeof(char*) * string_dict_fs_max_length);   \
    string_dict_fs_ptr->value = (char**) malloc(sizeof(char*) * string_dict_fs_max_length); \
    string_dict_fs_ptr->max_length = string_dict_fs_max_length;                             \
    string_dict_fs_ptr->next_free_index = 0;                                                \
} while(0)

// function caller must ensure key_string and value_string are null terminated.
#define add_entry_fs_str_dict(string_dict_fs_ptr, key_string, value_string, is_entry_added_ptr) do {                                    \
    if (string_dict_fs_ptr->next_free_index < string_dict_fs_ptr->max_length) {                                                         \
        string_dict_fs_ptr->key[string_dict_fs_ptr->next_free_index] = (char*) malloc(sizeof(char) * (strlen(key_string) + 1));         \
        strncpy(string_dict_fs_ptr->key[string_dict_fs_ptr->next_free_index], key_string, strlen(key_string) + 1);                      \
        string_dict_fs_ptr->value[string_dict_fs_ptr->next_free_index] = (char*) malloc(sizeof(char) * (strlen(value_string) + 1));     \
        strncpy(string_dict_fs_ptr->value[string_dict_fs_ptr->next_free_index], value_string, strlen(value_string) + 1);                \
        string_dict_fs_ptr->next_free_index += 1;                                                                                       \
        *is_entry_added_ptr = true;                                                                                                     \
    } else {                                                                                                                            \
        *is_entry_added_ptr = false;                                                                                                    \
    }                                                                                                                                   \
} while(0)

#endif