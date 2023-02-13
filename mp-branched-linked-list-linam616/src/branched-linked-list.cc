#include "branched-linked-list.hpp"

#include <stdexcept>
#include <string>
BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
    return;
  }
  Node* to_copy_curr = to_copy.head_;
  Node* curr = head_;
  while (to_copy_curr != nullptr) {
    Node* to_add = PushBack(to_copy_curr->data_);
    if (curr == nullptr) {
      head_ = to_add;
    }
    curr = to_add;
    if (to_copy_curr->next_bll_ != nullptr) {
      curr->next_bll_ = new BLL(*(to_copy_curr->next_bll_));
    }
    to_copy_curr = to_copy_curr->next_node_;
  }
}
BLL::~BLL() {
  if (head_ == nullptr) {
    return;
  }
  while (head_ != nullptr) {
    if (head_->next_bll_ != nullptr) {
      head_->next_bll_->~BLL();
      delete head_->next_bll_;
    }
    Node* temp = head_->next_node_;
    delete head_;
    head_ = temp;
  }
  head_ = nullptr;
}
BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  if (rhs.head_ == nullptr) {
    head_ = nullptr;
    return *this;
  }
  // have to clear preexisting data
  while (head_ != nullptr) {
    if (head_->next_bll_ != nullptr) {
      head_->next_bll_->~BLL();
      delete head_->next_bll_;
    }
    Node* temp = head_->next_node_;
    delete head_;
    head_ = temp;
  }
  head_ = nullptr;
  // copy data
  Node* rhs_curr = rhs.head_;
  Node* curr = head_;
  while (rhs_curr != nullptr) {
    Node* to_add = PushBack(rhs_curr->data_);
    if (curr == nullptr) {
      head_ = to_add;
    }
    curr = to_add;
    if (rhs_curr->next_bll_ != nullptr) {
      curr->next_bll_ = new BLL(*(rhs_curr->next_bll_));
    }
    rhs_curr = rhs_curr->next_node_;
  }
  return *this;
}
Node* BLL::PushBack(char dat) {
  auto* tmp = new Node(dat);
  if (head_ == nullptr) {
    head_ = tmp;
    return tmp;
  }
  Node* curr = head_;
  while (curr->next_node_ != nullptr) {
    curr = curr->next_node_;
  }
  curr->next_node_ = tmp;
  return tmp;
}
char BLL::GetAt(size_t idx) const {
  if (idx >= Size()) {
    throw std::invalid_argument("idx is greater than size");
  }
  size_t count = 0;
  Node* curr = head_;
  while (curr != nullptr) {
    if (idx == count) {
      return curr->data_;
    }
    if (curr->next_bll_ != nullptr) {
      if (idx <= (count + curr->next_bll_->Size())) {  // then go into the BLL
        curr = curr->next_bll_->head_;
        count++;
      }
    } else {
      count++;
      curr = curr->next_node_;
    }
  }
  return curr->data_;
}
void BLL::SetAt(size_t idx, char dat) {
  if (idx >= Size()) {
    throw std::invalid_argument("idx is greater than size");
  }
  size_t count = 0;
  Node* curr = head_;
  while (curr != nullptr) {
    if (idx == count) {
      curr->data_ = dat;
    }
    if (curr->next_bll_ != nullptr) {
      if (idx <= (count + curr->next_bll_->Size())) {  // then go into the BLL
        curr = curr->next_bll_->head_;
        count++;
      }
    } else {
      count++;
      curr = curr->next_node_;
    }
  }
}

void BLL::Join(size_t idx, BLL* list) {
  if (idx >= Size() || idx < 0) {
    throw std::invalid_argument("idx is out of bounds!");
  }
  if (idx == 0) {
    if (head_->next_bll_ != nullptr) {
      throw std::invalid_argument("already BLL");
    }
    head_->next_bll_ = list;
    return;
  }
  size_t count = 0;
  Node* curr = head_;
  while (curr != nullptr) {
    if (idx == count) {
      if (curr->next_bll_ != nullptr) {
        throw std::invalid_argument("already BLL");
      }
      curr->next_bll_ = list;
      break;
    }
    if (curr->next_bll_ != nullptr) {
      if (idx <= (count + curr->next_bll_->Size())) {  // then go into the BLL
        curr = curr->next_bll_->head_;
        count++;
      }
    } else {
      count++;
      curr = curr->next_node_;
    }
  }
  if (!(IsBLLAcyclic())) {
    curr->next_bll_ = nullptr;
    throw std::invalid_argument("BLL is cyclic!");
  }
}
std::string BLL::ToString() const { return ToStringHelper(head_); }
std::string BLL::ToStringHelper(Node* node) const {
  std::string str;
  if (node == nullptr) {
    return "";
  }
  Node* curr = node;
  while (curr != nullptr) {
    str += curr->data_;
    if (curr->next_bll_ != nullptr) {
      str += ToStringHelper(curr->next_bll_->head_);
    }
    curr = curr->next_node_;
  }
  return str;
}
size_t BLL::Size() const { return SizeHelper(head_); }
size_t BLL::SizeHelper(Node* node) const {
  size_t count = 0;
  if (node == nullptr) {
    return 0;
  }
  Node* curr = node;
  while (curr != nullptr) {
    if (curr->next_bll_ != nullptr) {
      count += SizeHelper(curr->next_bll_->head_);
    }
    count++;
    curr = curr->next_node_;
  }
  return count;
}
bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) {
    return true;
  }
  Node* tort = head_;
  Node* hare = NextNode(head_);
  while (tort != nullptr && hare != nullptr) {
    if (tort == hare) {
      return false;
    }
    tort = NextNode(tort);
    hare = NextNode(hare);
    hare = NextNode(hare);
  }
  return true;
}

Node* BLL::NextNode(Node* node) const {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->next_bll_ != nullptr) {
    return node->next_bll_->head_;
  }
  return node->next_node_;
}