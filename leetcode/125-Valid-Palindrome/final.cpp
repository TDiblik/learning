#include <string>

class Solution {
public:
  bool isPalindrome(std::string s) {
    size_t p_left = 0;
    size_t p_right = s.size() - 1;

    while (p_left < p_right) {
      char left = s[p_left];
      char right = s[p_right];

      if (left >= 'A' && left <= 'Z') left += ('a' - 'A');
      if (right >= 'A' && right <= 'Z') right += ('a' - 'A');

      if ((left < 'a' && !(left >= '0' && left <= '9')) || left > 'z') {
        p_left++;
        continue;
      }
      if ((right < 'a' && !(right >= '0' && right <= '9')) || right > 'z') {
        p_right--;
        continue;
      }

      if (left == right) {
        p_left++;
        p_right--;
        continue;
      }

      return false;
    }

    return true;
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

TEST_CASE("Example 5") {
 Solution s;
 REQUIRE(s.isPalindrome("aa"));
}
