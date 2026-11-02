#include <vector>

class Solution {
public:
  std::vector<int> productExceptSelf(std::vector<int>& nums) {
    std::vector<int> output;
    for (size_t i = 0; i < nums.size(); i++) {
      output.push_back(1);
      for (size_t j = 0; j < nums.size(); j++) {
        if (i == j) continue;
        output[i] *= nums[j];
      }
    }

    return output;
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("example 1") {
  Solution s;

  std::vector<int> input = {1, 2, 3, 4};
  auto output = s.productExceptSelf(input);

  std::vector<int> expected = {24, 12, 8, 6};
  REQUIRE(output == expected);
}

TEST_CASE("example 2") {
  Solution s;

  std::vector<int> input = {-1, 1, 0, -3, 3};
  auto output = s.productExceptSelf(input);

  std::vector<int> expected = {0, 0, 9, 0, 0};
  REQUIRE(output == expected);
}
