#include "naive_search.h"

#include <string>

std::size_t naive_search(std::string_view pattern, std::string_view text) {
    for (int i = 0; i < text.size() - (pattern.size() - 1); i++) {
        int j;
        for (j = 0; j < pattern.size(); j++) {
            if (pattern[j] != text[i + j])
                break;
        }
        if (j == pattern.size())
            return i;
    }

    return std::string::npos;
}
