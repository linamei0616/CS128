#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include <catch/catch.hpp>
#include <string>
#include <vector>

#include "functions.hpp"

TEST_CASE("CountDna", "[case-1]") {

  const std::vector<int> &alvin = {3, 3, 2};
  const std::vector<int> &casey = {5, 4, 2};
  std::vector<std::vector<std::string>> vect = {
    {"Names", "A", "B", "C"},
    {"Casey", "5", "4", "2"},
    {"Alvin", "3", "3", "2"}
  };
  REQUIRE(CountDna("AAAAABBBBCC", vect) == casey );
  REQUIRE(CountDna("ABABABAAABBBCCABC", vect) == alvin );
  std::vector<int> counts =  CountDna("ABABABAAABBBCCABC", vect);
  for(unsigned int loop = 0 ; loop < vect.size() ; loop++) {
    REQUIRE(Match(counts, vect.at(1)));
  }
}
