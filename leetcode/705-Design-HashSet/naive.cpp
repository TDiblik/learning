#include <functional>
#include <iostream>
#include <string>

class MyHashSet {
private:
  std::hash<int> _hash = std::hash<int>{};

public:
  MyHashSet() {}

  void add(int key) {
    auto resp = _hash(key);
    std::cout << "Hash: " << resp << "\n";
  }

  void remove(int key) { (void)key; }

  bool contains(int key) {
    (void)key;
    return false;
  }
};

#define CATCH_CONFIG_MAIN
#include "../../vendor/catch2/catch.hpp"

TEST_CASE("Design HashSet") {
  SECTION("Test 1 (Example)") {
    MyHashSet set;
    set.add(1);
    set.add(2);
    CHECK(set.contains(1) == true);
    CHECK(set.contains(3) == false);

    set.add(2);
    CHECK(set.contains(2) == true);

    set.remove(2);
    CHECK(set.contains(2) == false);
  }

  SECTION("Test 2 (Remove non-existent element)") {
    MyHashSet set;
    set.remove(10);
    CHECK(set.contains(10) == false);
  }

  SECTION("Test 3 (Constraint Boundaries - Max value)") {
    MyHashSet set;
    int max_val = 1000000;
    set.add(max_val);
    CHECK(set.contains(max_val) == true);

    set.remove(max_val);
    CHECK(set.contains(max_val) == false);
  }

  SECTION("Test 4 (Constraint Boundaries - Min value)") {
    MyHashSet set;
    set.add(0);
    CHECK(set.contains(0) == true);

    set.remove(0);
    CHECK(set.contains(0) == false);
  }
}
