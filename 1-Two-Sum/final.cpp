#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
  static std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> mapping;

    for (size_t i = 0; i < nums.size(); i++) {
      int complement = target - nums[i];
      if (mapping.find(complement) != mapping.end()) {
        return {mapping[complement], (int)i};
      }
      mapping[nums[i]] = (int)i;
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
