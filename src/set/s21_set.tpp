#include "s21_set.h"

namespace s21 {

template <typename T>
set<T>::set() : tree_(new tree()) {}

template <typename T>
set<T>::set(std::initializer_list<value_type> const &items) : set() {
  for (auto it : items) {
    insert(it);
  }
}

template <typename T>
set<T>::set(const set &other) : tree_(new tree(*other.tree_)) {}

template <typename T>
set<T>::set(set &&other) : tree_(new tree(std::move(*other.tree_))) {}

template <typename T>
set<T>::~set() {
  delete tree_;
}

template <typename T>
set<T> set<T>::operator=(set &&other) {
  if (this != &other) {
    *tree_ = std::move(*other.tree_);
  }
  return *this;
}

template <typename T>
set<T> set<T>::operator=(const set &other) {
  if (this != &other) {
    *tree_ = *other.tree_;
  }
  return *this;
}

template <typename T>
typename set<T>::iterator set<T>::begin() {
  return tree_->begin();
}

template <typename T>
typename set<T>::iterator set<T>::end() {
  return tree_->end();
}

template <typename T>
typename set<T>::const_iterator set<T>::begin() const {
  return static_cast<const RBTree<value_type> &>(*tree_).begin();
}

template <typename T>
typename set<T>::const_iterator set<T>::end() const {
  return static_cast<const RBTree<value_type> &>(*tree_).end();
}

template <typename T>
bool set<T>::empty() const {
  return tree_->empty();
}

template <typename T>
typename set<T>::size_type set<T>::size() const {
  return tree_->size();
}

template <typename T>
typename set<T>::size_type set<T>::max_size() const {
  return tree_->max_size();
}

template <typename T>
void set<T>::clear() {
  tree_->clear();
}

template <typename T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(
    const value_type &value) {
  return tree_->insertUnique(value);
}

template <typename T>
void set<T>::erase(iterator pos) {
  tree_->erase(pos);
}

template <typename T>
void set<T>::swap(set &other) {
  tree_->swap(*other.tree_);
}

template <typename T>
void set<T>::merge(set &other) {
  tree_->mergeUnique(*other.tree_);
}

template <typename T>
typename set<T>::iterator set<T>::find(const value_type &key) {
  return tree_->Find(key);
}

template <typename T>
bool set<T>::contains(const value_type &key) {
  return find(key) != end();
}

template <typename T>
template <typename... Args>
std::vector<std::pair<typename set<T>::iterator, bool>> set<T>::insert_many(
    Args &&...args) {
  std::vector<std::pair<typename set<T>::iterator, bool>> res;
  for (auto &arg : {args...}) {
    res.push_back(insert(arg));
  }
  return res;
}

}  // namespace s21