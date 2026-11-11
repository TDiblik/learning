#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

class Solution {
public:
  int carFleet(int target, std::vector<int>& position, std::vector<int>& speed) {
    std::vector<std::pair<int, int>> res; // first -> position ; second -> speed

    assert(speed.size() > 0);
    for (size_t i = 0; i < position.size(); i++) res.emplace_back(position[i], speed[i]);
    std::sort(res.rbegin(), res.rend());

    int groups = 0;
    double latest_group_time = 0;
    for (const auto [first, second] : res) {
      double solo_time = static_cast<double>(target - first) / second;

      if (solo_time > latest_group_time) {
        groups++;
        latest_group_time = solo_time;
      }
    }

    return groups;
  }
};

#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Example 1") {
  Solution s;

  std::vector<int> pos = { 10, 8, 0, 5, 3 };
  std::vector<int> speed = { 2, 4, 1, 1, 3 };
  REQUIRE(s.carFleet(12, pos, speed) == 3);
}

TEST_CASE("Example 2") {
  Solution s;

  std::vector<int> pos = { 3 };
  std::vector<int> speed = { 3 };
  REQUIRE(s.carFleet(10, pos, speed) == 1);
}

TEST_CASE("Example 3") {
  Solution s;

  std::vector<int> pos = { 0, 2, 4 };
  std::vector<int> speed = { 4, 2, 1 };
  REQUIRE(s.carFleet(100, pos, speed) == 1);
}

TEST_CASE("Example 4") {
  Solution s;

  std::vector<int> pos = { 2, 4 };
  std::vector<int> speed = { 3, 2 };
  REQUIRE(s.carFleet(10, pos, speed) == 1);
}

TEST_CASE("Example 5") {
  Solution s;

  std::vector<int> pos = { 4, 6 };
  std::vector<int> speed = { 3, 2 };
  REQUIRE(s.carFleet(10, pos, speed) == 1);
}
