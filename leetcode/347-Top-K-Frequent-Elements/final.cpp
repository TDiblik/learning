#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
    std::unordered_map<int, unsigned int> map;
    map.reserve(static_cast<std::size_t>(nums.size()));

    for (auto n : nums) map[n]++;

    using Pair = std::pair<unsigned int, int>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;

    // always has smallest on top and pop(s) it when it is outside of the range "k"
    for (auto [key, value] : map){
      pq.push({value, key});
      if (pq.size() > static_cast<std::size_t>(k)) pq.pop();
    }

    std::vector<int> result;
    result.reserve(static_cast<std::size_t>(k));
    while (!pq.empty()) {
      result.push_back(pq.top().second);
      pq.pop();
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
