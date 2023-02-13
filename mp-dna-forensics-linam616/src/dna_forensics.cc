#include <iostream>

#include "functions.hpp"
#include "utilities.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <cctype>


int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
std::string data = argv[1];
std::string dna_input = argv[2]; 
std::string single = Single(data, dna_input);
std::cout << single << std::endl;
return 0;
}