#include <algorithm>
#include <string>
#include <vector>

class Solution {
public:
  static std::string longestCommonPrefix(std::vector<std::string> &strs) {
    auto smallest = std::ranges::min_element(strs, std::less<>{}, &std::string::size);
    auto smallest_size = smallest->size();
    for (size_t i = 0; i < smallest_size; i++) {
      for (size_t j = 0; j < strs.size(); j++) {
        if (strs[j].at(i) != smallest->at(i)) return smallest->substr(0, i);
      }
    }

    return smallest->substr(0, smallest_size);
  }
};

#define CATCH_CONFIG_MAIN
#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Longest Common Prefix") {
  std::vector<std::string> strs;

  SECTION("Test 1 (Example 1)") {
    strs = {"flower", "flow", "flight"};
    CHECK(Solution::longestCommonPrefix(strs) == "fl");
  }
  SECTION("Test 2 (Example 2 - No common prefix)") {
    strs = {"dog", "racecar", "car"};
    CHECK(Solution::longestCommonPrefix(strs) == "");
  }
  SECTION("Test 3 (Single string in array)") {
    strs = {"single"};
    CHECK(Solution::longestCommonPrefix(strs) == "single");
  }
  SECTION("Test 4 (First string is empty)") {
    strs = {"", "b", "c"};
    CHECK(Solution::longestCommonPrefix(strs) == "");
  }
  SECTION("Test 5 (Middle string is empty)") {
    strs = {"a", "", "c"};
    CHECK(Solution::longestCommonPrefix(strs) == "");
  }
  SECTION("Test 6 (All strings identical)") {
    strs = {"test", "test", "test"};
    CHECK(Solution::longestCommonPrefix(strs) == "test");
  }
  SECTION("Test 7 (Prefix is the entire shortest string - first)") {
    strs = {"ab", "abc", "abcd"};
    CHECK(Solution::longestCommonPrefix(strs) == "ab");
  }
  SECTION("Test 8 (Prefix is the entire shortest string - last)") {
    strs = {"abcd", "abc", "ab"};
    CHECK(Solution::longestCommonPrefix(strs) == "ab");
  }
  SECTION("Test 9 (Prefix fails on last string)") {
    strs = {"a", "a", "b"};
    CHECK(Solution::longestCommonPrefix(strs) == "");
  }
  SECTION("Test 10 (Different starting characters)") {
    strs = {"c", "acc", "ccc"};
    CHECK(Solution::longestCommonPrefix(strs) == "");
  }
  SECTION("Test 11 (Max limits: 200 strings of 200 'a's)") {
    std::vector<std::string> max_strs(200, std::string(200, 'a'));
    CHECK(Solution::longestCommonPrefix(max_strs) == std::string(200, 'a'));
  }
  SECTION("Test 12 (Large limits: Mismatch at the very last character)") {
    std::vector<std::string> max_strs(200, std::string(200, 'a'));
    std::vector<std::string> large_mismatch = max_strs;
    large_mismatch.push_back(std::string(199, 'a') + "z");
    CHECK(Solution::longestCommonPrefix(large_mismatch) == std::string(199, 'a'));
  }
}
