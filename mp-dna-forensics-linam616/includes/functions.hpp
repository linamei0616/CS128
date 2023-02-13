#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
#include <vector>
#include <string>
#include <cctype>

std::string Single(const std::string &data, const std::string &dna_input);
std::vector<std::vector<std::string>> RetrieveData(const std::string &data);
std::vector<int> CountDna(const std::string &data, const std::vector<std::vector<std::string>> &word);
bool Match(const std::vector<int> &dna_vect, const std::vector<std::string> &info_vect);
#endif