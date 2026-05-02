#include <iostream>
#include <vector>

class Solution {
public:
  static std::vector<int> twoSum(std::vector<int>& nums, int target) {
    for (size_t i = 0; i < nums.capacity(); i++) {
      for (size_t j = 0; j < nums.capacity(); j++) {
        if (i == j) continue;
        if (nums[i] + nums[j] == target) return {(int)i, (int)j};
      }
    }
    return {};
  }
};

int main() {
  int target = 9;
  std::vector<int> nums = {2,7,11,15};

  auto solution = Solution::twoSum(nums, target);
  for (int c : solution) {
    std::cout << c << "\n";
  }
}
