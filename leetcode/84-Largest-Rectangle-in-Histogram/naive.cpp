#include <cassert>
#include <cstddef>
#include <stack>
#include <vector>

class MinStack {
private:
  std::stack<std::pair<int, int>> st; // first -> value ; second -> min value

public:
  MinStack() {}

  void push(int value) {
    if (st.empty()) [[unlikely]] {
      st.emplace(value, value);
      return;
    }

    st.emplace(value, std::min(this->getMin(), value));
  }

  void pop() {
    assert(!st.empty());
    st.pop();
  }

  int top() const noexcept {
    assert(!st.empty());
    return st.top().first;
  }

  int getMin() const noexcept {
    assert(!st.empty());
    return st.top().second;
  }

  bool empty() const noexcept {
    return st.empty();
  }
};

class Solution {
public:
  int largestRectangleArea(std::vector<int>& heights) {
    std::vector<MinStack> min_st(heights.size(), MinStack());

    for (size_t i = 0; i < heights.size(); i++) {
      for (size_t j = i; j < heights.size(); j++) {
        if (!min_st[i].empty() && min_st[i].getMin() > heights[j]) break;
        min_st[i].push(heights[j]);
      }
      for (size_t j = i; j-- > 0;) {
        if (!min_st[i].empty() && min_st[i].getMin() > heights[j]) break;
        min_st[i].push(heights[j]);
      }
    }

    int largest = 0;
    for (auto s : min_st) {
      if (s.empty()) continue;

      const int min = s.getMin();
      int multiplier = 0;
      while (!s.empty()) {
        multiplier++;
        s.pop();
      }

      const int area = min * multiplier;
      if (area > largest) largest = area;
    }

    return largest;
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
