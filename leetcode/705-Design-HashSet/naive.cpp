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

  void remove(int key) {}

  bool contains(int key) { }
};

void checkResult(bool expected, bool got, const std::string &test_name) {
  if (expected == got) {
    std::cout << "[PASS] " << test_name << "\n";
  } else {
    std::cout << "[FAIL] " << test_name << "\n";
    std::cout << "       Expected: " << (expected ? "true" : "false") << ", Got: " << (got ? "true" : "false") << "\n\n";
  }
}

int main() {
  std::cout << "Running tests for Design HashSet...\n\n";

  // --- Test 1: LeetCode Example 1 ---
  {
    MyHashSet set;
    set.add(1);
    set.add(2);
    checkResult(true, set.contains(1), "Test 1.1 (Example: contains 1)");
    checkResult(false, set.contains(3), "Test 1.2 (Example: contains 3)");

    set.add(2);
    checkResult(true, set.contains(2), "Test 1.3 (Example: contains 2 after duplicate add)");

    set.remove(2);
    checkResult(false, set.contains(2), "Test 1.4 (Example: contains 2 after remove)");
  }

  // --- Test 2: Removing a non-existent element ---
  {
    MyHashSet set;
    set.remove(10); // Should do nothing and not crash
    checkResult(false, set.contains(10), "Test 2 (Remove non-existent element)");
  }

  // --- Test 3: Constraint Boundaries (Max value: 10^6) ---
  {
    MyHashSet set;
    int max_val = 1000000;
    set.add(max_val);
    checkResult(true, set.contains(max_val), "Test 3.1 (Max boundary element added)");

    set.remove(max_val);
    checkResult(false, set.contains(max_val), "Test 3.2 (Max boundary element removed)");
  }

  // --- Test 4: Constraint Boundaries (Min value: 0) ---
  {
    MyHashSet set;
    set.add(0);
    checkResult(true, set.contains(0), "Test 4.1 (Min boundary element 0 added)");

    set.remove(0);
    checkResult(false, set.contains(0), "Test 4.2 (Min boundary element 0 removed)");
  }

  std::cout << "\nFinished running tests.\n";
  return 0;
}
