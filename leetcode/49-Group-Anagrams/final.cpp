#include <unordered_map>
#include <algorithm>
#include <vector>

class Solution {
public:
  std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> map{};

    for (auto& s : strs) {
      std::string key = s;
      std::sort(key.begin(), key.end());
      map[std::move(key)].push_back(std::move(s)); // we dont care about messing up the input + this prevents copy
    }

    std::vector<std::vector<std::string>> output;
    for (auto& [_, val] : map) output.push_back(val);

    return output;
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("example 1") {
  auto s = new Solution();
  std::vector<std::string> input = {"eat","tea","tan","ate","nat","bat"};

  auto output = s->groupAnagrams(input);

  for (auto& group : output) std::sort(group.begin(), group.end());
  std::sort(output.begin(), output.end());
  std::vector<std::vector<std::string>> expected = {
    {"ate", "eat", "tea"},
    {"bat"},
    {"nat", "tan"}
  };
  REQUIRE(output == expected);
}

TEST_CASE("example 2") {
  auto s = new Solution();
  std::vector<std::string> input = {""};

  auto output = s->groupAnagrams(input);
  REQUIRE(output[0][0] == "");
}

TEST_CASE("example 3") {
  auto s = new Solution();
  std::vector<std::string> input = {"a"};

  auto output = s->groupAnagrams(input);
  REQUIRE(output[0][0] == "a");
}
