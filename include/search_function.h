#pragma once

#include <functional>
#include <string_view>

/* Interface for all string searching functions
 *
 * Searches for the occurrence of pattern inside of text and returns the index
 * of the first character of the match. If no occurrence of pattern is found in
 * text then return std::string::npos */
using StringSearchFunction =
    std::function<std::size_t(std::string_view pattern, std::string_view text)>;
