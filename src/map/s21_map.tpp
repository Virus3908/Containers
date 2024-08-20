#include "s21_map.h"

namespace s21 {

template <typename KEY, typename T>
map<KEY, T>::map() : tree_(new tree()) {}

template <typename KEY, typename T>
map<KEY, T>::map(std::initializer_list<value_type> const &items) : map() {
  for (auto it : items) {
    insert(it);
  }
}

template <typename KEY, typename T>
map<KEY, T>::map(const map &other) : tree_(new tree(*other.tree_)) {}

template <typename KEY, typename T>
map<KEY, T>::map(map &&other) : tree_(new tree(std::move(*other.tree_))) {}

template <typename KEY, typename T>
map<KEY, T>::~map() {
  delete tree_;
}

template <typename KEY, typename T>
map<KEY, T> map<KEY, T>::operator=(map &&other) {
  if (this != &other) {
    *tree_ = std::move(*other.tree_);
  }
  return *this;
}

template <typename KEY, typename T>
map<KEY, T> map<KEY, T>::operator=(const map &other) {
  if (this != &other) {
    *tree_ = *other.tree_;
  }
  return *this;
}

template <typename KEY, typename T>
typename map<KEY, T>::mapped_type &map<KEY, T>::at(const key_type &key) {
  value_type find_this_key(key, mapped_type());
  iterator it = tree_->Find(find_this_key);
  if (it == tree_->end()) {
    throw std::out_of_range("No element with this key");
  }
  return (*it).second;
}

template <typename KEY, typename T>
const typename map<KEY, T>::mapped_type &map<KEY, T>::at(
    const key_type &key) const {
  return const_cast<map<KEY, T>>(*this)->at(key);
}

template <typename KEY, typename T>
typename map<KEY, T>::mapped_type &map<KEY, T>::operator[](
    const key_type &key) {
  value_type find_this_key(key, mapped_type());
  std::pair<iterator, bool> res = tree_->insertUnique(find_this_key);
  return (*res.first).second;
}

template <typename KEY, typename T>
typename map<KEY, T>::iterator map<KEY, T>::begin() {
  return tree_->begin();
}

template <typename KEY, typename T>
typename map<KEY, T>::iterator map<KEY, T>::end() {
  return tree_->end();
}

template <typename KEY, typename T>
typename map<KEY, T>::const_iterator map<KEY, T>::begin() const {
  return static_cast<const RBTree<value_type, MapComparator<value_type>> &>(
             *tree_)
      .begin();
}

template <typename KEY, typename T>
typename map<KEY, T>::const_iterator map<KEY, T>::end() const {
  return static_cast<const RBTree<value_type, MapComparator<value_type>> &>(
             *tree_)
      .end();
}

template <typename KEY, typename T>
bool map<KEY, T>::empty() const {
  return tree_->empty();
}

template <typename KEY, typename T>
typename map<KEY, T>::size_type map<KEY, T>::size() const {
  return tree_->size();
}

template <typename KEY, typename T>
typename map<KEY, T>::size_type map<KEY, T>::max_size() const {
  return tree_->max_size();
}

template <typename KEY, typename T>
void map<KEY, T>::clear() {
  tree_->clear();
}

template <typename KEY, typename T>
std::pair<typename map<KEY, T>::iterator, bool> map<KEY, T>::insert(
    const value_type &value) {
  return tree_->insertUnique(value);
}

template <typename KEY, typename T>
std::pair<typename map<KEY, T>::iterator, bool> map<KEY, T>::insert(
    const key_type &key, const mapped_type &obj) {
  value_type val(key, obj);
  std::pair<iterator, bool> res = tree_->insertUnique(val);
  return res;
}

template <typename KEY, typename T>
std::pair<typename map<KEY, T>::iterator, bool> map<KEY, T>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  value_type val(key, obj);
  std::pair<iterator, bool> res = tree_->insertUnique(val);
  if (!res.second) {
    *res.first = val;
  }
  return res;
}

template <typename KEY, typename T>
void map<KEY, T>::erase(iterator pos) {
  tree_->erase(pos);
}

template <typename KEY, typename T>
void map<KEY, T>::swap(map &other) {
  tree_->swap(*other.tree_);
}

template <typename KEY, typename T>
void map<KEY, T>::merge(map &other) {
  tree_->mergeUnique(*other.tree_);
}

template <typename KEY, typename T>
bool map<KEY, T>::contains(const key_type &key) {
  value_type find_this_key(key, mapped_type());
  return !(tree_->Find(find_this_key) == end());
}

template <typename KEY, typename T>
template <typename... Args>
std::vector<std::pair<typename map<KEY, T>::iterator, bool>>
map<KEY, T>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> res;
  for (auto &arg : {args...}) {
    res.push_back(insert(arg));
  }
  return res;
}

}  // namespace s21