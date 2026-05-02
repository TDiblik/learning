#include <iostream>
#include <string>
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
    if (!t_seen.empty()) return false;

    return true;
  }
};

void runTest(const std::string& s, const std::string& t, bool expected, const std::string& test_name) {
  bool result = Solution::isAnagram(s, t);
  if (result == expected) {
    std::cout << test_name << " Passed\n";
  } else {
    std::cout << test_name << " Failed\n";
    std::cout << "   Expected: " << (expected ? "true" : "false") << ", Got: " << (result ? "true" : "false") << "\n";
  }
}

int main() {
  std::cout << "Running tests for Valid Anagram...\n\n";

  runTest("anagram", "nagaram", true, "Test 1 (Example 1)");
  runTest("rat", "car", false, "Test 2 (Example 2)");
  runTest("a", "a", true, "Test 3 (Single Character Match)");
  runTest("a", "b", false, "Test 4 (Single Character Mismatch)");
  runTest("ab", "a", false, "Test 5 (Length Mismatch - s > t)");
  runTest("a", "ab", false, "Test 6 (Length Mismatch - t > s)");
  runTest("aabbcc", "abcabc", true, "Test 7 (Multiple Characters, Correct Frequencies)");
  runTest("aabbcc", "aabbcd", false, "Test 8 (Same Length, One Different Character)");
  runTest("aacc", "ccac", false, "Test 9 (Same Characters, Different Frequencies)");
  std::string large_s(50000, 'a');
  std::string large_t(50000, 'a');
  large_s[25000] = 'z';
  large_t[49999] = 'z';
  runTest(large_s, large_t, true, "Test 10 (Max Length Strings 5 * 10^4)");

  std::cout << "\nFinished running tests.\n";
  return 0;
}
