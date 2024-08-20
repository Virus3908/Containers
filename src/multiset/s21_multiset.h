#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "../set/s21_set.h"

namespace s21 {

template <typename T>
class multiset : public set<T> {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using tree = RBTree<value_type>;
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;

  multiset();
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &other);
  multiset(multiset &&other);

  multiset operator=(multiset &&other);
  multiset operator=(const multiset &other);

  std::pair<iterator, bool> insert(const value_type &value);
  void merge(multiset &other);
  size_type count(const value_type &key);
  iterator lower_bound(const value_type &key);
  iterator upper_bound(const value_type &key);
  std::pair<iterator, iterator> equal_range(const value_type &key);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

}  // namespace s21

#include "s21_multiset.tpp"

#endif