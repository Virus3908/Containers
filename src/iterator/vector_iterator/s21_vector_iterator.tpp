#include "s21_vector_iterator.h"

namespace s21 {

template <typename T>
VectorIterator<T>::VectorIterator() : cur_pos_(nullptr) {}

template <typename T>
VectorIterator<T>::VectorIterator(value_type *pos) : cur_pos_(pos) {}

template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator &other)
    : VectorIterator() {
  *this = other;
}

template <typename T>
VectorIterator<T>::VectorIterator(VectorIterator &&other) : VectorIterator() {
  *this = std::move(other);
}

template <typename T>
VectorIterator<T> &VectorIterator<T>::operator=(const VectorIterator &other) {
  if (this != &other) {
    cur_pos_ = other.cur_pos_;
  }
  return *this;
}

template <typename T>
VectorIterator<T> &VectorIterator<T>::operator=(VectorIterator &&other) {
  if (this != &other) {
    cur_pos_ = other.cur_pos_;
    other.cur_pos_ = nullptr;
  }
  return *this;
}

template <typename T>
bool VectorIterator<T>::operator==(const VectorIterator &other) const {
  return cur_pos_ == other.cur_pos_;
}

template <typename T>
bool VectorIterator<T>::operator<(const VectorIterator &other) const {
  return (*this - other) < 0;
}

template <typename T>
bool VectorIterator<T>::operator>(const VectorIterator &other) const {
  return (*this - other) > 0;
}

template <typename T>
bool VectorIterator<T>::operator!=(const VectorIterator &other) const {
  return cur_pos_ != other.cur_pos_;
}

template <typename T>
VectorIterator<T> &VectorIterator<T>::operator++() {
  ++cur_pos_;
  return *this;
}

template <typename T>
VectorIterator<T> &VectorIterator<T>::operator--() {
  --cur_pos_;
  return *this;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int) {
  VectorIterator tmp(*this);
  ++(*this);
  return tmp;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator--(int) {
  VectorIterator tmp(*this);
  --(*this);
  return tmp;
}

template <typename T>
VectorIterator<T> &VectorIterator<T>::operator+=(int val) {
  for (int i = 0; i < val; ++i) {
    ++(*this);
  }
  return *this;
}

template <typename T>
VectorIterator<T> &VectorIterator<T>::operator-=(int val) {
  for (int i = 0; i < val; ++i) {
    --(*this);
  }
  return *this;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator+(int val) {
  VectorIterator<T> tmp(*this);
  for (int i = 0; i < val; ++i) {
    ++(tmp);
  }
  return tmp;
}

template <typename T>
typename VectorIterator<T>::difference_type VectorIterator<T>::operator-(const VectorIterator &other) {
  return cur_pos_ - other.cur_pos_;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator-(int val) {
  VectorIterator<T> tmp(*this);
  for (int i = 0; i < val; ++i) {
    --(tmp);
  }
  return tmp;
}

template <typename T>
typename VectorIterator<T>::reference VectorIterator<T>::operator*() {
  return *cur_pos_;
}

template <typename T>
typename VectorIterator<T>::value_type *VectorIterator<T>::operator->() {
  return cur_pos_;
}

template <typename T>
ConstVectorIterator<T>::ConstVectorIterator() : VectorIterator<T>() {}

template <typename T>
ConstVectorIterator<T>::ConstVectorIterator(value_type *pos)
    : VectorIterator<T>(pos) {}

template <typename T>
ConstVectorIterator<T>::ConstVectorIterator(const VectorIterator<T> &other)
    : VectorIterator<T>(other) {}

template <typename T>
ConstVectorIterator<T>::ConstVectorIterator(const ConstVectorIterator &other)
    : VectorIterator<T>(other) {}

template <typename T>
ConstVectorIterator<T>::ConstVectorIterator(ConstVectorIterator &&other)
    : VectorIterator<T>(std::move(other)) {}

template <typename T>
ConstVectorIterator<T> &ConstVectorIterator<T>::operator=(
    const ConstVectorIterator &other) {
  if (this != &other) {
    this->cur_pos_ = other.cur_pos_;
  }
  return *this;
}

template <typename T>
ConstVectorIterator<T> &ConstVectorIterator<T>::operator=(
    ConstVectorIterator &&other) {
  if (this != &other) {
    this->cur_pos_ = other.cur_pos_;
    other.cur_pos_ = nullptr;
  }
  return *this;
}

template <typename T>
typename ConstVectorIterator<T>::const_reference
ConstVectorIterator<T>::operator*() {
  return *this->cur_pos_;
}

}  // namespace s21