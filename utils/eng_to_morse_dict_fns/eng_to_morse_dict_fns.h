#ifndef ENG_TO_MORSE_DICT_FNS
#define ENG_TO_MORSE_DICT_FNS

#include "../../lib/dict_lib/dict_fixed_size.h"

/*
** parameter: 
**    - (none)
** action:
**    - prints out a description of the flag and value.
** returns:
**    - string_dict_fixed_size*: pointer to this struct on the heap.
*/
string_dict_fixed_size* init_str_dict_fs_morse_to_eng();

#endif