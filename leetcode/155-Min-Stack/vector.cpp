#include <cassert>
#include <climits>
#include <vector>

class MinStack {
private:
  std::vector<std::pair<int, int>> st; // first -> value ; second -> minValue

public:
  MinStack() {
    st.reserve(30'000); // at most 3 * 10^4 calls, we can assume max amount of elements
  }

  void push(int value) {
    if (st.empty()) [[unlikely]] {
      st.emplace_back(value, value);
      return;
    }

    st.emplace_back(value, std::min(this->getMin(), value));
  }

  void pop() {
    assert(!st.empty());
    st.pop_back();
  }

  int top() const noexcept {
    assert(!st.empty());
    return st.back().first;
  }

  int getMin() const noexcept {
    assert(!st.empty());
    return st.back().second;
  }
};

// push(5)  → stack: [5]        min: 5
// push(3)  → stack: [5, 3]     min: 3
// push(7)  → stack: [5, 3, 7]  min: 3
// pop()    → stack: [5, 3]     min: 3
// pop()    → stack: [5]        min: 5

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("Example 1") {
  MinStack minStack;
  minStack.push(-2);
  minStack.push(0);
  minStack.push(-3);
  REQUIRE(minStack.getMin() == -3);  // return -3
  minStack.pop();
  REQUIRE(minStack.top() == 0);      // return 0
  REQUIRE(minStack.getMin() == -2);  // return -2
}

TEST_CASE("MinStack - INT_MIN and INT_MAX edge cases") {
  MinStack st;

  st.push(INT_MAX - 1);
  st.push(INT_MAX - 1);
  st.push(INT_MAX);

  REQUIRE(st.top() == INT_MAX);

  st.pop();
  REQUIRE(st.getMin() == INT_MAX - 1);

  st.pop();
  REQUIRE(st.getMin() == INT_MAX - 1);

  st.pop();

  st.push(INT_MAX);
  REQUIRE(st.top() == INT_MAX);
  REQUIRE(st.getMin() == INT_MAX);

  st.push(INT_MIN);
  REQUIRE(st.top() == INT_MIN);
  REQUIRE(st.getMin() == INT_MIN);

  st.pop();
  REQUIRE(st.getMin() == INT_MAX);
}
