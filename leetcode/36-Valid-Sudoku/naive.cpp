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

    for (size_t i = 0; i < num_of_rows; i++) {
      for (size_t j = 0; j < num_of_cols; j++) {
        uintf val = 0;
        char c = board[i][j];
        switch (c) {
          case '.': break;
          case '1': val = 1; break;
          case '2': val = 2; break;
          case '3': val = 3; break;
          case '4': val = 4; break;
          case '5': val = 5; break;
          case '6': val = 6; break;
          case '7': val = 7; break;
          case '8': val = 8; break;
          case '9': val = 9; break;
          default: break;
        }

        board_parsed[i][j] = val;
      }
    }

    std::unordered_map<size_t, std::unordered_set<uintf>> seen_rows; // row index as index
    for (size_t i = 0; i < num_of_rows; i++) {
      for (size_t j = 0; j < num_of_cols; j++) {
        auto v = board_parsed[i][j];
        if (v != 0 && !seen_rows[i].insert(v).second) return false;
      }
    }

    std::unordered_map<size_t, std::unordered_set<uintf>> seen_cols; // col index as index
    for (size_t i = 0; i < num_of_rows; i++) {
      for (size_t j = 0; j < num_of_cols; j++) {
        auto v = board_parsed[i][j];
        if (v != 0 && !seen_cols[j].insert(v).second) return false;
      }
    }

    for (size_t i = 1; i < num_of_rows; i += 3) {
      for (size_t j = 1; j < num_of_cols; j += 3) {
        std::unordered_set<uintf> seen;
        #define check(val) if (val != 0 && !seen.insert(val).second) return false;
        check(board_parsed[i-1][j-1]);
        check(board_parsed[i-1][j]);
        check(board_parsed[i-1][j+1]);

        check(board_parsed[i][j-1]);
        check(board_parsed[i][j]);
        check(board_parsed[i][j+1]);

        check(board_parsed[i+1][j-1]);
        check(board_parsed[i+1][j]);
        check(board_parsed[i+1][j+1]);
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
