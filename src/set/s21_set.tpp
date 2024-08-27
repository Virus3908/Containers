#include "s21_set.h"

namespace s21 {

template <typename T, typename Compare>
set<T, Compare>::set() : tree_(new tree()) {}

template <typename T, typename Compare>
set<T, Compare>::set(std::initializer_list<value_type> const &items) : set() {
  for (auto it : items) {
    insert(it);
  }
}

template <typename T, typename Compare>
set<T, Compare>::set(const set &other) : tree_(new tree(*other.tree_)) {}

template <typename T, typename Compare>
set<T, Compare>::set(set &&other) : tree_(new tree(std::move(*other.tree_))) {}

template <typename T, typename Compare>
set<T, Compare>::~set() {
  delete tree_;
}

template <typename T, typename Compare>
set<T, Compare> set<T, Compare>::operator=(set &&other) {
  if (this != &other) {
    *tree_ = std::move(*other.tree_);
  }
  return *this;
}

template <typename T, typename Compare>
set<T, Compare> set<T, Compare>::operator=(const set &other) {
  if (this != &other) {
    *tree_ = *other.tree_;
  }
  return *this;
}

template <typename T, typename Compare>
typename set<T, Compare>::iterator set<T, Compare>::begin() {
  return tree_->begin();
}

template <typename T, typename Compare>
typename set<T, Compare>::iterator set<T, Compare>::end() {
  return tree_->end();
}

template <typename T, typename Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::begin() const {
  return static_cast<const RBTree<value_type> &>(*tree_).begin();
}

template <typename T, typename Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::end() const {
  return static_cast<const RBTree<value_type> &>(*tree_).end();
}

template <typename T, typename Compare>
bool set<T, Compare>::empty() const {
  return tree_->empty();
}

template <typename T, typename Compare>
typename set<T, Compare>::size_type set<T, Compare>::size() const {
  return tree_->size();
}

template <typename T, typename Compare>
typename set<T, Compare>::size_type set<T, Compare>::max_size() const {
  return tree_->max_size();
}

template <typename T, typename Compare>
void set<T, Compare>::clear() {
  tree_->clear();
}

template <typename T, typename Compare>
std::pair<typename set<T, Compare>::iterator, bool> set<T, Compare>::insert(
    const value_type &value) {
  return tree_->insertUnique(value);
}

template <typename T, typename Compare>
void set<T, Compare>::erase(iterator pos) {
  tree_->erase(pos);
}

template <typename T, typename Compare>
void set<T, Compare>::swap(set &other) {
  tree_->swap(*other.tree_);
}

template <typename T, typename Compare>
void set<T, Compare>::merge(set &other) {
  tree_->mergeUnique(*other.tree_);
}

template <typename T, typename Compare>
typename set<T, Compare>::iterator set<T, Compare>::find(
    const value_type &key) {
  return tree_->Find(key);
}

template <typename T, typename Compare>
bool set<T, Compare>::contains(const value_type &key) {
  return find(key) != end();
}

template <typename T, typename Compare>
template <typename... Args>
std::vector<std::pair<typename set<T, Compare>::iterator, bool>>
set<T, Compare>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> res;
  (res.push_back(this->insert(std::forward<Args>(args))), ...);
  return res;
}

}  // namespace s21