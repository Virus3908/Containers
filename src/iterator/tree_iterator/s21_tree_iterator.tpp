#include "s21_tree_iterator.h"
namespace s21 {

template <typename T>
TreeIterator<T>::TreeIterator() : cur_pos_(nullptr) {}

template <typename T>
TreeIterator<T>::TreeIterator(Node *node, Node *nil)
    : cur_pos_(node), nil_(nil) {}

template <typename T>
TreeIterator<T>::TreeIterator(const TreeIterator &other)
    : cur_pos_(other.cur_pos_), nil_(other.nil_) {}

template <typename T>
TreeIterator<T> &TreeIterator<T>::operator=(const TreeIterator &other) {
  cur_pos_ = other.cur_pos_;
  nil_ = other.nil_;
  return *this;
}

template <typename T>
typename TreeIterator<T>::reference TreeIterator<T>::operator*() {
  reference res = cur_pos_->val_;
  return res;
}

template <typename T>
typename TreeIterator<T>::value_type *TreeIterator<T>::operator->() {
  return &(cur_pos_->val_);
}

template <typename T>
TreeIterator<T> &TreeIterator<T>::operator++() {
  if (cur_pos_) {
    if (cur_pos_->right_ != nil_) {
      cur_pos_ = GetMin(cur_pos_->right_);
    } else {
      Node *par = cur_pos_->parent_;
      while (par != nil_ && par->right_ == cur_pos_) {
        cur_pos_ = par;
        par = cur_pos_->parent_;
      }
      cur_pos_ = par;
    }
  }
  return *this;
}

template <typename T>
TreeIterator<T> &TreeIterator<T>::operator--() {
  if (cur_pos_) {
    if (cur_pos_->left_ != nil_) {
      cur_pos_ = GetMax(cur_pos_->left_);
    } else {
      Node *par = cur_pos_->parent_;
      while (par != nil_ && par->left_ == cur_pos_ && cur_pos_ != nil_) {
        cur_pos_ = par;
        par = cur_pos_->parent_;
      }
      cur_pos_ = par;
    }
  }
  return *this;
}

template <typename T>
TreeIterator<T> TreeIterator<T>::operator++(int) {
  TreeIterator tmp(*this);
  ++(*this);
  return tmp;
}

template <typename T>
TreeIterator<T> TreeIterator<T>::operator--(int) {
  TreeIterator tmp(*this);
  --(*this);
  return tmp;
}

template <typename T>
bool TreeIterator<T>::operator==(const TreeIterator &other) const {
  return cur_pos_ == other.cur_pos_;
}

template <typename T>
bool TreeIterator<T>::operator!=(const TreeIterator &other) const {
  return cur_pos_ != other.cur_pos_;
}

template <typename T>
typename TreeIterator<T>::Node *TreeIterator<T>::GetMin(Node *node) {
  while (node && node->left_ != nil_) {
    node = node->left_;
  }
  return node;
}

template <typename T>
typename TreeIterator<T>::Node *TreeIterator<T>::GetMax(Node *node) {
  if (node && node->right_ != nil_) {
    node = node->right_;
  }
  return node;
}

template <typename T>
typename TreeIterator<T>::Node *TreeIterator<T>::GetNode() {
  return cur_pos_;
}

// CONST ITERATOR
// BEGINS HERE

template <typename T>
ConstTreeIterator<T>::ConstTreeIterator() : TreeIterator<T>() {}

template <typename T>
ConstTreeIterator<T>::ConstTreeIterator(Node *node, Node *nil)
    : TreeIterator<T>(node, nil) {}

template <typename T>
ConstTreeIterator<T>::ConstTreeIterator(const ConstTreeIterator &other)
    : TreeIterator<T>(other) {}

template <typename T>
ConstTreeIterator<T>::ConstTreeIterator(const TreeIterator<T> &other)
    : TreeIterator<T>(other) {}

template <typename T>
ConstTreeIterator<T> &ConstTreeIterator<T>::operator=(
    const ConstTreeIterator &other) {
  this->cur_pos_ = other.cur_pos_;
  this->nil_ = other.nil_;
  return *this;
}

template <typename T>
typename ConstTreeIterator<T>::const_reference
ConstTreeIterator<T>::operator*() {
  return this->cur_pos_->val_;
}

}  // namespace s21