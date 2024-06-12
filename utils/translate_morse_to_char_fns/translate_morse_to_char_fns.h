#ifndef TRANSLATE_MORSE_TO_CHAR_FNS
#define TRANSLATE_MORSE_TO_CHAR_FNS

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../structs/structs_definitions.h"

malloc_str translate_morse_to_english(malloc_str* morse_malloc_str_struct, const int32_t LETTER_COUNT, const int32_t WORD_COUNT, const bool DEBUG_MODE);

#endif