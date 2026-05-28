#include <vector>
#include <unordered_map>

class Solution {
public:
  static std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> mapping;

    for (size_t i = 0; i < nums.size(); i++) {
      int complement = target - nums[i];
      if (mapping.find(complement) != mapping.end()) {
        return {mapping[complement], (int)i};
      }
      mapping[nums[i]] = (int)i;
    }

    return {};
  }
};

#define CATCH_CONFIG_MAIN
#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Two Sum final") {
  std::vector<int> nums = {2, 7, 11, 15};
  CHECK(Solution::twoSum(nums, 9) == std::vector<int>{0, 1});
}
