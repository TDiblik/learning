#include <stack>
#include <string>

class Solution {
public:
  // s consists of parentheses only '()[]{}'.
  bool isValid(std::string s) {
    std::stack<char> st;

    for (char c : s) {
      if (c == '(' || c == '[' || c == '{') {
        st.push(c);
        continue;
      }

      if (st.empty()) return false;

      auto top = st.top();
      if (
        (top == '(' && c != ')') ||
        (top == '[' && c != ']') ||
        (top == '{' && c != '}')
      ) {
        return false;
      }
      st.pop();
    }

    return st.empty();
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("Example 1") {
  Solution s;
  REQUIRE(s.isValid("()"));
}

TEST_CASE("Example 2") {
  Solution s;
  REQUIRE(s.isValid("()[]{}"));
}

TEST_CASE("Example 3") {
  Solution s;
  REQUIRE_FALSE(s.isValid("(]"));
}

TEST_CASE("Example 4") {
  Solution s;
  REQUIRE(s.isValid("([])"));
}

TEST_CASE("Example 5") {
  Solution s;
  REQUIRE_FALSE(s.isValid("([)]"));
}

TEST_CASE("Example 6") {
  Solution s;
  REQUIRE_FALSE(s.isValid("["));
}

TEST_CASE("Example 7") {
  Solution s;
  REQUIRE_FALSE(s.isValid("]"));
}
