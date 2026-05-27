#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

class Solution {
public:
  static std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::vector<std::string> ordered_strings = strs;
    for (std::string &s : ordered_strings) std::ranges::sort(s);

    std::unordered_map<std::string, std::vector<std::string>> res_map;
    for (size_t i = 0; i < ordered_strings.size(); i++) res_map[ordered_strings[i]].push_back(strs[i]);

    std::vector<std::vector<std::string>> res;
    res.reserve(res_map.size());
    for (auto& [key, value] : res_map) res.push_back(std::move(value));

    return res;
  }
};

void normalizeGroups(std::vector<std::vector<std::string>>& groups) {
  for (auto& group : groups) {
    std::sort(group.begin(), group.end());
  }
  std::sort(groups.begin(), groups.end());
}

void runTest(std::vector<std::string> input, std::vector<std::vector<std::string>> expected, const std::string& test_name) {
  std::vector<std::string> input_copy = input;
  std::vector<std::vector<std::string>> result = Solution::groupAnagrams(input_copy);

  normalizeGroups(result);
  normalizeGroups(expected);

  if (result == expected) {
    std::cout << test_name << " Passed\n";
  } else {
    std::cout << test_name << " Failed\n";
    std::cout << "  (Expected and Actual outputs differ. Ensure all anagrams are grouped correctly.)\n";
  }
}

int main() {
  std::cout << "Running tests for groupAnagrams...\n\n";

  runTest({"eat","tea","tan","ate","nat","bat"}, {{"bat"}, {"nat","tan"}, {"ate","eat","tea"}}, "Test 1 (Example 1: Multiple groups)");
  runTest({""}, {{""}}, "Test 2 (Example 2: Single empty string)");
  runTest({"a"}, {{"a"}}, "Test 3 (Example 3: Single character)");
  runTest({"abc", "def", "xyz"}, {{"abc"}, {"def"}, {"xyz"}}, "Test 4 (No anagrams at all)");
  runTest({"aaa", "aaa", "aaa"}, {{"aaa", "aaa", "aaa"}}, "Test 5 (All identical strings)");
  runTest({"", "", "b", "b", "c"}, {{"", ""}, {"b", "b"}, {"c"}}, "Test 6 (Multiple empty strings and duplicates)");

  std::vector<std::string> large_input;
  std::vector<std::string> large_expected_group;
  large_input.reserve(10000);
  large_expected_group.reserve(10000);
  for (int i = 0; i < 10000; ++i) {
    large_input.push_back("zz");
    large_expected_group.push_back("zz");
  }
  runTest(large_input, {large_expected_group}, "Test 7 (Max Length Array 10^4 elements)");

  std::cout << "\nFinished running tests.\n";
  return 0;
}
