#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <initializer_list>
#include <limits>

#include "../iterator/vector_iterator/s21_vector_iterator.h"

namespace s21 {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = VectorIterator<value_type>;
  using const_iterator = ConstVectorIterator<value_type>;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &other);
  vector(vector &&other);
  ~vector();

  vector<T> &operator=(const vector &other);
  vector<T> &operator=(vector &&other);

  reference at(size_type pos);
  reference operator[](size_type pos);
  reference front();
  reference back();
  const_reference at(size_type pos) const;
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  value_type *data();
  const value_type *data() const;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args... args);
  template <typename... Args>
  void insert_many_back(Args... args);

 private:
  value_type *arr_;
  size_type size_ = 0U;
  size_type capacity_ = 0U;
};
}  // namespace s21

#include "s21_vector.tpp"

#endif