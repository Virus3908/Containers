#include "s21_map.h"

namespace s21 {

template <typename KEY, typename T, typename Compare>
map<KEY, T, Compare>::map() : tree_(new tree()) {}

template <typename KEY, typename T, typename Compare>
map<KEY, T, Compare>::map(std::initializer_list<value_type> const &items) : map() {
  for (auto it : items) {
    insert(it);
  }
}

template <typename KEY, typename T, typename Compare>
map<KEY, T, Compare>::map(const map &other) : tree_(new tree(*other.tree_)) {}

template <typename KEY, typename T, typename Compare>
map<KEY, T, Compare>::map(map &&other) : tree_(new tree(std::move(*other.tree_))) {}

template <typename KEY, typename T, typename Compare>
map<KEY, T, Compare>::~map() {
  delete tree_;
}

template <typename KEY, typename T, typename Compare>
map<KEY, T, Compare> map<KEY, T, Compare>::operator=(map &&other) {
  if (this != &other) {
    *tree_ = std::move(*other.tree_);
  }
  return *this;
}

template <typename KEY, typename T, typename Compare>
map<KEY, T, Compare> map<KEY, T, Compare>::operator=(const map &other) {
  if (this != &other) {
    *tree_ = *other.tree_;
  }
  return *this;
}

template <typename KEY, typename T, typename Compare>
typename map<KEY, T, Compare>::mapped_type &map<KEY, T, Compare>::at(const key_type &key) {
  value_type find_this_key(key, mapped_type());
  iterator it = tree_->Find(find_this_key);
  if (it == tree_->end()) {
    throw std::out_of_range("No element with this key");
  }
  return (*it).second;
}

template <typename KEY, typename T, typename Compare>
const typename map<KEY, T, Compare>::mapped_type &map<KEY, T, Compare>::at(
    const key_type &key) const {
  return const_cast<map<KEY, T, Compare>>(*this)->at(key);
}

template <typename KEY, typename T, typename Compare>
typename map<KEY, T, Compare>::mapped_type &map<KEY, T, Compare>::operator[](
    const key_type &key) {
  value_type find_this_key(key, mapped_type());
  std::pair<iterator, bool> res = tree_->insertUnique(find_this_key);
  return (*res.first).second;
}

template <typename KEY, typename T, typename Compare>
typename map<KEY, T, Compare>::iterator map<KEY, T, Compare>::begin() {
  return tree_->begin();
}

template <typename KEY, typename T, typename Compare>
typename map<KEY, T, Compare>::iterator map<KEY, T, Compare>::end() {
  return tree_->end();
}

template <typename KEY, typename T, typename Compare>
typename map<KEY, T, Compare>::const_iterator map<KEY, T, Compare>::begin() const {
  return static_cast<const RBTree<value_type, value_compare> &>(
             *tree_)
      .begin();
}

template <typename KEY, typename T, typename Compare>
typename map<KEY, T, Compare>::const_iterator map<KEY, T, Compare>::end() const {
  return static_cast<const RBTree<value_type, value_compare> &>(
             *tree_)
      .end();
}

template <typename KEY, typename T, typename Compare>
bool map<KEY, T, Compare>::empty() const {
  return tree_->empty();
}

template <typename KEY, typename T, typename Compare>
typename map<KEY, T, Compare>::size_type map<KEY, T, Compare>::size() const {
  return tree_->size();
}

template <typename KEY, typename T, typename Compare>
typename map<KEY, T, Compare>::size_type map<KEY, T, Compare>::max_size() const {
  return tree_->max_size();
}

template <typename KEY, typename T, typename Compare>
void map<KEY, T, Compare>::clear() {
  tree_->clear();
}

template <typename KEY, typename T, typename Compare>
std::pair<typename map<KEY, T, Compare>::iterator, bool> map<KEY, T, Compare>::insert(
    const value_type &value) {
  return tree_->insertUnique(value);
}

template <typename KEY, typename T, typename Compare>
std::pair<typename map<KEY, T, Compare>::iterator, bool> map<KEY, T, Compare>::insert(
    const key_type &key, const mapped_type &obj) {
  value_type val(key, obj);
  std::pair<iterator, bool> res = tree_->insertUnique(val);
  return res;
}

template <typename KEY, typename T, typename Compare>
std::pair<typename map<KEY, T, Compare>::iterator, bool> map<KEY, T, Compare>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  value_type val(key, obj);
  std::pair<iterator, bool> res = tree_->insertUnique(val);
  if (!res.second) {
    (*res.first).second = obj;
  }
  return res;
}

template <typename KEY, typename T, typename Compare>
void map<KEY, T, Compare>::erase(iterator pos) {
  tree_->erase(pos);
}

template <typename KEY, typename T, typename Compare>
void map<KEY, T, Compare>::swap(map &other) {
  tree_->swap(*other.tree_);
}

template <typename KEY, typename T, typename Compare>
void map<KEY, T, Compare>::merge(map &other) {
  tree_->mergeUnique(*other.tree_);
}

template <typename KEY, typename T, typename Compare>
bool map<KEY, T, Compare>::contains(const key_type &key) {
  value_type find_this_key(key, mapped_type());
  return !(tree_->Find(find_this_key) == end());
}

template <typename KEY, typename T, typename Compare>
template <typename... Args>
std::vector<std::pair<typename map<KEY, T, Compare>::iterator, bool>>
map<KEY, T, Compare>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> res;
  (res.push_back(this->insert(std::forward<Args>(args))), ...);
  return res;
}

}  // namespace s21