// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
  SECTION("Drop Disk To Board", "[Drop]") { // #4
    DropDiskToBoard(student, DiskType::kPlayer1, 0);
    REQUIRE(student.board[0][0] == DiskType::kPlayer1);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 8), std::runtime_error); // #2
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -2), std::runtime_error); // #10
    DropDiskToBoard(student, DiskType::kPlayer2, 0);
    REQUIRE(student.board[1][0] == DiskType::kPlayer2);
    REQUIRE_FALSE(student.board[0][0] == DiskType::kPlayer2);
    student.board[2][0] = DiskType::kPlayer1;
    student.board[3][0] = DiskType::kPlayer1;
    student.board[4][0] = DiskType::kPlayer1;
    student.board[5][0] = DiskType::kPlayer1;
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 0), std::runtime_error);
  }
    SECTION("Check for Winner", "[Winner]") {
    for (unsigned int i = 0; i < 4; i++) {
      DropDiskToBoard(student, DiskType::kPlayer1, 2);
    }
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1)); // #8
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2)); // #5
  }
    SECTION("Board Location In Bounds", "[Bounds]") {
    REQUIRE_FALSE(BoardLocationInBounds(10, 0)); // #6
    REQUIRE_FALSE(BoardLocationInBounds(-2, 0));
    REQUIRE_FALSE(BoardLocationInBounds(0, -2));
    REQUIRE_FALSE(BoardLocationInBounds(0, 10));
  }
}

/* 
10 test cases
1. Dropping Disk out of bounds vertically (should be runtime error)
2. Dropping Disk when it's full (should be runtime error)
3. Dropping Disk out of bounds horizontally (should be runtime error)
4. CheckForWinner works
5. BoardLocationInBounds works
6. Connect4 works
7. Dropping Disk when out of bounds negative numbers
8.
9.
10.
*/

/////////////////////////////////////////////////////////////////////////////////////////////