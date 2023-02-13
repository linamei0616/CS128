#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  // EXAMPLE INTERACTIONS WITH BLL //
  // Pushback works
  // ToString works
  // Size works
  // Join works
  // tested constructor
  BLL* first = new BLL();
  first->PushBack('0');
  first->PushBack('1');
  first->PushBack('2');
  BLL* third = new BLL();
  third->PushBack('a');
  third->PushBack('b');
  third->PushBack('c');
  first->Join(0, third);
  BLL* second = new BLL();
  second->PushBack('z');
  first->Join(0, second);
  second->Join(0, third);
  std::cout << "first " << first->ToString() << std::endl;  // 12a9
  std::cout << "first " << first->ToString() << std::endl;  // 12a9
  return 0;
}
