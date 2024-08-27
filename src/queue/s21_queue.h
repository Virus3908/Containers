#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../Node/s21_node.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Node = Node_t<T>;

  queue();                                                // done
  queue(std::initializer_list<value_type> const &items);  // done
  queue(const queue &other_queue);                        // done
  queue(queue &&other_queue);                             // done
  ~queue();                                               // done

  queue<T> &operator=(queue &&other_queue);       // done
  queue<T> &operator=(const queue &other_queue);  // done

  reference front();
  reference back();
  const_reference front() const;
  const_reference back() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Node *top_;
  Node *bottom_;
  size_type size_ = 0U;

  void clear();
};

};  // namespace s21

#include "s21_queue.tpp"

#endif