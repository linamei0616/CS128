// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <limits>

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Word Find Horizontal") {
    std::vector<std::vector<char>> puzzle{ {'d', 'e', 'a', 'o', 'u'},
                                           {'h', 'e', 'l', 'l', 'o'},
                                           {'c', 'a', 'l', 'o', 'm'},
                                           {'a', 'e', 't', 'a', 'u'},
                                           {'t', 'e', 't', 'o', 'u'},
                                           {'a', 'e', 'm', 'a', 't'}};
    WordSearchSolver wss(puzzle);

    SECTION("Word is hello") {
        WordLocation result = wss.FindWord("hello");
        REQUIRE(result.word == "hello");
        REQUIRE(result.char_positions.at(0).character == 'h');
        REQUIRE(result.char_positions.at(0).row == 1);
        REQUIRE(result.char_positions.at(0).col == 0);
        REQUIRE(result.char_positions.at(1).character == 'e');
        REQUIRE(result.char_positions.at(1).row == 1);
        REQUIRE(result.char_positions.at(1).col == 1);
    }
    SECTION("Word is 'e'") {
        WordLocation result = wss.FindWord("e");
        REQUIRE(result.word == "e");
        REQUIRE(result.char_positions.at(0).character == 'e');
        REQUIRE(result.char_positions.at(0).row == 0);
        REQUIRE(result.char_positions.at(0).col == 1);
    }
    SECTION("Word is mat") {
        WordLocation result = wss.FindWord("mat");
        REQUIRE(result.word == "mat");
        REQUIRE(result.char_positions.at(0).character == 'm');
        REQUIRE(result.char_positions.at(0).row == 5);
        REQUIRE(result.char_positions.at(0).col == 2);
    }
}

TEST_CASE("Word Find Vertical") {
    std::vector<std::vector<char>> puzzle{ {'d', 'e', 'a', 'o', 'u'},
                                           {'h', 'e', 'l', 'l', 'o'},
                                           {'c', 'a', 'l', 'o', 'm'},
                                           {'a', 'e', 't', 'a', 'u'},
                                           {'t', 'e', 't', 'o', 'u'},
                                           {'a', 'e', 'm', 'a', 't'}};
    WordSearchSolver wss(puzzle);
    SECTION("Word is cat") {
        WordLocation result = wss.FindWord("cat");
        REQUIRE(result.word == "cat");
        REQUIRE(result.char_positions.at(0).character == 'c');
        REQUIRE(result.char_positions.at(0).row == 2);
        REQUIRE(result.char_positions.at(0).col == 0);
    }
}
TEST_CASE("Word Find RightDiag") {
    std::vector<std::vector<char>> puzzle{ {'d', 'e', 'a', 'o', 'u'},
                                           {'h', 'e', 'l', 'l', 'o'},
                                           {'c', 'a', 'l', 'o', 'y'},
                                           {'a', 'e', 't', 'a', 'p'},
                                           {'t', 'e', 't', 'a', 'u'},
                                           {'a', 'e', 't', 'a', 't'}};
    WordSearchSolver wss(puzzle);
    SECTION("Word is hat") {
        WordLocation result = wss.FindWord("hat");
        REQUIRE(result.word == "hat");
        REQUIRE(result.char_positions.at(0).character == 'h');
        REQUIRE(result.char_positions.at(0).row == 1);
        REQUIRE(result.char_positions.at(0).col == 0);
        REQUIRE(result.char_positions.at(0).character == 'a');
        REQUIRE(result.char_positions.at(0).row == 2);
        REQUIRE(result.char_positions.at(0).col == 1);
        std::cout << result << std::endl;
    }
}
TEST_CASE("Word Find LeftDiag") {
    std::vector<std::vector<char>> puzzle{ {'d', 'e', 'a', 'o', 'u'},
                                           {'h', 'e', 'l', 'l', 'o'},
                                           {'c', 'a', 'l', 'o', 'y'},
                                           {'a', 'e', 't', 'a', 'p'},
                                           {'t', 'e', 't', 'a', 'u'},
                                           {'a', 'e', 't', 'a', 't'}};
    WordSearchSolver wss(puzzle);
    SECTION("Word is pat") {
        WordLocation result = wss.FindWord("pat");
        REQUIRE(result.word == "pat");
        REQUIRE(result.char_positions.at(0).character == 'p');
        REQUIRE(result.char_positions.at(0).row == 3);
        REQUIRE(result.char_positions.at(0).col == 4);
        REQUIRE(result.char_positions.at(0).character == 'a');
        REQUIRE(result.char_positions.at(0).row == 4);
        REQUIRE(result.char_positions.at(0).col == 3);
        std::cout << result << std::endl;
    }
}
// REQUIRE(result.char_positions == {}
/////////////////////////////////////////////////////////////////////////////////////////////