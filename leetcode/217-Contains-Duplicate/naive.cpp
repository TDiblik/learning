#include <unordered_set>
#include <vector>

class Solution {
public:
  static bool containsDuplicate(std::vector<int>& nums) {
    std::unordered_set<int> seen;

    for (size_t i = 0; i < nums.size(); i++) {
      int current = nums[i];
      if (seen.find(current) != seen.end()) return true;
      seen.insert(current);
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
