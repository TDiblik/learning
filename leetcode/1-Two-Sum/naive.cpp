#include <vector>

class Solution {
public:
  std::vector<int> twoSum(std::vector<int>& nums, int target) {
    for (unsigned int i = 0; i < nums.size(); i++) {
      for (unsigned int j = 0; j < nums.size(); j++) {
        if (i == j) continue;
        if (nums[i] + nums[j] == target) return {(int)i, (int)j};
      }
    }
    return {};
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("{2 ,7, 11, 15}, 9") {
  auto s = new Solution();

  std::vector<int> nums = {2 ,7, 11, 15};
  auto output = s->twoSum(nums, 9);

  REQUIRE(output[0] == 0);
  REQUIRE(output[1] == 1);
}

TEST_CASE("{3, 2, 4}, 6") {
  auto s = new Solution();

  std::vector<int> nums = {3, 2, 4};
  auto output = s->twoSum(nums, 6);

  REQUIRE(output[0] == 1);
  REQUIRE(output[1] == 2);
}

TEST_CASE("{3, 3}, 6") {
  auto s = new Solution();

  std::vector<int> nums = {3, 3};
  auto output = s->twoSum(nums, 6);

  REQUIRE(output[0] == 0);
  REQUIRE(output[1] == 1);
}
