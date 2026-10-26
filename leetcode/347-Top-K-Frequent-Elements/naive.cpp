#include <algorithm>
#include <unordered_map>
#include <map>
#include <vector>

class Solution {
public:
  std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
    std::unordered_map<int, unsigned int> map = {};

    for (auto n : nums) map[n]++;

    std::multimap<unsigned int, int> flipped;
    for (auto [key, value] : map) flipped.insert({ value, key });

    std::vector<int> result;
    auto it = flipped.end();
    int i = 0;
    while (it != flipped.begin() && i < k) {
      it = std::prev(it);
      i++;
      result.push_back(it->second);
    }

    return result;
  }
};


#include "../../vendor/catch2/catch.hpp"

TEST_CASE("example 1") {
  Solution s;

  std::vector<int> input = {1, 1, 1, 2, 2, 3};
  auto output = s.topKFrequent(input, 2);
  std::sort(output.begin(), output.end());

  std::vector<int> expected = {1, 2};

  REQUIRE(output == expected);
}

TEST_CASE("example 2") {
  Solution s;

  std::vector<int> input = {1};
  auto output = s.topKFrequent(input, 1);
  std::sort(output.begin(), output.end());

  std::vector<int> expected = {1};

  REQUIRE(output == expected);
}

TEST_CASE("example 3") {
  Solution s;

  std::vector<int> input = {1, 2, 1, 2, 1, 2, 3, 1, 3, 2};
  auto output = s.topKFrequent(input, 2);
  std::sort(output.begin(), output.end());

  std::vector<int> expected = {1, 2};
  REQUIRE(output == expected);
}
