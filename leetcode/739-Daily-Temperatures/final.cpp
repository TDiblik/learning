#include <cstddef>
#include <stack>
#include <vector>

class Solution {
public:
  std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
    std::vector<int> answ(temperatures.size(), 0);
    std::stack<size_t> mono_st; // store indexes only, it's enough

    for (size_t i = 0; i < temperatures.size(); i++) {
      while (!mono_st.empty() && temperatures[mono_st.top()] < temperatures[i]) {
        const auto left = mono_st.top();
        mono_st.pop();

        answ[left] = static_cast<int>(i - left);
      }
      mono_st.push(i);
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

TEST_CASE("Example 4 - large input") {
  Solution s;

  std::vector<int> temperatures(100000, 99);
  temperatures.back() = 100;

  std::vector<int> expected(100000, 0);
  for (size_t i = 0; i < 99999; i++) {
    expected[i] = static_cast<int>(99999 - i);
  }

  REQUIRE(s.dailyTemperatures(temperatures) == expected);
}
