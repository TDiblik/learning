#include <vector>
#include <algorithm>

class Solution {
public:
  static int removeElement(std::vector<int>& nums, int val) {
    nums.erase(std::remove(nums.begin(), nums.end(), val), nums.end());
    return (int)nums.size();
  }
};

#define CATCH_CONFIG_MAIN
#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Remove Element") {
  auto runTest = [](std::vector<int> nums, int val, std::vector<int> expectedNums) {
    size_t k = (size_t)Solution::removeElement(nums, val);
    CHECK(k == expectedNums.size());
    if (k == expectedNums.size()) {
      std::sort(nums.begin(), nums.begin() + (long)k);
      std::sort(expectedNums.begin(), expectedNums.end());
      for (size_t i = 0; i < k; i++) {
        CHECK(nums[i] == expectedNums[i]);
      }
    }
  };

  SECTION("Test 1 (Example 1)") { runTest({3, 2, 2, 3}, 3, {2, 2}); }
  SECTION("Test 2 (Example 2)") { runTest({0, 1, 2, 2, 3, 0, 4, 2}, 2, {0, 1, 4, 0, 3}); }
  SECTION("Test 3 (Empty array)") { runTest({}, 0, {}); }
  SECTION("Test 4 (No occurrences of val)") { runTest({1, 2, 3, 4}, 5, {1, 2, 3, 4}); }
  SECTION("Test 5 (Array consists entirely of val)") { runTest({2, 2, 2, 2}, 2, {}); }
  SECTION("Test 6 (Single element, equals val)") { runTest({5}, 5, {}); }
  SECTION("Test 7 (Single element, does not equal val)") { runTest({5}, 4, {5}); }
  SECTION("Test 8 (Val is only at the beginning)") { runTest({2, 3, 4, 5}, 2, {3, 4, 5}); }
  SECTION("Test 9 (Val is only at the end)") { runTest({3, 4, 5, 2}, 2, {3, 4, 5}); }
  SECTION("Test 10 (Consecutive vals in the middle)") { runTest({4, 2, 2, 5, 6}, 2, {4, 5, 6}); }
}
