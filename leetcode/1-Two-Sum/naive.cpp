#include <vector>

class Solution {
public:
  static std::vector<int> twoSum(std::vector<int>& nums, int target) {
    for (size_t i = 0; i < nums.capacity(); i++) {
      for (size_t j = 0; j < nums.capacity(); j++) {
        if (i == j) continue;
        if (nums[i] + nums[j] == target) return {(int)i, (int)j};
      }
    }
    return {};
  }
};

#define CATCH_CONFIG_MAIN
#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Two Sum naive") {
  std::vector<int> nums = {2, 7, 11, 15};
  CHECK(Solution::twoSum(nums, 9) == std::vector<int>{0, 1});
}
