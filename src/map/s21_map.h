#ifndef S21_MAP_H
#define S21_MAP_H

#include "../tree/s21_RBTree.h"

namespace s21 {

template <typename T>
struct MapComparator {
  bool operator()(T val1, T val2) { return val1.first < val2.first; }
};

template <typename KEY, typename T>
class map {
 public:
  using key_type = KEY;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using tree = RBTree<value_type, MapComparator<value_type>>;
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &other);
  map(map &&other);
  ~map();

  map operator=(map &&other);
  map operator=(const map &other);

  mapped_type &at(const key_type &key);
  const mapped_type &at(const key_type &key) const;
  mapped_type &operator[](const key_type &key);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  bool contains(const key_type &key);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  tree *tree_;
};

}  // namespace s21

#include "s21_map.tpp"

#endif