#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>

// Your function declarations should go in this header file.
bool InvalidHawaiianWord(std::vector<char> vec);
std::vector<char> ConvertingToVector(std::string word);
bool CheckVConsonant(std::vector<char> vec);
std::string CheckConsonants(char c);
std::string CheckVowelGroups(std::vector<char> vec);
std::string CheckVowel(char c);
std::string CheckSpecialCharacters(char c);
std::string AddingDash(std::vector<char> vec);
std::vector<char> RemovingElements(std::vector<char> vec);
bool Consonants(char c);
bool WConsonants(std::vector<char> vec);
bool SpecialCharacters(char c);
bool VowelGroups(std::vector<char> vec);
bool Vowel(char c);

#endif