#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
public:
  bool isValidSudoku(std::vector<std::vector<char>>& board) {
    if (board.size() < 1) return false;

    using uintf = uint_fast8_t;
    const size_t num_of_rows = board.size();
    const size_t num_of_cols = board[0].size();
    std::vector<std::vector<uintf>> board_parsed(num_of_rows, std::vector<uintf>(num_of_cols, 0));

    std::unordered_map<size_t, std::unordered_set<uintf>> seen_rows; // row index as index
    std::unordered_map<size_t, std::unordered_set<uintf>> seen_cols; // col index as index
    for (size_t i = 0; i < num_of_rows; i++) {
      for (size_t j = 0; j < num_of_cols; j++) {
        uintf v = 0;
        char c = board[i][j];
        switch (c) {
          case '.': break;
          case '1': v = 1; break;
          case '2': v = 2; break;
          case '3': v = 3; break;
          case '4': v = 4; break;
          case '5': v = 5; break;
          case '6': v = 6; break;
          case '7': v = 7; break;
          case '8': v = 8; break;
          case '9': v = 9; break;
          default: break;
        }

        board_parsed[i][j] = v;
        if (v != 0 && !seen_rows[i].insert(v).second) return false;
        if (v != 0 && !seen_cols[j].insert(v).second) return false;

        // on every bottom right of 3x3
        if (i % 3 == 2 && j % 3 == 2) {
          std::unordered_set<uintf> seen;
          #define check(val) if (val != 0 && !seen.insert(val).second) return false;

          check(board_parsed[i-2][j-2]);
          check(board_parsed[i-2][j-1]);
          check(board_parsed[i-2][j]);

          check(board_parsed[i-1][j-2]);
          check(board_parsed[i-1][j-1]);
          check(board_parsed[i-1][j]);

          check(board_parsed[i][j-2]);
          check(board_parsed[i][j-1]);
          check(board_parsed[i][j]);
        }
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
