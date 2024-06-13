#include "./eng_to_morse_dict_fns.h"
#include "../../defines/program_operation_def.h"
#include "../../defines/english_morse_dict.h"

string_dict_fixed_size* init_str_dict_fs_morse_to_eng() {
    string_dict_fixed_size* str_dict_fs_ptr;
    new_fs_str_dict(str_dict_fs_ptr, MORSE_CHAR_COUNT);

    // fill the dictionary with morse string as key and english equivalent as value.
    add_entry_fs_str_dict(str_dict_fs_ptr, A_morse, "A"); add_entry_fs_str_dict(str_dict_fs_ptr, B_morse, "B");
    add_entry_fs_str_dict(str_dict_fs_ptr, C_morse, "C"); add_entry_fs_str_dict(str_dict_fs_ptr, D_morse, "D");
    add_entry_fs_str_dict(str_dict_fs_ptr, E_morse, "E"); add_entry_fs_str_dict(str_dict_fs_ptr, F_morse, "F");
    add_entry_fs_str_dict(str_dict_fs_ptr, G_morse, "G"); add_entry_fs_str_dict(str_dict_fs_ptr, H_morse, "H");
    add_entry_fs_str_dict(str_dict_fs_ptr, I_morse, "I"); add_entry_fs_str_dict(str_dict_fs_ptr, J_morse, "J");
    add_entry_fs_str_dict(str_dict_fs_ptr, K_morse, "K"); add_entry_fs_str_dict(str_dict_fs_ptr, L_morse, "L");
    add_entry_fs_str_dict(str_dict_fs_ptr, M_morse, "M"); add_entry_fs_str_dict(str_dict_fs_ptr, N_morse, "N");
    add_entry_fs_str_dict(str_dict_fs_ptr, O_morse, "O"); add_entry_fs_str_dict(str_dict_fs_ptr, P_morse, "P");
    add_entry_fs_str_dict(str_dict_fs_ptr, Q_morse, "Q"); add_entry_fs_str_dict(str_dict_fs_ptr, R_morse, "R");
    add_entry_fs_str_dict(str_dict_fs_ptr, S_morse, "S"); add_entry_fs_str_dict(str_dict_fs_ptr, T_morse, "T");
    add_entry_fs_str_dict(str_dict_fs_ptr, U_morse, "U"); add_entry_fs_str_dict(str_dict_fs_ptr, V_morse, "V");
    add_entry_fs_str_dict(str_dict_fs_ptr, W_morse, "W"); add_entry_fs_str_dict(str_dict_fs_ptr, X_morse, "X");
    add_entry_fs_str_dict(str_dict_fs_ptr, Y_morse, "Y"); add_entry_fs_str_dict(str_dict_fs_ptr, Z_morse, "Z");
    add_entry_fs_str_dict(str_dict_fs_ptr, morse_1, "1"); add_entry_fs_str_dict(str_dict_fs_ptr, morse_2, "2");
    add_entry_fs_str_dict(str_dict_fs_ptr, morse_3, "3"); add_entry_fs_str_dict(str_dict_fs_ptr, morse_4, "4");
    add_entry_fs_str_dict(str_dict_fs_ptr, morse_5, "5"); add_entry_fs_str_dict(str_dict_fs_ptr, morse_6, "6");
    add_entry_fs_str_dict(str_dict_fs_ptr, morse_7, "7"); add_entry_fs_str_dict(str_dict_fs_ptr, morse_8, "8");
    add_entry_fs_str_dict(str_dict_fs_ptr, morse_9, "9"); add_entry_fs_str_dict(str_dict_fs_ptr, morse_0, "0");
}