#include <string>

class Solution {
public:
  bool isAnagram(std::string s, std::string t) {
    int counts[26] = {0}; // letters of the alphabet

    // c-'a' => ensure out ascii range is from 0 - 25
    for (char& c : s) counts[(int)c-'a'] += 1;
    for (char& c : t) {
      if (counts[(int)c-'a'] == 0) return false;
      counts[(int)c-'a'] -= 1;
    }
    for (auto c : counts) if (c != 0) return false;

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
