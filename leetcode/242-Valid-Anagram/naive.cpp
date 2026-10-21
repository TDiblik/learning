#include <string>
#include <unordered_map>

class Solution {
public:
  bool isAnagram(std::string s, std::string t) {
    std::unordered_map<char, int> chars;
    for (char c : s) chars[c] += 1;
    for (char c : t) {
      if (chars[c] == 0) return false;
      chars[c] -= 1;
    }
    for (auto c : chars) if (c.second != 0) return false;

    return true;
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("should return true") {
  auto s = new Solution();
  REQUIRE(s->isAnagram("anagram", "nagaram"));
}

TEST_CASE("should return false") {
  auto s = new Solution();
  REQUIRE_FALSE(s->isAnagram("rat", "car"));
  REQUIRE_FALSE(s->isAnagram("ab", "a"));
}
