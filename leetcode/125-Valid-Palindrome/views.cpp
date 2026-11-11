#include <algorithm>
#include <ranges>
#include <string>

class Solution {
public:
  bool isPalindrome(std::string s) {
    auto cleaned = s |
      std::views::transform([](char c){
          if (c >= 'A' && c <= 'Z') return (char)(c + ('a' - 'A'));
          else if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) return c;
          else return ' ';
        }
      ) |
      std::views::filter([](char c) { return !std::isspace(c); });

    return std::ranges::equal(cleaned, cleaned | std::views::reverse);
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("Example 1") {
 Solution s;
 REQUIRE(s.isPalindrome("A man, a plan, a canal: Panama"));
}

TEST_CASE("Example 2") {
 Solution s;
 REQUIRE_FALSE(s.isPalindrome("race a car"));
}

TEST_CASE("Example 3") {
 Solution s;
 REQUIRE(s.isPalindrome(" "));
}

TEST_CASE("Example 4") {
 Solution s;
 REQUIRE_FALSE(s.isPalindrome("0P"));
}
