#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, unsigned int> seen;

    for (unsigned int i = 0; i < nums.size(); i++) {
      auto diff = target - nums[i];
      if (seen.find(diff) != seen.end()) return {(int)seen[diff], (int)i};
      seen[nums[i]] = i;
    }

    return {};
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("{2, 7, 11, 15}, 9") {
  auto s = new Solution();

  std::vector<int> nums = {2, 7, 11, 15};
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
