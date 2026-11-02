#include <cstddef>
#include <vector>

class Solution {
public:
  std::vector<int> productExceptSelf(std::vector<int>& nums) {
    const size_t n = nums.size();
    std::vector<int> output(n, 1);

    int left = 1;
    int right = 1;
    for (size_t i = 0; i < n; i++) {
      output[i] *= left;
      left *= nums[i];

      size_t j = n - 1 - i;
      output[j] *= right;
      right *= nums[j];
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
