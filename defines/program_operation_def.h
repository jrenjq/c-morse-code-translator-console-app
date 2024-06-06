#ifndef PROGRAM_OPERATION_DEF
#define PROGRAM_OPERATION_DEF

// for program operation.
#define CONFIG_ARGUMENTS_PATH "config/arguments.toml"
#define KEY_LOOKING_FOR "required_flags"
#define ENCLOSING_CHAR_STR "\""
#define MAX_CHAR_PER_LINE 256  // MUST ensure this value >= max expected chars of each line in config file! BUT if too big causes seg fault or value truncation.
#define MAX_FLAGS_ALLOWED 256  // MUST ensure this value >= max expected flags possible in the config file! BUT if too big causes seg fault or value truncation.

#endif