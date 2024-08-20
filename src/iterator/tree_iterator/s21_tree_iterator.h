#ifndef S21_TREE_ITERATOR_H
#define S21_TREE_ITERATOR_H

#include "../../Node/s21_node.h"

namespace s21 {

template <typename T>
class TreeIterator {
 public:
  using value_type = T;
  using reference = value_type &;
  using Node = Node_tree<T>;

  TreeIterator();
  TreeIterator(Node *node, Node *nil);
  TreeIterator(const TreeIterator &other);
  ~TreeIterator() = default;

  TreeIterator &operator=(const TreeIterator &other);
  reference operator*();
  TreeIterator &operator++();
  TreeIterator &operator--();
  TreeIterator operator++(int);
  TreeIterator operator--(int);
  value_type *operator->();
  bool operator==(const TreeIterator &other) const;
  bool operator!=(const TreeIterator &other) const;

  Node *GetNode();
  //   void begin();
  //   void end();

 protected:
  Node *GetMin(Node *node);
  Node *GetMax(Node *node);

  Node *cur_pos_;
  Node *nil_;
};

template <typename T>
class ConstTreeIterator : public TreeIterator<T> {
 public:
  using value_type = T;
  using const_reference = const value_type &;
  using Node = Node_tree<T>;

  ConstTreeIterator();
  ConstTreeIterator(Node *node, Node *nil);
  ConstTreeIterator(const TreeIterator<T> &other);
  ConstTreeIterator(const ConstTreeIterator &other);
  ~ConstTreeIterator() = default;

  ConstTreeIterator &operator=(const ConstTreeIterator &other);
  const_reference operator*();
};

}  // namespace s21

#include "s21_tree_iterator.tpp"

#endif