#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <initializer_list>

namespace s21 {

template <typename T, std::size_t S>
class array {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &other);
  array(array &&other);
  ~array();

  array<T, S> &operator=(const array &other);
  array<T, S> &operator=(array &&other);

  reference at(size_type pos);
  reference operator[](size_type pos);
  reference front();
  reference back();

  const_reference at(size_type pos) const;
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;

  iterator data();
  const_iterator data() const;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void swap(array &other);
  void fill(const_reference value);

 private:
  value_type arr_[S] = {};
};
}  // namespace s21
#include "s21_array.tpp"

#endif