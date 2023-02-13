#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
    std::vector<std::vector<char>> puzzle{ {'d', 'e', 'a', 'o', 'u'},
                                           {'h', 'e', 'l', 'l', 'o'},
                                           {'c', 'a', 'l', 'o', 'y'},
                                           {'a', 'e', 't', 'a', 'p'},
                                           {'t', 'e', 't', 'a', 'u'},
                                           {'a', 'e', 't', 'a', 't'}};                                    
  WordSearchSolver wss(puzzle);
  std::cout << wss.FindWord("hat");
  std::cout << wss.FindWord("pat");
  std::cout << wss.FindWord("ehc");

}