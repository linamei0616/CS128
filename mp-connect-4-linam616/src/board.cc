#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (int row = 0; row < Board::kBoardHeight; row++) {
    for (int col = 0; col < Board::kBoardWidth; col++) {
      b.board[row][col] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col >= Board::kBoardWidth || 
  (b.board[Board::kBoardHeight-1][col] != DiskType::kEmpty) || col < 0) {
    throw std::runtime_error("Runtime Error");
  }
  for (int row = 0; row < Board::kBoardHeight; row++) {
    if (b.board[row][col] == DiskType::kEmpty) {
      b.board[row][col] = disk;
      return;
    }
  }
}

bool CheckForWinner(Board& b, DiskType disk) {
  return (SearchForWinner(b, disk, WinningDirection::kHorizontal) 
  || SearchForWinner(b, disk, WinningDirection::kVertical)
  || SearchForWinner(b, disk, WinningDirection::kRightDiag) 
  || SearchForWinner(b, disk, WinningDirection::kLeftDiag));
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal) {
    return KHorizontal(b, disk);
  }
  if (to_check == WinningDirection::kVertical) {
    return KVertical(b, disk);
  }
  if (to_check == WinningDirection::kRightDiag) {
    return KRightDiag(b, disk);
  }
    if (to_check == WinningDirection::kLeftDiag) {
    return KLeftDiag(b, disk);
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  return (row < Board::kBoardHeight && col < Board::kBoardWidth && row >= 0 && col >= 0);
}

bool KHorizontal(Board& b, DiskType disk) { //smth abt these r wrong
  for (int row = 0; row < Board::kBoardHeight; row++) {
    for (int col = 0; col < Board::kBoardWidth - 3; col++) {
      if (b.board[row][col] == disk && b.board[row][col+1] == disk &&
      b.board[row][col+2] == disk && b.board[row][col+3] == disk) {
        return true;
      }
    }
  }
  return false;
}
bool KVertical(Board& b, DiskType disk) {
  for (int row = 0; row < Board::kBoardHeight - 2; row++) {
    for (int col = 0; col < Board::kBoardWidth; col++) {
      if (b.board[row][col] == disk && b.board[row+1][col] == disk &&
      b.board[row+2][col] == disk && b.board[row+3][col] == disk) {
        return true;
      }
    }
  }
  return false;
}
bool KRightDiag(Board& b, DiskType disk) {
  for (int row = 0; row < Board::kBoardHeight; row++) {
    for (int col = 0; col < Board::kBoardWidth; col++) {
        if (b.board[row][col] == disk && b.board[row+1][col+1] == disk &&
        b.board[row+2][col+2] == disk && b.board[row+3][col+3] == disk) {
          return true;
        }
    }
  }
  return false;
}
bool KLeftDiag(Board& b, DiskType disk) {
  for (int row = 0; row < Board::kBoardHeight; row++) {
    for (int col = 3; col < Board::kBoardWidth; col++) {
        if (b.board[row][col] == disk && b.board[row+1][col-1] == disk &&
        b.board[row+2][col-2] == disk && b.board[row+3][col-3] == disk) {
          return true;
        }
    }
  }
  return false;
}


/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}
