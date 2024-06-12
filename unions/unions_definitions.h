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

// dictionary template for morse code to english alphabet and numbers.
typedef union english_morse_dict_union {
    struct english_morse_dict_struct {
        char a_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char b_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char c_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char d_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char e_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char f_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char g_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char h_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char i_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char j_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char k_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char l_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char m_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char n_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char o_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char p_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char q_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char r_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char s_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char t_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char u_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char v_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char w_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char x_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];
        char y_morse    [MAX_NUM_MORSE_CODE_CHAR + 1]; char z_morse    [MAX_NUM_MORSE_CODE_CHAR + 1];

        char morse_one  [MAX_NUM_MORSE_CODE_CHAR + 1]; char morse_two  [MAX_NUM_MORSE_CODE_CHAR + 1];
        char morse_three[MAX_NUM_MORSE_CODE_CHAR + 1]; char morse_four [MAX_NUM_MORSE_CODE_CHAR + 1];
        char morse_five [MAX_NUM_MORSE_CODE_CHAR + 1]; char morse_six  [MAX_NUM_MORSE_CODE_CHAR + 1];
        char morse_seven[MAX_NUM_MORSE_CODE_CHAR + 1]; char morse_eight[MAX_NUM_MORSE_CODE_CHAR + 1];
        char morse_nine [MAX_NUM_MORSE_CODE_CHAR + 1];
    } english_morse_dict_struct;  

    // enables the struct members of same data type to be iterated over.
    char english_morse_dict_struct_arr[NUM_ENG_MORSE_DICT_STRUCT_MEMBERS][MAX_NUM_MORSE_CODE_CHAR + 1];
} english_morse_dict_union;

#endif