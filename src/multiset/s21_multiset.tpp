#include "s21_multiset.h"

namespace s21 {

template <typename T, typename Compare>
multiset<T, Compare>::multiset() : set<T, Compare>() {}

template <typename T, typename Compare>
multiset<T, Compare>::multiset(const multiset &other)
    : set<T, Compare>(other) {}

template <typename T, typename Compare>
multiset<T, Compare>::multiset(multiset &&other)
    : set<T, Compare>(std::move(other)) {}

template <typename T, typename Compare>
multiset<T, Compare>::multiset(std::initializer_list<value_type> const &items) {
  for (auto &it : items) {
    insert(it);
  }
}

template <typename T, typename Compare>
multiset<T, Compare> multiset<T, Compare>::operator=(multiset &&other) {
  if (this != &other) {
    set<T, Compare>::operator=(std::move(other));
  }
  return *this;
}

template <typename T, typename Compare>
multiset<T, Compare> multiset<T, Compare>::operator=(const multiset &other) {
  if (this != &other) {
    set<T, Compare>::operator=(other);
  }
  return *this;
}

template <typename T, typename Compare>
std::pair<typename multiset<T, Compare>::iterator, bool>
multiset<T, Compare>::insert(const value_type &value) {
  return this->tree_->insert(value);
}

template <typename T, typename Compare>
void multiset<T, Compare>::merge(multiset &other) {
  this->tree_->merge(*other.tree_);
}

template <typename T, typename Compare>
typename multiset<T, Compare>::size_type multiset<T, Compare>::count(
    const value_type &key) {
  size_type res = 0U;
  iterator begin = this->lower_bound(key);
  iterator end = this->upper_bound(key);
  while (begin != end) {
    ++res;
    ++begin;
  }
  return res;
}

template <typename T, typename Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::lower_bound(
    const value_type &key) {
  return this->tree_->lower_bound(key);
}

template <typename T, typename Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::upper_bound(
    const value_type &key) {
  return this->tree_->upper_bound(key);
}

template <typename T, typename Compare>
std::pair<typename multiset<T, Compare>::iterator,
          typename multiset<T, Compare>::iterator>
multiset<T, Compare>::equal_range(const value_type &key) {
  return std::pair(lower_bound(key), upper_bound(key));
}

template <typename T, typename Compare>
template <typename... Args>
std::vector<std::pair<typename multiset<T, Compare>::iterator, bool>>
multiset<T, Compare>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> res;
  (res.push_back(this->insert(std::forward<Args>(args))), ...);
  return res;
}

}  // namespace s21