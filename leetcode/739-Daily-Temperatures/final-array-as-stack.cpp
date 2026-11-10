#include <cstddef>
#include <vector>

class Solution {
public:
  std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
    std::vector<int> answ(temperatures.size(), 0);
    std::vector<size_t> mono_st; // use vector instead of stack, better cache locality.
    mono_st.reserve(temperatures.size());

    for (size_t i = 0; i < temperatures.size(); i++) {
      while (!mono_st.empty() && temperatures[mono_st.back()] < temperatures[i]) {
        const auto left = mono_st.back();
        mono_st.pop_back();

        answ[left] = static_cast<int>(i - left);
      }
      mono_st.push_back(i);
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
