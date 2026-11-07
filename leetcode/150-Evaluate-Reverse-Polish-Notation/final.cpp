#include <stack>
#include <string>
#include <vector>

class Solution {
public:
  int evalRPN(std::vector<std::string>& tokens) {
    std::stack<int> calcs;

    for (std::string& s : tokens) {
      const size_t s_len = s.length();
      const char fchar = s[0]; // empty tokens are forbidded by the assignment

      if (s_len == 1 && fchar == '+') {
        int second_operand = calcs.top();
        calcs.pop();
        int first_operand = calcs.top();
        calcs.pop();

        calcs.push(first_operand + second_operand);
        continue;
      }
      if (s_len == 1 && fchar == '-') {
        int second_operand = calcs.top();
        calcs.pop();
        int first_operand = calcs.top();
        calcs.pop();

        calcs.push(first_operand - second_operand);
        continue;
      }
      if (s_len == 1 && fchar == '*') {
        int second_operand = calcs.top();
        calcs.pop();
        int first_operand = calcs.top();
        calcs.pop();

        calcs.push(first_operand * second_operand);
        continue;
      }
      if (s_len == 1 && fchar == '/') {
        int second_operand = calcs.top();
        calcs.pop();
        int first_operand = calcs.top();
        calcs.pop();

        calcs.push(first_operand / second_operand); // devision by zero is forbidded by the assignment
        continue;
      }


      int value = 0;
      size_t i = 0;
      int multiplier = 1;

      if (fchar == '-') {
        value += (s[1] - '0') * -1;
        i = 2;
        multiplier = -1;
      }

      for (; i < s.size(); i++) {
        value *= 10;
        value += (s[i] - '0') * multiplier;
      }

      calcs.push(value);
    }

    return calcs.top();
  }
};

#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Example 1") {
  Solution s;
  std::vector<std::string> input = { "2", "1", "+", "3", "*" };
  REQUIRE(s.evalRPN(input) == 9);
}

TEST_CASE("Example 2") {
  Solution s;
  std::vector<std::string> input = { "4", "13", "5", "/", "+" };
  REQUIRE(s.evalRPN(input) == 6);
}

TEST_CASE("Example 3") {
  Solution s;
  std::vector<std::string> input = { "10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+" };
  REQUIRE(s.evalRPN(input) == 22);
}

TEST_CASE("Example 4") {
  Solution s;
  std::vector<std::string> input = { "3", "-4", "+" };
  REQUIRE(s.evalRPN(input) == -1);
}

TEST_CASE("Example 5") {
  Solution s;
  std::vector<std::string> input = {"-11", "2", "*"};
  REQUIRE(s.evalRPN(input) == -22);
}
