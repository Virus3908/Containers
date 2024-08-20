#ifndef S21_LIST_ITERATOR_H
#define S21_LIST_ITERATOR_H

#include "../../Node/s21_node.h"

namespace s21 {

template <typename T>
class ListConstIterator {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Node = Node_t<T>;

  ListConstIterator();
  ListConstIterator(Node *pos);
  ListConstIterator(const ListConstIterator &other);

  ListConstIterator &operator++();
  ListConstIterator &operator--();
  ListConstIterator operator++(int);
  ListConstIterator operator--(int);
  ListConstIterator &operator=(const ListConstIterator &other);
  bool operator==(const ListConstIterator &other);
  bool operator!=(const ListConstIterator &other);

  const_reference operator*();
  value_type *operator->();

  Node *GetNode();

 protected:
  Node *curr_pos;
};

template <typename T>
class ListIterator : public ListConstIterator<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Node = Node_t<T>;

  ListIterator();
  ListIterator(Node *pos);
  ListIterator(ListIterator &other);
  ListIterator(ListConstIterator<T> &other);

  ListIterator &operator=(const ListIterator &other);
  reference operator*();
};

};  // namespace s21

#include "s21_list_iterator.tpp"

#endif