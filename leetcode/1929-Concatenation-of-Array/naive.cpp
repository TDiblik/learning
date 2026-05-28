#include <algorithm>
#include <vector>

class Solution {
public:
    static std::vector<int> getConcatenation(std::vector<int>& nums) {
      std::vector<int> ans = std::vector<int>(nums.size() * 2);
      std::copy(nums.begin(), nums.end(), ans.begin());
      std::copy(nums.begin(), nums.end(), (int)nums.size() + ans.begin());
      return ans;
    }
};

#define CATCH_CONFIG_MAIN
#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Concatenation of Array") {
  auto runTest = [](std::vector<int> input, std::vector<int> expected) {
    CHECK(Solution::getConcatenation(input) == expected);
  };

  SECTION("Test 1 (Example 1)") { runTest({1, 4, 1, 2}, {1, 4, 1, 2, 1, 4, 1, 2}); }
  SECTION("Test 2 (Example 2)") { runTest({22, 21, 20, 1}, {22, 21, 20, 1, 22, 21, 20, 1}); }
  SECTION("Test 3 (Single Element)") { runTest({7}, {7, 7}); }
  SECTION("Test 4 (Identical Elements)") { runTest({5, 5, 5}, {5, 5, 5, 5, 5, 5}); }
  SECTION("Test 5 (Max Length Array)") {
    std::vector<int> largeInput(1000, 1);
    std::vector<int> largeExpected(2000, 1);
    runTest(largeInput, largeExpected);
  }
}
