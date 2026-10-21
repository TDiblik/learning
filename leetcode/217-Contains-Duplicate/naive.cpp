#include <unordered_set>
#include <vector>

class Solution {
public:
  bool containsDuplicate(std::vector<int>& nums) {
    std::unordered_set<int> seen;

    for (auto num : nums){
      if (seen.find(num) != seen.end()) return true;
      seen.insert(num);
    }

    return false;
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("should ouput true") {
  auto s = new Solution();
  std::vector<int> input = {1,2,3,1};
  REQUIRE(s->containsDuplicate(input) == true);

  input = {1,1,1,3,3,4,3,2,4,2};
  REQUIRE(s->containsDuplicate(input) == true);
}

TEST_CASE("should ouput false") {
  auto s = new Solution();
  std::vector<int> input = {1,2,3,4};
  REQUIRE(s->containsDuplicate(input) == false);
}
