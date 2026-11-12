#include <algorithm>
#include <cstddef>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    const size_t n = nums.size();
    std::vector<std::vector<int>> answ;

    std::sort(nums.begin(), nums.end());

    for (size_t i = 0; (i + 2) < n; i++) { // +2 -> must be a tripplet
      if (i > 0 && nums[i] == nums[i - 1]) continue; // skip duplicates

      const int current = nums[i];
      size_t p_left = i + 1;
      size_t p_right = n - 1;

      while (p_left < p_right) {
        if (current + nums[p_left] + nums[p_right] > 0) {
          p_right--;
          continue;
        }
        if (current + nums[p_left] + nums[p_right] < 0) {
          p_left++;
          continue;
        }

        answ.push_back({current, nums[p_left], nums[p_right]});
        p_left++;
        p_right--;

        while (p_left < p_right && nums[p_left] == nums[p_left - 1]) p_left++; // skip duplicates
      }
    }

    return answ;
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("Example 1") {
  Solution s;
  std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
  std::vector<std::vector<int>> expected = { { -1, -1, 2 }, { -1, 0, 1 } };
  REQUIRE(s.threeSum(nums) == expected);
}

TEST_CASE("Example 2") {
  Solution s;
  std::vector<int> nums = {0, 1, 1};
  std::vector<std::vector<int>> expected = { };
  REQUIRE(s.threeSum(nums) == expected);
}

TEST_CASE("Example 3") {
  Solution s;
  std::vector<int> nums = {0, 0, 0};
  std::vector<std::vector<int>> expected = { { 0, 0, 0 } };
  REQUIRE(s.threeSum(nums) == expected);
}

TEST_CASE("Example 4") {
  Solution s;
  std::vector<int> nums = {0, 0, 0, 0};
  std::vector<std::vector<int>> expected = { { 0, 0, 0 } };
  REQUIRE(s.threeSum(nums) == expected);
}
