#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Solution {
public:
  static int removeElement(std::vector<int>& nums, int val) {
    int k = 0;
    for (size_t i = 0; i < nums.size(); i++) {
      if (nums[i] != val) {
        nums[(size_t)k] = nums[i];
        k += 1;
      }
    }
    return k;
  }
};

void runTest(std::vector<int> nums, int val, std::vector<int> expectedNums, const std::string& test_name) {
  std::vector<int> original_nums = nums;
  size_t k = (size_t)Solution::removeElement(nums, val);

  bool passed = true;
  if (k != expectedNums.size()) {
    passed = false;
  } else {
    std::sort(nums.begin(), nums.begin() + (long)k);
    std::sort(expectedNums.begin(), expectedNums.end());
    for (size_t i = 0; i < k; i++) {
      if (nums[i] != expectedNums[i]) {
        passed = false;
        break;
      }
    }
  }

  if (passed) {
    std::cout << "[PASS] " << test_name << "\n";
  } else {
    std::cout << "[FAIL] " << test_name << "\n";
    std::cout << "       Input: nums=[";
    for(size_t i=0; i<original_nums.size(); ++i) std::cout << original_nums[i] << (i<original_nums.size()-1 ? "," : "");
    std::cout << "], val=" << val << "\n";
    std::cout << "       Expected Length: " << expectedNums.size() << ", Got: " << k << "\n";
    std::cout << "       Expected Elements: [";
    for(size_t i=0; i<expectedNums.size(); ++i) std::cout << expectedNums[i] << (i<expectedNums.size()-1 ? "," : "");
    std::cout << "]\n       Got Elements: [";
    for(size_t i=0; i < k; ++i) std::cout << nums[i] << (i<k-1 ? "," : "");
    std::cout << "]\n\n";
  }
}

int main() {
    std::cout << "Running tests for Remove Element...\n\n";

    runTest({3, 2, 2, 3}, 3, {2, 2}, "Test 1 (Example 1)");
    runTest({0, 1, 2, 2, 3, 0, 4, 2}, 2, {0, 1, 4, 0, 3}, "Test 2 (Example 2)");
    runTest({}, 0, {}, "Test 3 (Empty array)");
    runTest({1, 2, 3, 4}, 5, {1, 2, 3, 4}, "Test 4 (No occurrences of val)");
    runTest({2, 2, 2, 2}, 2, {}, "Test 5 (Array consists entirely of val)");
    runTest({5}, 5, {}, "Test 6 (Single element, equals val)");
    runTest({5}, 4, {5}, "Test 7 (Single element, does not equal val)");
    runTest({2, 3, 4, 5}, 2, {3, 4, 5}, "Test 8 (Val is only at the beginning)");
    runTest({3, 4, 5, 2}, 2, {3, 4, 5}, "Test 9 (Val is only at the end)");
    runTest({4, 2, 2, 5, 6}, 2, {4, 5, 6}, "Test 10 (Consecutive vals in the middle)");

    std::cout << "\nFinished running tests.\n";
    return 0;
}
