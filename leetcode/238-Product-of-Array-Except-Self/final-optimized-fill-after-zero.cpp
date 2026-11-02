#include <cstddef>
#include <vector>
#include <algorithm>

class Solution {
public:
  std::vector<int> productExceptSelf(std::vector<int>& nums) {
    std::vector<int> output(nums.size(), 1);

    int left = 1;
    for (size_t i = 0; i < nums.size(); i++) {
      if (left == 0) {
        std::fill(output.begin() + static_cast<long>(i), output.end(), 0);
        break;
      }

      output[i] *= left;
      left *= nums[i];
    }

    int right = 1;
    for (int i = static_cast<int>(nums.size()) - 1; i >= 0; i--) {
      if (right == 0) {
        std::fill(output.begin(), output.begin() + i + 1, 0);
        break;
      }

      output[static_cast<size_t>(i)] *= right;
      right *= nums[static_cast<size_t>(i)];
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