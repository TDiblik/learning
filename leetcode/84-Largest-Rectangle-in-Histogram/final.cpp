#include <cassert>
#include <cstddef>
#include <vector>

class Solution {
public:
  int largestRectangleArea(std::vector<int>& heights) {
    // todo: right now i get time limited on leetcode.
    // the final solution should have somehing to do with monotonic stacks.
  }
};



#include "../../vendor/catch2/catch.hpp"
TEST_CASE("Example 1") {
  Solution s;
  std::vector<int> input = { 2, 1, 5, 6, 2, 3 };
  REQUIRE(s.largestRectangleArea(input) == 10);
}

TEST_CASE("Example 2") {
  Solution s;
  std::vector<int> input = { 2, 4 };
  REQUIRE(s.largestRectangleArea(input) == 4);
}

TEST_CASE("Example 3") {
  Solution s;
  std::vector<int> input = { 1 };
  REQUIRE(s.largestRectangleArea(input) == 1);
}

TEST_CASE("Example 4") {
  Solution s;
  std::vector<int> input = { 2,1,2 };
  REQUIRE(s.largestRectangleArea(input) == 3);
}

TEST_CASE("Example 5") {
  Solution s;
  std::vector<int> input(30000, 1);
  REQUIRE(s.largestRectangleArea(input) == 30000);
}
