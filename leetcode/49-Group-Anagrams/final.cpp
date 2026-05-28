#include <unordered_map>
#include <vector>
#include <algorithm>

class Solution {
public:
  static std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> res_map;
    res_map.reserve(strs.size());

    for (std::string &s : strs) {
      std::string key = s;
      std::ranges::sort(key);
      res_map[key].push_back(s);
    }

    std::vector<std::vector<std::string>> res;
    res.reserve(res_map.size());
    for (auto& [_, val] : res_map) res.push_back(std::move(val));

    return res;
  }
};

void normalizeGroups(std::vector<std::vector<std::string>>& groups) {
  for (auto& group : groups) {
    std::sort(group.begin(), group.end());
  }
  std::sort(groups.begin(), groups.end());
}

#define CATCH_CONFIG_MAIN
#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Group Anagrams") {
  auto runTest = [](std::vector<std::string> input, std::vector<std::vector<std::string>> expected) {
    std::vector<std::vector<std::string>> result = Solution::groupAnagrams(input);
    normalizeGroups(result);
    normalizeGroups(expected);
    CHECK(result == expected);
  };

  SECTION("Test 1 (Example 1: Multiple groups)") {
    runTest({"eat","tea","tan","ate","nat","bat"}, {{"bat"}, {"nat","tan"}, {"ate","eat","tea"}});
  }
  SECTION("Test 2 (Example 2: Single empty string)") {
    runTest({""}, {{""}});
  }
  SECTION("Test 3 (Example 3: Single character)") {
    runTest({"a"}, {{"a"}});
  }
  SECTION("Test 4 (No anagrams at all)") {
    runTest({"abc", "def", "xyz"}, {{"abc"}, {"def"}, {"xyz"}});
  }
  SECTION("Test 5 (All identical strings)") {
    runTest({"aaa", "aaa", "aaa"}, {{"aaa", "aaa", "aaa"}});
  }
  SECTION("Test 6 (Multiple empty strings and duplicates)") {
    runTest({"", "", "b", "b", "c"}, {{"", ""}, {"b", "b"}, {"c"}});
  }
  SECTION("Test 7 (Max Length Array 10^4 elements)") {
    std::vector<std::string> large_input(10000, "zz");
    std::vector<std::string> large_expected_group(10000, "zz");
    runTest(large_input, {large_expected_group});
  }
}
