#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "search_function.h"

#include "naive_search.h"
#include "boyer_moore_search.h"

using Clock = std::chrono::steady_clock;

int main(int argc, const char **const argv) {
  std::vector<std::string_view> args(argc);
  for (int i = 0; i < argc; i++) {
    args[i] = argv[i];
  }

  if (args.size() != 4) {
    std::cout << "Usage: search <algorithm> <pattern> <path>\n";
    return 0;
  }

  std::string_view executable_name = args[0];
  std::filesystem::path file_path(args[3]);
  if (!std::filesystem::exists(file_path)) {
    std::cout << std::format("{}: {}: No such file or directory\n",
                             executable_name, file_path.string());
    return 0;
  }

  std::fstream fstream(file_path);
  std::stringstream buffer;
  buffer << fstream.rdbuf();
  std::string file_contents(buffer.str());

  /* Fill this with definitions names and functions for string searching
   * algorithms */
  const std::unordered_map<std::string_view, StringSearchFunction> algo_map{
    { "naive", naive_search },
    { "boyer-moore", boyer_moore_search },
  };

  std::string_view algo_str = args[1];
  if (!algo_map.contains(algo_str)) {
    std::cout << std::format("{}: No such search algorithm {}\n",
                             executable_name, algo_str);
    return 0;
  }

  std::string_view pattern = args[2];
  StringSearchFunction search_func = algo_map.at(algo_str);

  auto begin = Clock::now();
  std::size_t idx = search_func(pattern, file_contents);
  auto end = Clock::now();
  auto duration_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

  if (idx != std::string::npos) {
    std::cout << std::format("Found {} at index {} in {} in {}\n", pattern,
                             idx, file_path.string(), duration_ms);
  } else {
    std::cout << std::format("Couldn't find {} in {} in {}\n", pattern,
                             file_path.string(), duration_ms);
  }

  return 0;
}
