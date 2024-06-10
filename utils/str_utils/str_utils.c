#include "str_utils.h"

#include <string.h>

int32_t count_substrings(char* haystack, const char* NEEDLE, int32_t needle_length) {
    // find how many NEEDLEs there are in the haystack.
    int32_t needle_count = 0;
    if (needle_length > 0) {
        while(haystack = strstr(haystack, NEEDLE)) {  // move the cursor to wherever the NEEDLE is, ends if there are no more NEEDLEs.
            needle_count++;  // increment the number of needles encountered.
            haystack += needle_length;  // increment cursor on the haystack by the length of the NEEDLE. this prevents overlapping hits.
        }
    }
    return needle_count;
}

