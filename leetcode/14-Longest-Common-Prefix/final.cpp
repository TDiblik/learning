#include <algorithm>
#include <iostream>
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

void runTest(std::vector<std::string> strs, const std::string &expected, const std::string &test_name) {
  std::string result = Solution::longestCommonPrefix(strs);
  if (result == expected) {
    std::cout << test_name << " Passed\n";
  } else {
    std::cout << test_name << " Failed\n";
    std::cout << "    Expected: \"" << expected << "\", Got: \"" << result << "\"\n";
  }
}

int main() {
  std::cout << "Running tests for Longest Common Prefix...\n\n";

  runTest({"flower", "flow", "flight"}, "fl", "Test 1 (Example 1)");
  runTest({"dog", "racecar", "car"}, "", "Test 2 (Example 2 - No common prefix)");
  runTest({"single"}, "single", "Test 3 (Single string in array)");
  runTest({"", "b", "c"}, "", "Test 4 (First string is empty)");
  runTest({"a", "", "c"}, "", "Test 5 (Middle string is empty)");
  runTest({"test", "test", "test"}, "test", "Test 6 (All strings identical)");
  runTest({"ab", "abc", "abcd"}, "ab", "Test 7 (Prefix is the entire shortest string - first)");
  runTest({"abcd", "abc", "ab"}, "ab", "Test 8 (Prefix is the entire shortest string - last)");
  runTest({"a", "a", "b"}, "", "Test 9 (Prefix fails on last string)");
  runTest({"c", "acc", "ccc"}, "", "Test 10 (Different starting characters)");
  std::vector<std::string> max_strs(200, std::string(200, 'a'));
  runTest(max_strs, std::string(200, 'a'), "Test 11 (Max limits: 200 strings of 200 'a's)");
  std::vector<std::string> large_mismatch = max_strs;
  large_mismatch.push_back(std::string(199, 'a') + "z");
  runTest(large_mismatch, std::string(199, 'a'), "Test 12 (Large limits: Mismatch at the very last character)");

  std::cout << "\nFinished running tests.\n";
  return 0;
}
