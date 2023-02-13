#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::DNAstrand(const char* kArray, int size) {
  for (int i = 0; i < size; i++) {
    PushBack(kArray[i]);
  }
}
DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* temp = head_->next;
    delete head_;
    head_ = temp;
  }
  head_ = tail_ = nullptr;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (&to_splice_in == this || FindLengthPattern(pattern) == 0 ||
      head_ == nullptr) {
    return;
  }
  int length_dna = FindLengthDNA();
  char* array_dna = new char[length_dna];  // array_dna holds the pre-existing
                                           // array of chars that we're splicing
  FillInArray(array_dna);
  int length_pattern = FindLengthPattern(pattern);
  int position = FindPosition(
      array_dna,
      length_dna,
      pattern,
      length_pattern);  // find what position to stop at during the linked list
  Replace(position, length_pattern, to_splice_in);
  DeallocateArray(array_dna, length_dna);
  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}

int DNAstrand::FindLengthDNA() {
  int length_dna = 0;
  Node* temp = head_;
  while (temp != nullptr) {
    length_dna++;
    temp = temp->next;
  }
  return length_dna;
}
int DNAstrand::FindLengthPattern(const char* pattern) {
  int length = 0;
  while (pattern[length] != '\0') {
    length++;
  }
  return length;
}
void DNAstrand::FillInArray(char* array_dna) {
  int x = 0;  // temp count variable
  Node* temp = head_;
  while (temp != nullptr) {
    array_dna[x] = (temp->data);
    temp = temp->next;
    x++;
  }
}
void DNAstrand::Replace(int position,
                        int length_pattern,
                        DNAstrand& to_splice_in) {
  Node* curr = head_;
  for (int x = 0; x < position - 1; x++) {
    curr = curr->next;  // temp_address_before is now where we need to splice
  }
  Node* temp_address_after =
      curr;               // this will store the last part of the list before
  Node* iterator = curr;  // iterator deletes
  for (int i = 0; i < length_pattern; i++) {
    if (iterator->next ==
        tail_) {  // this means that we're adding to the end of the linked list
      tail_ = to_splice_in.tail_;
    }
    if (position == 0) {
      head_ = to_splice_in.head_;
      temp_address_after = iterator->next;
      delete iterator;
      iterator = temp_address_after;
    } else {
      if (i == 0) {
        iterator = iterator->next;
      }
      temp_address_after = iterator->next;  // 2nd part of the linked list is whatever is next
      delete iterator;
      iterator = temp_address_after;
    }
  }
  curr->next = to_splice_in.head_;
  for (int i = 0; i < to_splice_in.FindLengthDNA(); i++) {
    curr = curr->next;
  }
  curr->next = temp_address_after;
  temp_address_after = nullptr;
  iterator = nullptr;
}

bool DNAstrand::Empty() const { return (head_ == nullptr); };
void DNAstrand::PushBack(char val) {
  Node* tmp = new Node(val);
  if (head_ == nullptr) {
    head_ = tail_ = tmp;
  } else {
    tail_->next = tmp;
    tail_ = tmp;
  }
}

void DNAstrand::Iterate() {
  Node* temp = head_;
  while (temp != nullptr) {
    temp = temp->next;
  }
}

unsigned int StrLen(const char* c_str) {
  int to_return = 0;
  while (*c_str != '\0') {
    to_return++;
    c_str++;
  }
  return to_return;
}
int FindPosition(const char* array_dna,
                 int length_dna,
                 const char* pattern,
                 int length_pattern) {
  int position = -1;
  for (int i = 0; i <= length_dna - length_pattern;
       i++) {  // iterating through char array of dna strand
    int count = 0;
    for (int x = 0; x < length_pattern;
         x++) {  // seeing if char array [i+..] = the pattern
      if (array_dna[i + x] != pattern[x]) {
        break;
      }
      count++;
      if (count == length_pattern) {
        position = i;
      }
    }
  }
  if (position == -1) {
    throw std::invalid_argument("Pattern does not exist");
  }
  return position;
}
void DeallocateArray(char* array_dna, int length_dna) {
  for (int i = 0; i < length_dna; i++) {
    array_dna[i] = '\0';
  }
  delete[] array_dna;
  array_dna = nullptr;
}
