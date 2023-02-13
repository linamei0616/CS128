#include "WordSearchSolver.hpp"
#include "CharPositions.hpp" 
#include "WordLocation.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <limits>

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation temp_location;
  temp_location = FindWord(word, CheckDirection::kHorizontal);
  if (!(temp_location.char_positions.empty())) {return temp_location;}
  temp_location = FindWord(word, CheckDirection::kVertical);
  if (!(temp_location.char_positions.empty())) {return temp_location;}
  temp_location = FindWord(word, CheckDirection::kRightDiag);
  if (!(temp_location.char_positions.empty())) {return temp_location;}
  temp_location = FindWord(word, CheckDirection::kLeftDiag);
  return temp_location;
}

WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction) {
  WordLocation temp_location;
  if (direction == CheckDirection::kHorizontal) {
    temp_location = FindWordkHorizontal(word);
  }
  if (direction == CheckDirection::kVertical) {
    temp_location = FindWordkVertical(word);
  }
  if (direction == CheckDirection::kLeftDiag) {
    temp_location = FindWordkLeftDiag(word);
  }
  if (direction == CheckDirection::kRightDiag) {
    temp_location = FindWordkRightDiag(word);
  }
  return temp_location;
}

// helper functions
std::string WordSearchSolver::ReverseStr(std::string& str) {
  std::string new_str;
  int length = str.length();
  for (int i = length-1; i>=0; i--) {
    new_str += str.at(i);
  }
  return new_str;
}
WordLocation WordSearchSolver::FindWordkHorizontal(const std::string& word){
  WordLocation temp_location;
  for (size_t row = 0; row < puzzle_height_; row++) { // new temp string for every row
    std::string temp_string;
    std::vector<CharPositions> char_vector; // 2 properties
    for (size_t col = 0; col < puzzle_width_; col++) { // to population the string with chars in each col
      temp_string += puzzle_.at(row).at(col);
    }
    // std::string reversed_temp_string = ReverseStr(temp_string);
    if (!(temp_location.char_positions.empty())) {break;}
    for (unsigned long i=0; i < temp_string.length() - (word.length()-1); i++) { // iterating through the string
      CharPositions temp_char {}; //3 properties
      if (!(temp_location.char_positions.empty())) {break;}
      if (temp_string.substr(i, word.length()) == word) { // if temp string = word
        for (unsigned long j=0; j<word.length(); j++) {
          temp_char.character = word.at(j);
          temp_char.row = row;
          temp_char.col = i+j;
          char_vector.push_back(temp_char);
        }
        temp_location.char_positions = char_vector;
        temp_location.word = word;
        break;
      }
      /* if (reversed_temp_string.substr(i, word.length()) == word) {
        for (unsigned long j=0; j<word.length(); j++) {
          temp_char.character = word.at(j);
          temp_char.row = row;
          temp_char.col = reversed_temp_string.length()-(word.length()+j);
          char_vector.push_back(temp_char);
        }
        temp_location.char_positions = char_vector;
        temp_location.word = word;
        break; 
      } created so that reverse could work too*/
    }
  }
  return temp_location;
}
WordLocation WordSearchSolver::FindWordkVertical(const std::string& word){
  WordLocation temp_location;
  for (size_t col = 0; col < puzzle_width_; col++) {
    std::string temp_string;
    std::vector<CharPositions> char_vector; // 2 properties
    for (size_t row = 0; row < puzzle_height_; row++) { 
    temp_string += puzzle_.at(row).at(col);
    }
    if (!(temp_location.char_positions.empty())) {break;}
    for (unsigned long i=0; i < temp_string.length() - (word.length()-1); i++) { // iterating through the string
      CharPositions temp_char {}; //3 properties
      if (!(temp_location.char_positions.empty())) {break;}
      if (temp_string.substr(i, word.length()) == word) { // if temp string = word
        for (unsigned long j=0; j<word.length(); j++) {
          temp_char.character = word.at(j);
          temp_char.row = i+j;
          temp_char.col = col;
          char_vector.push_back(temp_char);
        }
        temp_location.char_positions = char_vector;
        temp_location.word = word;
        break;
      }
    }
  }
  return temp_location;
}
WordLocation WordSearchSolver::FindWordkRightDiag(const std::string& word){
  WordLocation temp_location;
  std::string temp_string;
  for (size_t row = 0; row <= puzzle_height_-word.length(); row++) {
    for (size_t col = 0; col <= puzzle_width_-word.length(); col++) {
      temp_string = "";
      std::vector<CharPositions> char_vector; // 2 properties
      for (unsigned int i = 0; i < word.length(); i++) {
        if (puzzle_.at(row+i).at(col+i)==word.at(i)) {
          CharPositions temp_char = {};
          temp_char.character = word.at(i);
          temp_char.row = (size_t)row+i;
          temp_char.col = (size_t)col+i;
          temp_string += word.at(i);
          char_vector.push_back(temp_char);
        }
      }
      if (temp_string == word) {
        temp_location.word = word;
        temp_location.char_positions = char_vector;
        break;
      }
    }
  }
  if (temp_location.word != word) {
    temp_location = WordLocation{};
  }
  return temp_location;
}
WordLocation WordSearchSolver::FindWordkLeftDiag(const std::string& word){
  WordLocation temp_location;
  std::string temp_string;
  for (size_t row = 0; row < puzzle_height_; row++) {
    for (size_t col = 0; col < puzzle_width_; col++) {
      temp_string = "";
      std::vector<CharPositions> char_vector; // 2 properties
      for (unsigned long i = 0; i < word.length(); i++) {
        if (LocationInBounds(row+i, col-i)) {
          if (puzzle_.at(row+i).at(col-i)==word.at(i)) {
            CharPositions temp_char = {};
            temp_char.character = word.at(i);
            temp_char.row = row+i;
            temp_char.col = col-i;
            temp_string += word.at(i);
            char_vector.push_back(temp_char);
          }
        }
      }
      if (temp_string == word) {
        temp_location.word = word;
        temp_location.char_positions = char_vector;
        break;
      }
    }
  }
  if (temp_location.word != word) {
    temp_location = WordLocation{};
  }
  return temp_location;
}

