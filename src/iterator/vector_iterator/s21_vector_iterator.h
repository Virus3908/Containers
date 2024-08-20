#ifndef S21_VECTOR_ITERATOR_H
#define S21_VECTOR_ITERATOR_H

#include <iostream>

namespace s21 {

template <typename T>
class VectorIterator {
 public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using reference = value_type &;
  using difference_type = std::ptrdiff_t;

  VectorIterator();
  VectorIterator(value_type *pos);
  VectorIterator(const VectorIterator &other);
  VectorIterator(VectorIterator &&other);

  VectorIterator<T> &operator=(const VectorIterator &other);
  VectorIterator<T> &operator=(VectorIterator &&other);

  bool operator==(const VectorIterator &other) const;
  bool operator!=(const VectorIterator &other) const;
  bool operator>(const VectorIterator &other) const;
  bool operator<(const VectorIterator &other) const;

  VectorIterator<T> &operator++();
  VectorIterator<T> &operator--();
  VectorIterator<T> operator++(int);
  VectorIterator<T> operator--(int);
  VectorIterator<T> &operator+=(int val);
  VectorIterator<T> &operator-=(int val);
  VectorIterator<T> operator+(int val);
  VectorIterator<T> operator-(int val);
  difference_type operator-(const VectorIterator &other);

  value_type *operator->();
  reference operator*();

 protected:
  value_type *cur_pos_;
};

template <typename T>
class ConstVectorIterator : public VectorIterator<T> {
 public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using const_reference = value_type &;
  using difference_type = std::ptrdiff_t;

  ConstVectorIterator();
  ConstVectorIterator(value_type *pos);
  ConstVectorIterator(const VectorIterator<T> &other);
  ConstVectorIterator(const ConstVectorIterator &other);
  ConstVectorIterator(ConstVectorIterator &&other);

  ConstVectorIterator<T> &operator=(const ConstVectorIterator &other);
  ConstVectorIterator<T> &operator=(ConstVectorIterator &&other);

  const_reference operator*();
};

}  // namespace s21

#include "s21_vector_iterator.tpp"

#endif