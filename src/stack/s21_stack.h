#ifndef S21_STACK_H
#define S21_STACK_H

#include "../Node/s21_node.h"

namespace s21 {

template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Node = Node_t<T>;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &other);
  stack(stack &&other);
  ~stack();

  stack<T> &operator=(stack &&other);
  stack<T> &operator=(const stack &other);

  reference top();
  const_reference top() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <class... Args>
  void insert_many_front(Args &&...args);

 private:
  Node *top_;
  size_type size_;

  void clear();
  void copy(const stack &other);
};
}  // namespace s21

#include "s21_stack.tpp"

#endif