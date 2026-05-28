#include <vector>

class Solution {
public:
  static int majorityElement(std::vector<int> &nums) {
    int candidate, count = 0;
    for (int num : nums) {
      if (count == 0) candidate = num;

      if (candidate == num) count += 1;
      else count -= 1;
    }

    return candidate;
  }
};

#define CATCH_CONFIG_MAIN
#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Majority Element") {
  std::vector<int> nums;

  SECTION("Test 1 (Example 1)") {
    nums = {3, 2, 3};
    CHECK(Solution::majorityElement(nums) == 3);
  }
  SECTION("Test 2 (Example 2)") {
    nums = {2, 2, 1, 1, 1, 2, 2};
    CHECK(Solution::majorityElement(nums) == 2);
  }
  SECTION("Test 3 (Single element)") {
    nums = {5};
    CHECK(Solution::majorityElement(nums) == 5);
  }
  SECTION("Test 4 (All elements the same)") {
    nums = {1, 1, 1, 1};
    CHECK(Solution::majorityElement(nums) == 1);
  }
  SECTION("Test 5 (Majority clustered at the end)") {
    nums = {1, 2, 2, 2, 2};
    CHECK(Solution::majorityElement(nums) == 2);
  }
  SECTION("Test 6 (Majority clustered at the beginning)") {
    nums = {2, 2, 2, 2, 1};
    CHECK(Solution::majorityElement(nums) == 2);
  }
  SECTION("Test 7 (Alternating elements with majority)") {
    nums = {6, 5, 5, 6, 5};
    CHECK(Solution::majorityElement(nums) == 5);
  }
}
