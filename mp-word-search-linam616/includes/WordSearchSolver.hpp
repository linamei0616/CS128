#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle) {
    puzzle_ = puzzle;
    puzzle_height_ = puzzle.size();
    puzzle_width_ = puzzle.at(0).size();
  };
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);

// helper functions : 
  WordLocation FindWordkHorizontal(const std::string& word);
  WordLocation FindWordkVertical(const std::string& word);
  WordLocation FindWordkLeftDiag(const std::string& word);
  WordLocation FindWordkRightDiag(const std::string& word);
  std::string ReverseStr(std::string& str);

private:
  bool LocationInBounds(size_t row, size_t col) const;
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};


#endif