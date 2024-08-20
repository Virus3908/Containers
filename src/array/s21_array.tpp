#include "s21_array.h"

namespace s21 {

template <typename T, std::size_t S>
array<T, S>::array() {}

template <typename T, std::size_t S>
array<T, S>::array(std::initializer_list<value_type> const &items) {
  if (items.size() != S) {
    throw std::runtime_error("Size error");
  }
  for (auto i = 0U; i < S; ++i) {
    arr_[i] = items.begin()[i];
  }
}

template <typename T, std::size_t S>
array<T, S>::array(const array &other) {
  *this = other;
}

template <typename T, std::size_t S>
array<T, S>::array(array &&other) {
  *this = std::move(other);
}

template <typename T, std::size_t S>
array<T, S>::~array() {}

template <typename T, std::size_t S>
array<T, S> &array<T, S>::operator=(const array &other) {
  if (this != &other) {
    for (auto i = 0U; i < S; ++i) {
      arr_[i] = other.arr_[i];
    }
  }
  return *this;
}

template <typename T, std::size_t S>
array<T, S> &array<T, S>::operator=(array &&other) {
  if (this != &other) {
    for (auto i = 0U; i < S; ++i) {
      arr_[i] = std::move(other.arr_[i]);
    }
  }
  return *this;
}

template <typename T, std::size_t S>
typename array<T, S>::const_reference array<T, S>::at(size_type pos) const {
  if (pos >= S) {
    throw std::out_of_range("Out of range array");
  }
  return this->operator[](pos);
}

template <typename T, std::size_t S>
typename array<T, S>::const_reference array<T, S>::operator[](
    size_type pos) const {
  return arr_[pos];
}

template <typename T, std::size_t S>
typename array<T, S>::const_reference array<T, S>::front() const {
  return this->operator[](0);
}

template <typename T, std::size_t S>
typename array<T, S>::const_reference array<T, S>::back() const {
  return this->operator[](S - 1);
}

template <typename T, std::size_t S>
typename array<T, S>::reference array<T, S>::at(size_type pos) {
  return const_cast<reference>(static_cast<const array &>(*this).at(pos));
}

template <typename T, std::size_t S>
typename array<T, S>::reference array<T, S>::operator[](size_type pos) {
  return const_cast<reference>(
      static_cast<const array &>(*this).operator[](pos));
}

template <typename T, std::size_t S>
typename array<T, S>::reference array<T, S>::front() {
  return const_cast<reference>(static_cast<const array &>(*this).front());
}

template <typename T, std::size_t S>
typename array<T, S>::reference array<T, S>::back() {
  return const_cast<reference>(static_cast<const array &>(*this).back());
}

template <typename T, std::size_t S>
typename array<T, S>::iterator array<T, S>::begin() {
  return arr_;
}

template <typename T, std::size_t S>
typename array<T, S>::iterator array<T, S>::end() {
  return (arr_ + S);
}

template <typename T, std::size_t S>
typename array<T, S>::const_iterator array<T, S>::begin() const {
  return arr_;
}

template <typename T, std::size_t S>
typename array<T, S>::const_iterator array<T, S>::end() const {
  return (arr_ + S);
}

template <typename T, std::size_t S>
typename array<T, S>::iterator array<T, S>::data() {
  return arr_;
}

template <typename T, std::size_t S>
typename array<T, S>::const_iterator array<T, S>::data() const {
  return arr_;
}

template <typename T, std::size_t S>
bool array<T, S>::empty() const {
  return begin() == end();
}

template <typename T, std::size_t S>
typename array<T, S>::size_type array<T, S>::size() const {
  return S;
}

template <typename T, std::size_t S>
typename array<T, S>::size_type array<T, S>::max_size() const {
  return std::numeric_limits<value_type>::max();
}

template <typename T, std::size_t S>
void array<T, S>::swap(array &other) {
  std::swap(arr_, other.arr_);
}

template <typename T, std::size_t S>
void array<T, S>::fill(const_reference value) {
  for (auto i = 0U; i < S; ++i) {
    arr_[i] = value;
  }
}

}  // namespace s21