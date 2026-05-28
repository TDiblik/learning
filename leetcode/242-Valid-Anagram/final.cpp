#include <string>
#include <sys/types.h>
#include <unordered_map>

class Solution {
public:
  static bool isAnagram(std::string s, std::string t) {
    if (s.length() != t.length()) return false;

    std::unordered_map<char, uint> s_seen;
    for (char c : s) {
      s_seen[c] += 1;
    }

    std::unordered_map<char, uint> t_seen;
    for (char c : t) {
      t_seen[c] += 1;
    }

    for (auto p : s_seen) {
      if (p.second != t_seen[p.first]) return false;
      t_seen.erase(p.first);
    }

    return t_seen.empty();
  }
};

#define CATCH_CONFIG_MAIN
#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Valid Anagram") {
  SECTION("Test 1 (Example 1)") { CHECK(Solution::isAnagram("anagram", "nagaram") == true); }
  SECTION("Test 2 (Example 2)") { CHECK(Solution::isAnagram("rat", "car") == false); }
  SECTION("Test 3 (Single Character Match)") { CHECK(Solution::isAnagram("a", "a") == true); }
  SECTION("Test 4 (Single Character Mismatch)") { CHECK(Solution::isAnagram("a", "b") == false); }
  SECTION("Test 5 (Length Mismatch - s > t)") { CHECK(Solution::isAnagram("ab", "a") == false); }
  SECTION("Test 6 (Length Mismatch - t > s)") { CHECK(Solution::isAnagram("a", "ab") == false); }
  SECTION("Test 7 (Multiple Characters, Correct Frequencies)") { CHECK(Solution::isAnagram("aabbcc", "abcabc") == true); }
  SECTION("Test 8 (Same Length, One Different Character)") { CHECK(Solution::isAnagram("aabbcc", "aabbcd") == false); }
  SECTION("Test 9 (Same Characters, Different Frequencies)") { CHECK(Solution::isAnagram("aacc", "ccac") == false); }
  SECTION("Test 10 (Max Length Strings 5 * 10^4)") {
    std::string large_s(50000, 'a');
    std::string large_t(50000, 'a');
    large_s[25000] = 'z';
    large_t[49999] = 'z';
    CHECK(Solution::isAnagram(large_s, large_t) == true);
  }
}
