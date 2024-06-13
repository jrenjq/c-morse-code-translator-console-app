#ifndef CUSTOM_DICT
#define CUSTOM_DICT

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// fixed size implementation via arrays = O(1) search via index. good for dicts that don't change.
typedef struct string_dict_fixed_size {  // also malloced on the heap.
    char** key;              // array of string, malloced on the heap.
    char** value;            // array of string, malloced on the heap.
    size_t max_length;       // length of each array of strings = maximum entries dict can have.
    size_t next_free_index;  // increment after each new entry. when next_free_index == max_length, fixed-size dict is full.
} string_dict_fixed_size;

// array of string is allocated on the heap.
#define new_fs_str_dict(string_dict_fs_ptr, string_dict_fs_max_length) do {                                                         \
    string_dict_fs_ptr = (string_dict_fixed_size*) malloc(sizeof(string_dict_fixed_size));                                          \
    string_dict_fs_ptr->key = (char**) malloc(sizeof(char*) * string_dict_fs_max_length);                                           \
    string_dict_fs_ptr->value = (char**) malloc(sizeof(char*) * string_dict_fs_max_length);                                         \
    string_dict_fs_ptr->max_length = string_dict_fs_max_length;                                                                     \
    string_dict_fs_ptr->next_free_index = 0;                                                                                        \
} while(0)

// free malloced members and the struct itself, and set pointer to the struct itself to null.
#define free_fs_str_dict(string_dict_fs_ptr) do {                                                                                   \
    for (size_t i = 0; i < string_dict_fs_ptr->max_length; i++) {                                                                   \
        free(string_dict_fs_ptr->key[i]);                                                                                           \
        free(string_dict_fs_ptr->value[i]);                                                                                         \
    }                                                                                                                               \
    free(string_dict_fs_ptr->key);                                                                                                  \
    free(string_dict_fs_ptr->value);                                                                                                \
    free(string_dict_fs_ptr);                                                                                                       \
    string_dict_fs_ptr = NULL;                                                                                                      \
} while(0)

// function caller must ensure key_string and value_string are null terminated.
// function caller should  ensure fixed-size dict is not full, before calling this function (e.g. via 'is_full_fs_str_dict' function).
#define add_entry_fs_str_dict(string_dict_fs_ptr, key_string, value_string) do {                                                    \
    string_dict_fs_ptr->key[string_dict_fs_ptr->next_free_index] = (char*) malloc(sizeof(char) * (strlen(key_string) + 1));         \
    strncpy(string_dict_fs_ptr->key[string_dict_fs_ptr->next_free_index], key_string, strlen(key_string) + 1);                      \
    string_dict_fs_ptr->value[string_dict_fs_ptr->next_free_index] = (char*) malloc(sizeof(char) * (strlen(value_string) + 1));     \
    strncpy(string_dict_fs_ptr->value[string_dict_fs_ptr->next_free_index], value_string, strlen(value_string) + 1);                \
    string_dict_fs_ptr->next_free_index += 1;                                                                                       \
} while(0)

// checks if the fixed-size string dict is full by comparing next_free_index member to maximum length.
#define is_full_fs_str_dict(string_dict_fs_ptr, is_full_bool_ptr) do {                                                              \
    *is_full_bool_ptr = (string_dict_fs_ptr->next_free_index >= string_dict_fs_ptr->max_length);                                    \
} while(0)

// gets value corresponding to found key. value is malloced on heap. malloc_value_string remains unchanged if nothing is found.
#define get_value_fs_str_dict(string_dict_fs_ptr, key_string, malloc_value_string) do {                                             \
    for (size_t i = 0; i < string_dict_fs_ptr->next_free_index; i++) {                                                              \
        if (strcmp(string_dict_fs_ptr->key[i], key_string) == 0) {                                                                  \
            malloc_value_string = malloc(sizeof(char) * (strlen(string_dict_fs_ptr->value[i]) + 1));                                \
            strncpy(malloc_value_string, string_dict_fs_ptr->value[i], strlen(string_dict_fs_ptr->value[i]) + 1);                   \
            break;                                                                                                                  \
        }                                                                                                                           \
    }                                                                                                                               \
} while(0)

// convenience macro to free and null the pointer.
#define free_and_null_ptr(ptr) do {                                                                                                 \
    free(ptr);                                                                                                                      \
    ptr = NULL;                                                                                                                     \
} while(0)

#endif