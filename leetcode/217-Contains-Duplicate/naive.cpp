#include <iostream>
#include <unordered_set>
#include <vector>

class Solution {
public:
  static bool containsDuplicate(std::vector<int>& nums) {
    std::unordered_set<int> seen;

    for (size_t i = 0; i < nums.size(); i++) {
      int current = nums[i];
      if (seen.find(current) != seen.end()) return true;
      seen.insert(current);
    }

    return false;
  }
};

void runTest(std::vector<int> input, bool expected, const std::string& test_name) {
  bool result = Solution::containsDuplicate(input);
  if (result == expected) {
    std::cout << test_name << " Passed\n";
  } else {
    std::cout << test_name << " Failed\n";
    std::cout << "   Expected: " << (expected ? "true" : "false") << ", Got: " << (result ? "true" : "false") << "\n";
  }
}

int main() {
  std::cout << "Running tests for containsDuplicate...\n\n";

  runTest({1, 2, 3, 1}, true, "Test 1 (Example 1)");
  runTest({1, 2, 3, 4}, false, "Test 2 (Example 2)");
  runTest({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}, true, "Test 3 (Example 3)");
  runTest({42}, false, "Test 4 (Single Element)");
  runTest({-1000000000, 1000000000, -1000000000}, true, "Test 5 (Extreme Values)");

  std::vector<int> large_input;
  large_input.reserve(100000);
  for (int i = 0; i < 99999; ++i) {
    large_input.push_back(i);
  }
  large_input.push_back(0);
  runTest(large_input, true, "Test 6 (Max Length Array 10^5)");

  std::cout << "\nFinished running tests.\n";
  return 0;
}
