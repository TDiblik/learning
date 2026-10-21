#include <map>
#include <vector>

class Solution {
public:
  std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::map<std::array<int, 26>, std::vector<std::string>> map{};

    for (auto s : strs) {
      std::array<int, 26> counts{};
      for (char& c : s) counts[(unsigned int)c-'a'] += 1;

      if (map.find(counts) == map.end()) map[counts] = std::vector{s};
      else map[counts].push_back(s);
    }

    auto output = std::vector<std::vector<std::string>>{};
    for (auto [_, val] : map) output.push_back(val);

    return output;
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("example 1") {
  auto s = new Solution();
  std::vector<std::string> input = {"eat","tea","tan","ate","nat","bat"};

  auto output = s->groupAnagrams(input);

  REQUIRE(output[0][0] == "tan");
  REQUIRE(output[0][1] == "nat");

  REQUIRE(output[1][0] == "eat");
  REQUIRE(output[1][1] == "tea");
  REQUIRE(output[1][2] == "ate");

  REQUIRE(output[2][0] == "bat");
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
