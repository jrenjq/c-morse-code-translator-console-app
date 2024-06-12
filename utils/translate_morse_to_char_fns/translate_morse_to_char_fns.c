#include "./translate_morse_to_char_fns.h"
#include "../../defines/english_morse_dict.h"
#include "../../unions/unions_definitions.h"
#include "../../lib/dict_lib/dict_fixed_size.h"

malloc_str translate_morse_to_english(malloc_str* morse_malloc_str_struct, const int32_t LETTER_COUNT, const int32_t WORD_COUNT, const bool DEBUG_MODE) {
    // assign a malloc string to hold the translated text. total char = (word_count - 1) + letter_count, where (word_count - 1) is number of spaces.
    malloc_str english_malloc_str_struct = {
        .str_ptr = (char*) malloc( (WORD_COUNT - 1) + LETTER_COUNT + 1 ),  // +1 at the end for null terminator.
        .str_len = (WORD_COUNT - 1) + LETTER_COUNT,
    };
    english_malloc_str_struct.str_ptr[english_malloc_str_struct.str_len] = '\0';
    if (DEBUG_MODE) printf("<in> morse_str has \"%s\" string, length of %d.\n", morse_malloc_str_struct->str_ptr, morse_malloc_str_struct->str_len);

    // using a string buffer, iterate and copy each morse character into the buffer until the letter delimiter.
    // when a letter delimiter is encountered, translate the morse string into an english character, and append it into the translation string. flush the string buffer.
    // when a word delimiter is encountered, append a space into the translation string.
    // char ch_buffer[256];  // maximum 255 characters + 1 null terminator.
    // for (size_t i = 0; i < morse_malloc_str_struct->str_len; i++) {  // iterate through the morse string.
    //     // printf("%c\n", morse_malloc_str_struct->str_ptr[i]);
    // }

    string_dict_fixed_size* str_dict_fs_ptr;
    new_fs_str_dict(str_dict_fs_ptr, 5);

    printf("length is %ld\n", str_dict_fs_ptr->max_length);
    printf("next free index is %ld\n", str_dict_fs_ptr->next_free_index);

    bool is_entry_added;
    add_entry_fs_str_dict(str_dict_fs_ptr, "Foo", "Bar", &is_entry_added); is_entry_added = false;
    add_entry_fs_str_dict(str_dict_fs_ptr, "Faz", "Baz", &is_entry_added); is_entry_added = false;

    printf("length is %ld\n", str_dict_fs_ptr->max_length);
    printf("next free index is %ld\n", str_dict_fs_ptr->next_free_index);
    printf("key 0 is %s\n", str_dict_fs_ptr->key[0]);
    printf("value 0 is %s\n", str_dict_fs_ptr->value[0]);
    printf("key 1 is %s\n", str_dict_fs_ptr->key[1]);
    printf("value 1 is %s\n", str_dict_fs_ptr->value[1]);

    for (size_t i = 0; i < NUM_ENG_MORSE_DICT_STRUCT_MEMBERS; i++) {

    }
}