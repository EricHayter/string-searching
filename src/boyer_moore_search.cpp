#include "boyer_moore_search.h"

#include <algorithm>
#include <array>
#include <string>

// Build the bad character table for Boyer-Moore algorithm
static std::array<int, 256> build_bad_char_table(std::string_view pattern) {
  std::array<int, 256> bad_char;
  const int m = pattern.size();

  // Initialize all occurrences as -1
  bad_char.fill(-1);

  // Fill the actual value of last occurrence of a character
  for (int i = 0; i < m; i++) {
    bad_char[static_cast<unsigned char>(pattern[i])] = i;
  }

  return bad_char;
}

std::size_t boyer_moore_search(std::string_view pattern,
                               std::string_view text) {
  const int m = pattern.size();
  const int n = text.size();

  // Empty pattern or pattern larger than text
  if (m == 0 || m > n) {
    return std::string::npos;
  }

  // Build the bad character table
  auto bad_char = build_bad_char_table(pattern);

  int shift = 0; // shift of the pattern with respect to text

  while (shift <= (n - m)) {
    int j = m - 1;

    // Keep reducing index j of pattern while characters of
    // pattern and text are matching at this shift
    while (j >= 0 && pattern[j] == text[shift + j]) {
      j--;
    }

    // If the pattern is present at current shift, then index j
    // will become -1 after the above loop
    if (j < 0) {
      return shift;
    } else {
      // Shift the pattern so that the bad character in text
      // aligns with the last occurrence of it in pattern.
      // The max function is used to make sure that we get
      // a positive shift. We may get a negative shift if the
      // last occurrence of bad character in pattern is on the
      // right side of the current character.
      shift += std::max(
          1, j - bad_char[static_cast<unsigned char>(text[shift + j])]);
    }
  }

  return std::string::npos;
}
