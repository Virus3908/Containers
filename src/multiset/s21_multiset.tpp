#include "s21_multiset.h"

namespace s21 {

template <typename T>
multiset<T>::multiset() : set<T>() {}

template <typename T>
multiset<T>::multiset(const multiset &other) : set<T>(other) {}

template <typename T>
multiset<T>::multiset(multiset &&other) : set<T>(std::move(other)) {}

template <typename T>
multiset<T>::multiset(std::initializer_list<value_type> const &items) {
  for (auto &it : items) {
    insert(it);
  }
}

template <typename T>
multiset<T> multiset<T>::operator=(multiset &&other) {
  if (this != &other) {
    set<T>::operator=(std::move(other));
  }
  return *this;
}

template <typename T>
multiset<T> multiset<T>::operator=(const multiset &other) {
  if (this != &other) {
    set<T>::operator=(other);
  }
  return *this;
}

template <typename T>
std::pair<typename multiset<T>::iterator, bool> multiset<T>::insert(
    const value_type &value) {
  return this->tree_->insert(value);
}

template <typename T>
void multiset<T>::merge(multiset &other) {
  this->tree_->merge(*other.tree_);
}

template <typename T>
typename multiset<T>::size_type multiset<T>::count(const value_type &key) {
  size_type res = 0U;
  iterator begin = this->lower_bound(key);
  iterator end = this->upper_bound(key);
  while (begin != end) {
    ++res;
    ++begin;
  }
  return res;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::lower_bound(const value_type &key) {
  return this->tree_->lower_bound(key);
}

template <typename T>
typename multiset<T>::iterator multiset<T>::upper_bound(const value_type &key) {
  return this->tree_->upper_bound(key);
}

template <typename T>
std::pair<typename multiset<T>::iterator, typename multiset<T>::iterator>
multiset<T>::equal_range(const value_type &key) {
  return std::pair(lower_bound(key), upper_bound(key));
}

template <typename T>
template <typename... Args>
std::vector<std::pair<typename multiset<T>::iterator, bool>>
multiset<T>::insert_many(Args &&...args) {
  std::vector<std::pair<typename multiset<T>::iterator, bool>> res;
  for (auto &arg : {args...}) {
    res.push_back(insert(arg));
  }
  return res;
}

}  // namespace s21