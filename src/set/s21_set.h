#ifndef S21_SET_H
#define S21_SET_H

#include "../tree/s21_RBTree.h"

namespace s21 {

template <typename T>
class set {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using tree = RBTree<value_type>;
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &other);
  set(set &&other);
  virtual ~set();

  set operator=(set &&other);
  set operator=(const set &other);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const value_type &key);
  bool contains(const value_type &key);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 protected:
  tree *tree_;
};
}  // namespace s21

#include "s21_set.tpp"

#endif
