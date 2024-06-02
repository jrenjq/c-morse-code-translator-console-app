#include "str_utils.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int32_t count_substrings(char* haystack, char* needle, int32_t needle_length) {
    // find how many needles there are in the haystack.
    int32_t needle_count = 0;
    if (needle_length > 0) {
        while(haystack = strstr(haystack, needle)) {  // move the cursor to wherever the needle is, ends if there are no more needles.
            needle_count++;  // increment the number of needles encountered.
            haystack += needle_length;  // increment cursor on the haystack by the length of the needle. this prevents overlapping hits.
        }
    }
    return needle_count;
}
