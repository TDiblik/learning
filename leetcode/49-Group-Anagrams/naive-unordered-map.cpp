#include <unordered_map>
#include <vector>

struct ArrayHash {
  std::size_t operator()(const std::array<int, 26>& a) const {
    std::size_t hash = 0;
    for (int count : a) hash = hash * 31 + std::hash<int>{}(count);
    return hash;
  }
};

class Solution {
public:
  std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::unordered_map<std::array<int, 26>, std::vector<std::string>, ArrayHash> map{};

    for (auto& s : strs) {
      std::array<int, 26> counts{};
      for (char& c : s) counts[(unsigned int)c-'a'] += 1;
      map[counts].push_back(s);
    }

    auto output = std::vector<std::vector<std::string>>{};
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
