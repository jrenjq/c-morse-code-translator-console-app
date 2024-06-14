#include "./translate_morse_to_char_fns.h"
#include "../eng_to_morse_dict_fns/eng_to_morse_dict_fns.h"
#include "../../defines/english_morse_dict.h"
#include "../../lib/dict_lib/dict_fixed_size.h"
#include "../../defines/program_operation_def.h"

malloc_str* translate_morse_to_english(malloc_str* morse_malloc_str_struct, const int32_t LETTER_COUNT, const int32_t WORD_COUNT, 
                                       morse_symbols_union* morse_symbols_ptr, const bool DEBUG_MODE) {
    // assign a malloc string to hold the translated text.
    malloc_str* english_malloc_str_struct_ptr = (malloc_str*) malloc(sizeof(malloc_str));
    english_malloc_str_struct_ptr->str_ptr = (char*) malloc( (WORD_COUNT - 1) + LETTER_COUNT + 1 );  // +1 at the end for null terminator.
    english_malloc_str_struct_ptr->str_len = (WORD_COUNT - 1) + LETTER_COUNT; // total char = (word_count - 1) + letter_count, (word_count - 1) is spaces count.
    english_malloc_str_struct_ptr->str_ptr[english_malloc_str_struct_ptr->str_len] = '\0';
    if (DEBUG_MODE) printf("<in> morse_str has \"%s\" string, length of %ld.\n", morse_malloc_str_struct->str_ptr, morse_malloc_str_struct->str_len);

    // using a string buffer, iterate and copy each morse character into the buffer until the letter delimiter.
    // encounter a letter delimiter: translate the morse string into an english character, and append it into the translation string. flush the string buffer.
    // encounter a word delimiter: append a space into the translation string.
    string_dict_fixed_size* str_dict_fs_ptr = init_str_dict_fs_morse_to_eng();  // dictionary for morse -> english.
    char ch_buffer[CH_BUFFER_SIZE];  // maximum 255 characters + 1 null terminator.
    size_t morse_ch_buffer_index = 0;  // to keep track of character buffer index.
    size_t eng_ch_buffer_index = 0;  // to keep track of the character in the translated string.
    char current_char;  // to save the iterated character.
    char* eng_char_malloc;  // translated english character.
    for (size_t i = 0; i < morse_malloc_str_struct->str_len; i++) {  // iterate through the morse string.
        current_char = morse_malloc_str_struct->str_ptr[i];
        if (current_char == morse_symbols_ptr->morse_symbols_struct.LETTER[0] ||  // letter delimiter = all morse char for one english char in buffer.
        i + 1 == morse_malloc_str_struct->str_len){  // last char in morse input = move it in buffer and all morse char for one english char will be in buffer.
            // ensure that the morse character buffer has the complete morse string, with null termination.
            if (i + 1 == morse_malloc_str_struct->str_len) {  // there is no letter/word delimiter at the last symbol / word.
                ch_buffer[morse_ch_buffer_index++] = current_char; // hence we will move the last character in and advance the buffer count.
            }
            ch_buffer[morse_ch_buffer_index] = '\0';  // delimit string in char buffer using null terminator.
            if (DEBUG_MODE) printf("<in>[%ld] buffer has %s ", i, ch_buffer);
            // translate morse string using the fixed-size dictionary (already initialised with morse->eng).
            get_value_fs_str_dict(str_dict_fs_ptr, ch_buffer, eng_char_malloc);
            if (eng_char_malloc != NULL) { 
                if (DEBUG_MODE) printf("<in>[%ld] %s found as %c!\n", i, ch_buffer, eng_char_malloc[0]);
                english_malloc_str_struct_ptr->str_ptr[eng_ch_buffer_index++] =  eng_char_malloc[0];
                if (DEBUG_MODE) printf("<in>[%ld] %c placed in %ld index in eng_buffer!\n", i, english_malloc_str_struct_ptr->str_ptr[eng_ch_buffer_index-1], eng_ch_buffer_index-1);
            } else {
                (void)fprintf(stderr, "ERROR: unrecognised morse string '%s' in 'morse_code_input/morse_code_input.txt'.\n"
                                      "Please ensure all morse letters are appended by '%c', and all morse words are appended by '%c'.\n"
                                      "Please also ensure there is no '%c' or '%c' as the first character of the input morse text!\n"
                                      "Aborting!\n",
                                        ch_buffer,
                                        morse_symbols_ptr->morse_symbols_struct.LETTER[0], morse_symbols_ptr->morse_symbols_struct.WORD[0],
                                        morse_symbols_ptr->morse_symbols_struct.LETTER[0], morse_symbols_ptr->morse_symbols_struct.WORD[0]);
                return NULL;
            }
            memset(ch_buffer, 0, CH_BUFFER_SIZE);  // flush character buffer.
            morse_ch_buffer_index = 0;  // reset character buffer index.
        } else if (current_char == morse_symbols_ptr->morse_symbols_struct.WORD[0]) {  // word delimiter = add a space.
            english_malloc_str_struct_ptr->str_ptr[eng_ch_buffer_index++] =  ' ';
            if (DEBUG_MODE) printf("<in>[%ld] %c placed in %ld index in eng_buffer!\n", i, english_malloc_str_struct_ptr->str_ptr[eng_ch_buffer_index-1], eng_ch_buffer_index-1);
        } else if (current_char == DOT_CHAR || current_char == DASH_CHAR) {  // move the dot and dash to build a morse string in character buffer.
            ch_buffer[morse_ch_buffer_index++] = current_char;
        } else {  // an unexpected character present in the morse code input file.
            (void)fprintf(stderr, "ERROR: invalid character '%c' in \"%s\".\n"
                                  "Please ensure the file contains only '%c', '%c', '%c', '%c', without spaces or line-breaks."
                                  "Aborting!\n",
                                  current_char, MORSE_CODE_INPUT_PATH, DOT_CHAR, DASH_CHAR,
                                  morse_symbols_ptr->morse_symbols_struct.LETTER[0], morse_symbols_ptr->morse_symbols_struct.WORD[0]);
            return NULL;
        }
    }
    english_malloc_str_struct_ptr->str_ptr[strlen(english_malloc_str_struct_ptr->str_ptr)] = '\0';  // terminate entire english str with null terminator.
    if (DEBUG_MODE) printf("<in> translated string is \"%s\"\n", english_malloc_str_struct_ptr->str_ptr);
    if (DEBUG_MODE) printf("<in> calculated length is: %ld\n", english_malloc_str_struct_ptr->str_len);
    if (DEBUG_MODE) printf("<in> actual length is %ld\n", strlen(english_malloc_str_struct_ptr->str_ptr));

    free_fs_str_dict(str_dict_fs_ptr);  // free the malloced morse->eng dict on the heap. no longer need it.

    return english_malloc_str_struct_ptr;
}