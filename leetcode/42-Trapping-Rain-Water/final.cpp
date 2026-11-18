#include <cassert>
#include <vector>

// n == height.length
// 1 <= n <= 2 * 104
// 0 <= height[i] <= 105
class Solution {
public:
  int trap(std::vector<int>& height) {
    int answ = 0;

    const size_t n = height.size();
    assert(n > 0);

    size_t left_p = 0;
    while (left_p < n && height[left_p] == 0) ++left_p; // skip initial spillage at the start

    int temp = 0;
    size_t right_p = left_p + 1;
    int left_max = height[left_p];
    while (right_p < n) {
      const int right = height[right_p];

      if (left_max <= right) {
        left_max = right;
        left_p = right_p;
        answ += temp;
        temp = 0;
      } else {
        temp += left_max - right;
      }
      ++right_p;
    }
    if (temp == 0) return answ; // no need to back track, all water was captured at the end

    right_p -= 1; // after the loop, right_p is equal to `n` -> which is one more than last index

    // skip spillage at the end
    while (right_p > left_p && height[right_p] == 0) --right_p;

    // go backwards and then every time i encountered bar bigger than the one at right_p,
    // i just counted the captured water and set right_p to the new bar and then repeated this untill left_p < right_p
    int right_max = height[right_p]; // store the value so that we don't jump around in memory
    while (left_p <= right_p) {
      const int right = height[right_p];

      if (right_max <= right) {
        right_max = right;
      } else {
        answ += right_max - right;
      }

      if (right_p == left_p) break;
      --right_p;
    }

    return answ;
  }
};

#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Example 1") {
  Solution s;
  std::vector<int> height = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
  REQUIRE(s.trap(height) == 6);
}

TEST_CASE("Example 2") {
  Solution s;
  std::vector<int> height = { 4, 2, 0, 3, 2, 5 };
  REQUIRE(s.trap(height) == 9);
}

TEST_CASE("Example 3") {
  Solution s;
  std::vector<int> height = { 5, 4, 1, 2 };
  REQUIRE(s.trap(height) == 1);
}

TEST_CASE("Example 4") {
  Solution s;
  std::vector<int> height = { 4, 2, 3 };
  REQUIRE(s.trap(height) == 1);
}
