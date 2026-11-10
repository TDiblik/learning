#include <cstddef>
#include <vector>

class Solution {
public:
  std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
    std::vector<int> answ(temperatures.size(), 0);
    for (size_t i = 0; i < temperatures.size(); i++) {
      for (size_t j = 1; (i + j) < temperatures.size(); j++) {
        if (temperatures[i] < temperatures[(i + j)]) {
          answ[i] = static_cast<int>(j);
          break;
        }
      }
    }

    return answ;
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("Example 1") {
  Solution s;
  std::vector<int> temperatures = { 73, 74, 75, 71, 69, 72, 76, 73 };
  std::vector<int> expected = { 1, 1, 4, 2, 1, 1, 0, 0 };
  REQUIRE(s.dailyTemperatures(temperatures) == expected);
}

TEST_CASE("Example 2") {
  Solution s;
  std::vector<int> temperatures = { 30, 40, 50, 60 };
  std::vector<int> expected = { 1, 1, 1, 0 };
  REQUIRE(s.dailyTemperatures(temperatures) == expected);
}

TEST_CASE("Example 3") {
  Solution s;
  std::vector<int> temperatures = { 30, 60, 90 };
  std::vector<int> expected = { 1, 1, 0 };
  REQUIRE(s.dailyTemperatures(temperatures) == expected);
}
