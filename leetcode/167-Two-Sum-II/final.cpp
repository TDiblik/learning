#include <cassert>
#include <vector>

class Solution {
public:
  std::vector<int> twoSum(std::vector<int>& numbers, int target) {
    assert(numbers.size() > 0);

    size_t p_left = 0;
    size_t p_right = numbers.size() - 1;

    while (p_left < p_right) {
      if (numbers[p_left] + numbers[p_right] > target) {
        p_right--;
        continue;
      }
      if (numbers[p_left] + numbers[p_right] < target) {
        p_left++;
        continue;
      }

      if (numbers[p_left] + numbers[p_right] == target) {
        return {static_cast<int>(p_left+1), static_cast<int>(p_right+1)};
      }
    }

    return {};
  }
};

#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Example 1") {
  Solution s;

  int target = 9;
  std::vector<int> numbers = { 2, 7, 11, 15 };
  std::vector<int> expected = { 1, 2 };
  REQUIRE(s.twoSum(numbers, target) == expected);
}

TEST_CASE("Example 2") {
  Solution s;

  int target = 6;
  std::vector<int> numbers = { 2, 3, 4 };
  std::vector<int> expected = { 1, 3 };
  REQUIRE(s.twoSum(numbers, target) == expected);
}

TEST_CASE("Example 3") {
  Solution s;

  int target = -1;
  std::vector<int> numbers = { -1, 0 };
  std::vector<int> expected = { 1, 2 };
  REQUIRE(s.twoSum(numbers, target) == expected);
}

TEST_CASE("Example 4") {
  Solution s;

  int target = 0;
  std::vector<int> numbers = { 0, 0, 3, 4 };
  std::vector<int> expected = { 1, 2 };
  REQUIRE(s.twoSum(numbers, target) == expected);
}
