#include <algorithm>
#include <cassert>
#include <climits>
#include <vector>

class Solution {
public:
  int maxArea(std::vector<int>& height) {
    const size_t n = height.size();
    assert(n > 0);

    size_t p_left = 0;
    size_t p_right = n - 1;
    int largest = INT_MIN;

    while (p_left < p_right) {
      const int a = static_cast<int>(p_right - p_left);

      const int left = height[p_left];
      const int right = height[p_right];
      const int b = std::min(left, right);

      const int possibly_largest = a * b;
      largest = std::max(possibly_largest, largest);

      if (left >= right) p_right--;
      else p_left++;
    }

    return largest;
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("Example 1") {
  Solution s;
  std::vector<int> heights = { 1, 8, 6, 2, 5, 4, 8, 3, 7 };
  REQUIRE(s.maxArea(heights) == 49);
}

TEST_CASE("Example 2") {
  Solution s;
  std::vector<int> heights = { 1, 1 };
  REQUIRE(s.maxArea(heights) == 1);
}

TEST_CASE("Example 3") {
  Solution s;
  std::vector<int> heights = { 2, 1 };
  REQUIRE(s.maxArea(heights) == 1);
}
