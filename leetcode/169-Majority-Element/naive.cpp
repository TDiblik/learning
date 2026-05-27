#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
public:
  static int majorityElement(std::vector<int> &nums) {
    std::unordered_map<int, uint> counted;

    for (int num : nums) counted[num] += 1;
    for (auto count : counted) {
      if (count.second > nums.size() / 2) return count.first;
    }

    std::unreachable();
  }
};

void runTest(std::vector<int> nums, int expected, const std::string &test_name) {
  std::vector<int> original_nums = nums;
  int result = Solution::majorityElement(nums);

  if (result == expected) {
    std::cout << "[PASS] " << test_name << "\n";
  } else {
    std::cout << "[FAIL] " << test_name << "\n";
    std::cout << "       Input: nums=[";
    for (size_t i = 0; i < original_nums.size(); ++i) {
      std::cout << original_nums[i] << (i < original_nums.size() - 1 ? "," : "");
    }
    std::cout << "]\n";
    std::cout << "       Expected: " << expected << ", Got: " << result << "\n\n";
  }
}

int main() {
  std::cout << "Running tests for Majority Element...\n\n";

  // Problem Examples
  runTest({3, 2, 3}, 3, "Test 1 (Example 1)");
  runTest({2, 2, 1, 1, 1, 2, 2}, 2, "Test 2 (Example 2)");

  // Additional Edge Cases
  runTest({5}, 5, "Test 3 (Single element)");
  runTest({1, 1, 1, 1}, 1, "Test 4 (All elements the same)");
  runTest({1, 2, 2, 2, 2}, 2, "Test 5 (Majority clustered at the end)");
  runTest({2, 2, 2, 2, 1}, 2, "Test 6 (Majority clustered at the beginning)");
  runTest({6, 5, 5, 6, 5}, 5, "Test 7 (Alternating elements with majority)");

  std::cout << "\nFinished running tests.\n";
  return 0;
}
