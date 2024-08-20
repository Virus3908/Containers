#include "s21_stack.h"

namespace s21 {

template <typename T>
stack<T>::stack() : top_(nullptr), size_(0U) {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items) : stack() {
  for (const auto &it : items) {
    push(it);
  }
}

template <typename T>
stack<T>::stack(const stack &other) : stack() {
  *this = other;
}

template <typename T>
stack<T>::stack(stack &&other) : stack() {
  *this = std::move(other);
}

template <typename T>
stack<T>::~stack() {
  clear();
}

template <typename T>
stack<T> &stack<T>::operator=(stack &&other) {
  if (this != &other) {
    swap(other);
  }
  return *this;
}

template <typename T>
stack<T> &stack<T>::operator=(const stack &other) {
  if (this != &other) {
    clear();
    copy(other);
  }
  return *this;
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
  if (empty()) {
    throw std::length_error("The stack is empty");
  }
  return top_->val;
}

template <typename T>
typename stack<T>::reference stack<T>::top() {
  return const_cast<reference>(static_cast<const stack &>(*this).top());
}

template <typename T>
typename stack<T>::size_type stack<T>::size() const {
  return size_;
}

template <typename T>
bool stack<T>::empty() const {
  return size_ == 0;
}

template <typename T>
void stack<T>::push(const_reference value) {
  Node *new_node = new Node(value, top_);
  top_ = new_node;
  ++size_;
}

template <typename T>
void stack<T>::pop() {
  if (empty()) {
    throw std::length_error("The stack is empty");
  }
  Node *temp = top_;
  top_ = top_->prev;
  delete temp;
  --size_;
}

template <typename T>
void stack<T>::clear() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
void stack<T>::swap(stack &other) {
  if (this != &other) {
    std::swap(top_, other.top_);
    std::swap(size_, other.size_);
  }
}

template <typename T>
void stack<T>::copy(const stack &other) {
  Node *other_node = other.top_;
  stack temp_stack;
  while (other_node) {
    temp_stack.push(other_node->val);
    other_node = other_node->prev;
  }
  while (!temp_stack.empty()) {
    push(temp_stack.top());
    temp_stack.pop();
  }
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    push(arg);
  }
}

}  // namespace s21