#include <unordered_set>
#include <vector>

class Solution {
public:
  // this implementation uses the hashset to get the optimal O(N) time complexity expected
  // for massive real-world datasets, an in-place sort (O(N log N)) and then checking nums[i] == nums[i-1] is faster due to CPU cache locality.
  static bool containsDuplicate(std::vector<int>& nums) {
    std::unordered_set<int> seen;
    seen.reserve(nums.size());
    for (auto num : nums) {
      if (!seen.insert(num).second) return true;
    }
    return false;
  }
};

#define CATCH_CONFIG_MAIN
#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Contains Duplicate") {
  SECTION("Test 1 (Example 1)") {
    std::vector<int> nums = {1, 2, 3, 1};
    CHECK(Solution::containsDuplicate(nums) == true);
  }
  SECTION("Test 2 (Example 2)") {
    std::vector<int> nums = {1, 2, 3, 4};
    CHECK(Solution::containsDuplicate(nums) == false);
  }
  SECTION("Test 3 (Example 3)") {
    std::vector<int> nums = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    CHECK(Solution::containsDuplicate(nums) == true);
  }
  SECTION("Test 4 (Single Element)") {
    std::vector<int> nums = {42};
    CHECK(Solution::containsDuplicate(nums) == false);
  }
  SECTION("Test 5 (Extreme Values)") {
    std::vector<int> nums = {-1000000000, 1000000000, -1000000000};
    CHECK(Solution::containsDuplicate(nums) == true);
  }
  SECTION("Test 6 (Max Length Array 10^5)") {
    std::vector<int> large_input;
    large_input.reserve(100000);
    for (int i = 0; i < 99999; ++i) large_input.push_back(i);
    large_input.push_back(0);
    CHECK(Solution::containsDuplicate(large_input) == true);
  }
}
