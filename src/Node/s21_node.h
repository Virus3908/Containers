#ifndef S21_NODE_H
#define S21_NODE_H

#include <iostream>

namespace s21 {

enum colors { BLACK, RED };

template <typename T>
struct Node_t {
  T val;
  Node_t *prev = nullptr;
  Node_t *next = nullptr;
  Node_t(T val_, Node_t *prev_ = nullptr, Node_t *next_ = nullptr)
      : val(val_), prev(prev_), next(next_) {}
};

template <typename T>
struct Node_tree {
  Node_tree *parent_;
  Node_tree *left_;
  Node_tree *right_;
  char color_;
  T val_;
  Node_tree(T val = T(), Node_tree *par = nullptr, Node_tree *left = nullptr,
            Node_tree *right = nullptr, int color = BLACK)
      : parent_(par), left_(left), right_(right), color_(color), val_(val) {}
};

}  // namespace s21

#endif
