#ifndef PROGRAM_OPERATION_DEF
#define PROGRAM_OPERATION_DEF

// customise program operation (change at your own risk).
// user arguments processing.
#define CONFIG_ARGUMENTS_PATH "config/arguments.toml"
#define KEY_LOOKING_FOR "allowed_flags"
#define ENCLOSING_CHAR_STR "\""
#define MAX_CHAR_PER_LINE 256  // MUST ensure this value >= max expected chars of each line in config file! BUT if too big causes seg fault or value truncation.
#define MAX_FLAGS_ALLOWED 256  // MUST ensure this value >= max expected flags possible in the config file! BUT if too big causes seg fault or value truncation.
// morse code file processing.
#define MORSE_CODE_INPUT_PATH "morse_code_input/morse_code_input.txt"
#define MAX_NUM_MORSE_CODE_CHAR 5
#define MORSE_CHAR_COUNT 36

// tied to ground truth constants (do not change).
#define REQUIRED_FLAGS_COUNT 4

#endif