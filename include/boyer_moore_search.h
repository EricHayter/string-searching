#pragma once

#include <string_view>

std::size_t boyer_moore_search(std::string_view pattern, std::string_view text);
