#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();
  void PushBack(T val);
  void InsertASC(const T& data);
  void InsertDESC(const T& data);

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  node_order_ = source.node_order_;
  // if list is empty
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
    return;
  }
  // if there is only 1 node
  if (source.head_->next == source.tail_->next) {
    PushBack(source.head_->data);
    head_->next = tail_;
    tail_->next = head_;
    std::cout << "This is head_ next: " << head_->next->data << std::endl;
    std::cout << "This is tail_ next: " << tail_->next->data << std::endl;
    return;
  }
  // if there is more than 1 node
  Node<T>* curr = source.head_;
  while (curr->next != source.head_) {
    PushBack(curr->data);
    curr = curr->next;
  }
  PushBack(curr->data);
}
template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (this == &source) {
    return *this;
  }
  // remove existing
  node_order_ = source.node_order_;
  while (head_ != tail_) {
    Node<T>* save = head_->next;
    delete head_;
    head_ = save;
  }
  delete head_;
  head_ = tail_ = nullptr;

  // finished removing
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
    return *this;
  }
  if (source.head_->next == source.tail_->next) {
    PushBack(source.head_->data);
    head_->next = tail_;
    tail_->next = head_;
    return *this;
  }

  Node<T>* curr = source.head_;
  while (curr->next != source.head_) {
    PushBack(curr->data);
    curr = curr->next;
  }
  PushBack(curr->data);
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  while (head_ != tail_) {
    Node<T>* save = head_->next;
    delete head_;
    head_ = save;
  }
  delete head_;
  head_ = tail_ = nullptr;
}
template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (node_order_ == Order::kASC) {
    InsertASC(data);
    return;
  }  // or else
  InsertDESC(data);
}
template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
  if (head_ == nullptr ||
      head_ == tail_) {  // if list is empty or if its only 1 node
    return;
  }
  Node<T>* prev = tail_;
  Node<T>* curr = head_;
  Node<T>* next = head_->next;
  while (curr->next != head_) {
    curr->next = prev;
    prev = curr;
    curr = next;
    next = curr->next;
  }
  // Node<T>* save = tail_;
  curr->next = prev;
  head_ = curr;
  tail_ = next;
  std::cout << "This is head_ next: " << head_->next->data << std::endl;
  std::cout << "This is tail_ next: " << tail_->next->data << std::endl;
}

// Helper functions
template <typename T>
void CircularLinkedList<T>::PushBack(T val) {
  auto tmp = new Node<T>(val);
  if (head_ == nullptr) {
    head_ = tail_ = tmp;
  } else {
    tail_->next = tmp;
    tail_ = tmp;
  }
  tail_->next = head_;
}

template <typename T>
void CircularLinkedList<T>::InsertASC(const T& data) {
  auto to_add = new Node<T>(data);
  if (head_ == nullptr) {  // when the list is empty
    head_ = tail_ = to_add;
    head_->next = tail_;
    tail_->next = head_;
    return;
  }
  Node<T>* curr = head_;
  if (data <= curr->data) {  // adding in the beginning
    to_add->next = head_;
    head_ = to_add;
    tail_->next = head_;
    return;
  }
  // traversing normally
  while (curr->next != head_) {
    if (data <= curr->next->data) {  // else adding to the middle of the list
      Node<T>* save = curr->next;
      curr->next = to_add;
      curr = curr->next;
      curr->next = save;
      return;
    }
    curr = curr->next;
  }
  if (curr->next == head_) {  // adding to the end
    tail_->next = to_add;
    tail_ = to_add;
    tail_->next = head_;
    return;
  }
}
template <typename T>
void CircularLinkedList<T>::InsertDESC(const T& data) {
  auto to_add = new Node<T>(data);
  if (head_ == nullptr) {  // when the list is empty
    head_ = tail_ = to_add;
    head_->next = tail_;
    tail_->next = head_;
    return;
  }
  Node<T>* curr = head_;
  if (data >= curr->data) {  // adding in the beginning
    to_add->next = head_;
    head_ = to_add;
    tail_->next = head_;
    return;
  }
  // traversing normally
  while (curr->next != head_) {
    if (data >= curr->next->data) {  // else adding to the middle of the list
      Node<T>* save = curr->next;
      curr->next = to_add;
      curr = curr->next;
      curr->next = save;
      return;
    }
    curr = curr->next;
  }
  if (curr->next == head_) {  // adding to the end
    tail_->next = to_add;
    tail_ = to_add;
    tail_->next = head_;
    return;
  }
}

#endif