#include <algorithm>
#include <vector>

class Solution {
public:
  // sorting and then going 1-by-1 is better for cache locality then unordered map
  bool containsDuplicate(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    for (unsigned int i = 0; i < nums.size()-1; i++) {
      if (nums[i] == nums[i+1]) return true;
    }
    return false;
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("should ouput true") {
  auto s = new Solution();
  std::vector<int> input = {1,2,3,1};
  REQUIRE(s->containsDuplicate(input));

  input = {1,1,1,3,3,4,3,2,4,2};
  REQUIRE(s->containsDuplicate(input));
}

TEST_CASE("should ouput false") {
  auto s = new Solution();
  std::vector<int> input = {1,2,3,4};
  REQUIRE_FALSE(s->containsDuplicate(input));
}
