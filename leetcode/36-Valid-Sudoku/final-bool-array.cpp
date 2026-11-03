#include <cstddef>
#include <vector>

class Solution {
public:
  bool isValidSudoku(std::vector<std::vector<char>>& board) {
    const size_t n = board.size();

    const size_t boxesPerRow = n / 3;
    const size_t boxCount = boxesPerRow * boxesPerRow;

    std::vector<std::array<bool, 9>> rows(n);
    std::vector<std::array<bool, 9>> cols(n);
    std::vector<std::array<bool, 9>> boxes(boxCount);

    for (size_t i = 0; i < n; ++i) {
      if (board[i].size() != n) return false;

      for (size_t j = 0; j < n; ++j) {
        const char c = board[i][j];
        if (c == '.') continue;

        const size_t num = static_cast<size_t>(c - '1');
        const size_t boxIndex = (i / 3) * boxesPerRow + (j / 3);

        if (rows[i][num] || cols[j][num] || boxes[boxIndex][num]) return false;

        rows[i][num] = true;
        cols[j][num] = true;
        boxes[boxIndex][num] = true;
      }
    }

    return true;
  }
};

#include "../../vendor/catch2/catch.hpp"
TEST_CASE("example 1") {
  Solution s;
  std::vector<std::vector<char>> board = {
     {'5','3','.','.','7','.','.','.','.'}
    ,{'6','.','.','1','9','5','.','.','.'}
    ,{'.','9','8','.','.','.','.','6','.'}
    ,{'8','.','.','.','6','.','.','.','3'}
    ,{'4','.','.','8','.','3','.','.','1'}
    ,{'7','.','.','.','2','.','.','.','6'}
    ,{'.','6','.','.','.','.','2','8','.'}
    ,{'.','.','.','4','1','9','.','.','5'}
    ,{'.','.','.','.','8','.','.','7','9'}
  };
  REQUIRE(s.isValidSudoku(board));
}

TEST_CASE("example 2 - catch col duplication") {
  Solution s;
  std::vector<std::vector<char>> board = {
    // here -> 8
    // ˇ
     {'8','3','.','.','7','.','.','.','.'}
    ,{'6','.','.','1','9','5','.','.','.'}
    ,{'.','9','8','.','.','.','.','6','.'}
    ,{'8','.','.','.','6','.','.','.','3'}
    ,{'4','.','.','8','.','3','.','.','1'}
    ,{'7','.','.','.','2','.','.','.','6'}
    ,{'.','6','.','.','.','.','2','8','.'}
    ,{'.','.','.','4','1','9','.','.','5'}
    ,{'.','.','.','.','8','.','.','7','9'}
  };
  REQUIRE_FALSE(s.isValidSudoku(board));
}

TEST_CASE("example 3 - catch row duplication") {
  Solution s;
  std::vector<std::vector<char>> board = {
     {'8','3','.','.','7','.','.','8','.'} // here -> 8
    ,{'6','.','.','1','9','5','.','.','.'}
    ,{'.','9','8','.','.','.','.','6','.'}
    ,{'5','.','.','.','6','.','.','.','3'}
    ,{'4','.','.','8','.','3','.','.','1'}
    ,{'7','.','.','.','2','.','.','.','6'}
    ,{'.','6','.','.','.','.','2','8','.'}
    ,{'.','.','.','4','1','9','.','.','5'}
    ,{'.','.','.','.','8','.','.','7','9'}
  };
  REQUIRE_FALSE(s.isValidSudoku(board));
}
