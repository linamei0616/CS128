#include <iostream>
#include <string>
#include <cctype>

#include "functions.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }
  std::string word = argv[1];
  std::string phonetics;
  std::vector<char> vec = ConvertingToVector(word); //convert into vector
  bool v_consonant = CheckVConsonant(vec);
  while (!vec.empty()) {
    if (InvalidHawaiianWord(vec)) {
      phonetics = word + " contains a character not a part of the Hawaiian language.";
      break;
    }
    while (!vec.empty()) {
      if (Consonants(vec[0])) {
        phonetics.append(CheckConsonants(vec[0]));
        break;
      }
      if (VowelGroups(vec)) {
        phonetics.append(CheckVowelGroups(vec));
        break;
      }
      if (Vowel(vec[0])) {
        phonetics.append(CheckVowel(vec[0]));
        break;
      }
      if (vec[0] == 'w' && v_consonant) {
        phonetics.append("v");
        break;
      }
      if (vec[0] == 'w' && !(v_consonant)) {
        phonetics.append("w");
        break;
      }
    }
    phonetics.append(AddingDash(vec));
    vec = RemovingElements(vec);
  }
  std::cout << phonetics << std::endl;
}