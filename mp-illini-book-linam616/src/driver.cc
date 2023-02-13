#include <iostream>

#include "illini_book.hpp"

int main() {
  IlliniBook book(
      "/home/vagrant/src/mp-illini-book-linam616/example/persons.csv",
      "/home/vagrant/src/mp-illini-book-linam616/example/relations.csv");
  std::cout << book << std::endl;
  // testing getRelated first
  for (int i : book.GetSteps(1, 1)) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  for (int i : book.GetSteps(1, 2)) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  for (int i : book.GetSteps(1, 3)) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  for (int i : book.GetSteps(9, 1)) {
    std::cout << i << " ";
  }
}
