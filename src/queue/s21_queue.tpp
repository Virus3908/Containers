#include "s21_queue.h"

namespace s21 {

template <typename T>
queue<T>::queue() : top_(nullptr), bottom_(nullptr), size_(0U) {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items) : queue() {
  for (const auto &i : items) {
    push(i);
  }
}

template <typename T>
queue<T>::queue(const queue &other_queue) : queue() {
  *this = other_queue;
}

template <typename T>
queue<T>::queue(queue &&other_queue) : queue() {
  swap(other_queue);
}

template <typename T>
queue<T>::~queue() {
  clear();
}

template <typename T>
queue<T> &queue<T>::operator=(queue &&other_queue) {
  if (this != &other_queue) {
    clear();
    swap(other_queue);
  }
  return *this;
}

template <typename T>
queue<T> &queue<T>::operator=(const queue &other_queue) {
  if (this != &other_queue) {
    clear();
    for (Node *it = other_queue.bottom_; it != nullptr; it = it->prev) {
      push(it->val);
    }
  }
  return *this;
}

template <typename T>
bool queue<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
  if (empty()) {
    throw std::length_error("The queue is empty");
  }
  return bottom_->val;
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  if (empty()) {
    throw std::length_error("The queue is empty");
  }
  return top_->val;
}

template <typename T>
typename queue<T>::reference queue<T>::front() {
  return const_cast<reference>(static_cast<const queue &>(*this).front());
}

template <typename T>
typename queue<T>::reference queue<T>::back() {
  return const_cast<reference>(static_cast<const queue &>(*this).back());
}

template <typename T>
typename queue<T>::size_type queue<T>::size() const {
  return size_;
}

template <typename T>
void queue<T>::push(const_reference value) {
  Node *new_node = new Node{value};
  if (empty()) {
    bottom_ = new_node;
  } else {
    top_->prev = new_node;
  }
  top_ = new_node;
  ++size_;
}

template <typename T>
void queue<T>::pop() {
  if (empty()) {
    throw std::length_error("The queue is empty");
  } else {
    Node *temp = bottom_->prev;
    if (bottom_ == top_) {
      top_ = nullptr;
    }
    delete bottom_;
    bottom_ = temp;
  }
  --size_;
}

template <typename T>
void queue<T>::clear() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
void queue<T>::swap(queue &other) {
  if (this != &other) {
    std::swap(top_, other.top_);
    std::swap(bottom_, other.bottom_);
    std::swap(size_, other.size_);
  }
}

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  (push(std::forward<Args>(args)), ...);
}

}  // namespace s21