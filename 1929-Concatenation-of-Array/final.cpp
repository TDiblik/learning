#include <iostream>
#include <vector>

class Solution {
public:
    static std::vector<int> getConcatenation(std::vector<int>& nums) {
      std::vector<int> ans;
      ans.reserve(nums.size() * 2);

      ans.insert(ans.end(), nums.begin(), nums.end());
      ans.insert(ans.end(), nums.begin(), nums.end());

      return ans;
    }
};

void runTest(std::vector<int> input, std::vector<int> expected, const std::string& test_name) {
  std::vector<int> result = Solution::getConcatenation(input);

  if (result == expected) {
    std::cout << test_name << " Passed\n";
  } else {
    std::cout << test_name << " Failed\n";
    std::cout << "   Expected size: " << expected.size() << ", Got: " << result.size() << "\n";
  }
}

int main() {
    std::cout << "Running tests for getConcatenation...\n\n";

    runTest({1, 4, 1, 2}, {1, 4, 1, 2, 1, 4, 1, 2}, "Test 1 (Example 1)");
    runTest({22, 21, 20, 1}, {22, 21, 20, 1, 22, 21, 20, 1}, "Test 2 (Example 2)");
    runTest({7}, {7, 7}, "Test 3 (Single Element)");
    runTest({5, 5, 5}, {5, 5, 5, 5, 5, 5}, "Test 4 (Identical Elements)");

    std::vector<int> large_input(1000, 1);
    std::vector<int> large_exptected(2000, 1);
    runTest(large_input, large_exptected, "Test 5 (Max Length Array)");

    std::cout << "\nFinished running tests.\n";
    return 0;
}
